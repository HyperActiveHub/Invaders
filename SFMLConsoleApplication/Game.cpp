#include "Game.h"
#include "ShipEntity.h"	
#include "InvaderEntity.h"		//Cirkulärt beroende kräver att dessa inkluderas i game.cpp istället för game.h, 
//samt att framåtdeklarationer av typerna Entity, EnttiyType och EntityFaction.

using namespace std;
using namespace sf;

namespace
{

}

Game::Game() 
{
}

void Game::run()
{
	Clock clock;

	while (!mGameOver && mRenderWindow.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		updateTime(deltaTime);
		updateEntities(deltaTime);

	}
}

Texture& Game::getTexture(string filename)
{
	for (auto t : mTextureResources)
	{
		if (filename == t->getFilename())
		{
			return t->getTexture();
		}
	}

	Texture tex;
	tex.loadFromFile(filename);
	TextureResource* textureResource = new TextureResource(filename, tex);
	mTextureResources.push_back(textureResource);
	return textureResource->getTexture();
}

void Game::collideEntities()
{
	EntityVector visibleEntities = getVisibleEntities();

	for (EntityVector::size_type i = 0; i < visibleEntities.size(); i++)
	{
		Entity* entity0 = visibleEntities[i];

		for (EntityVector::size_type j = 0; j < visibleEntities.size(); j++)
		{
			Entity* entity1 = visibleEntities[j];

			entity0->collide(entity1); // check LF
		}
	}

	//collide
}

EntityVector Game::getVisibleEntities()
{

}

void Game::destroyOldEntities()
{
	EntityVector remainingEntities;
	for (auto e : mEntities)
	{
		Entity* entity = e;
		if (isOld(entity))
		{
			delete entity;
		}
		else
		{
			remainingEntities.push_back(entity);
		}
	}
	mOldEntities.clear();
	mEntities = remainingEntities;
}

bool Game::isOld(Entity* entity)
{
	for (auto ent : mOldEntities)
	{
		if (ent == entity)
		{
			return true;
		}
	}
	return false;
}
