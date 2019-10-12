#include "Game.h"
#include "ShipEntity.h"	
#include "InvaderEntity.h"		//Cirkulärt beroende kräver att dessa inkluderas i game.cpp istället för game.h, 
//samt att framåtdeklarationer av typerna Entity, EnttiyType och EntityFaction.

using namespace std;
using namespace sf;

namespace
{
	const float ENEMY_SPAWN_TIME = 10.0f;	//placeholder
	const float ENEMY_SPAWN_DELTA = 5.0f;	//placeholder

	const unsigned int FRAMERATE = 144;

	const string windowTitle = "Invaders";
	const VideoMode videoMode = VideoMode(768, 1024);

}

Game::Game() :
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close),
	mTextureResources(),
	mEntities(),
	mOldEntities(),
	mNewEntities(),
	mTime(0),
	mSpawnTime(ENEMY_SPAWN_TIME),
	mSpawnDelta(ENEMY_SPAWN_DELTA),
	mGameOver(false)
{
	setFrameRate(FRAMERATE);
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
		display();
	}
}

RenderWindow& Game::getRenderWindow()
{
	return mRenderWindow;
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

			if (overlap(entity0, entity1))
			{
				entity0->collide(entity1);
				entity1->collide(entity0);
			}
		}
	}
}

bool Game::overlap(Entity* ent0, Entity* ent1)
{
	float deltaX = ent0->getPosition().x - ent1->getPosition().x;
	float deltaY = ent0->getPosition().y - ent1->getPosition().y;

	if (pow(deltaX, 2) + pow(deltaY, 2) < pow(ent0->getRadius() + ent1->getRadius(), 2))
	{
		return true;
	}
	return false;
}

EntityVector Game::getVisibleEntities()
{

	return /*temp*/ EntityVector();
}

void Game::destroyOldEntities()
{
	EntityVector remainingEntities;
	for (auto entity : mEntities)
	{
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
	for (auto oldEntity : mOldEntities)
	{
		if (oldEntity == entity)
		{
			return true;
		}
	}
	return false;
}

void Game::handleWindowEvents()
{
	Event event;
	while (mRenderWindow.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			mRenderWindow.close();
		}
	}
}

void Game::clearWindow()
{
	mRenderWindow.clear();
}

void Game::display()
{
	mRenderWindow.display();
}

void Game::updateTime(float deltaTime)
{
	//clock.reset? stuff?
}

void Game::updateEntities(float deltaTime)
{
	for (auto entity : mEntities)
	{
		entity->update(deltaTime);
	}
}

void Game::add(Entity* entity)
{
	mNewEntities.push_back(entity); //correct?
}

void Game::remove(Entity* entity)
{
	mOldEntities.push_back(entity); //correct?
}

void Game::setFrameRate(unsigned int rate)
{
	mRenderWindow.setFramerateLimit(rate);
}