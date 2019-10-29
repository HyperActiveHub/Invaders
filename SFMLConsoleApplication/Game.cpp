#include "Game.h"
#include "ShipEntity.h"	
#include "InvaderEntity.h"		//Cirkulärt beroende kräver att dessa inkluderas i game.cpp istället för game.h, 
//samt att framåtdeklarationer av typerna Entity, EnttiyType och EntityFaction.

#include <iostream>

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
	initRand();

	createShip();
}

void Game::run()
{
	Clock clock;
	while (!mGameOver && mRenderWindow.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		destroyOldEntities();
		addNewEntities();
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

void Game::createShip()
{
	ShipEntity* ship = new ShipEntity(this, getRenderWindow().getView().getCenter());
	mEntities.push_back(ship);
}

void Game::createInvader()
{
	int x = getRenderWindow().getSize().x;
	int y = -50;	//Temp y-axis spawnPos.
	Vector2f spawnPos((int)randValue(0, x), y);
	Vector2f direction(0, 1);

	if (x - spawnPos.x < x * 0.5f)	//If the spawnPos is closer to the right side, the direction is set to left and vice versa.
	{
		direction.x = -1;
	}
	else
		direction.x = 1;
	
	InvaderEntity* invader = new InvaderEntity(this, spawnPos, direction);
	add(invader);
}

int Game::randValue(int min, int max)
{
	return rand() % max + min;
}

void Game::collideEntities()
{
	EntityVector visibleEntities = getVisibleEntities();

	for (EntityVector::size_type i = 0; i < visibleEntities.size(); i++)
	{
		Entity* entity0 = visibleEntities[i];

		for (EntityVector::size_type j = i + 1; j < visibleEntities.size(); j++)
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
	EntityVector visibleEntities;

	for (auto entity : mEntities)
	{
		if (isVisible(entity))
		{
			visibleEntities.push_back(entity);
		}
	}

	return visibleEntities;
}

bool Game::isVisible(Entity* entity)
{
	if (entity->getPosition().x > getRenderWindow().getSize().x - entity->getRadius())
	{
		return false;
	}
	else if (entity->getPosition().x < entity->getRadius())
	{
		return false;
	}
	else if (entity->getPosition().y > getRenderWindow().getSize().y - entity->getRadius())
	{
		return false;
	}
	else if (entity->getPosition().y < entity->getRadius())
	{
		return false;
	}

	return true;
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

void Game::addNewEntities()
{
	for (auto entity : mNewEntities)
	{
		mEntities.push_back(entity);
	}

	mNewEntities.clear();
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
	mTime += deltaTime;
	if (mSpawnTime < mTime)
	{
		createInvader();
		mTime = 0;
	}
}

void Game::updateEntities(float deltaTime)
{
	for (auto entity : mEntities)
	{
		entity->update(deltaTime);
	}

	collideEntities();
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

void Game::initRand()
{
	srand((unsigned int)time(0));
}