#include "Game.h"
#include "ShipEntity.h"	
#include "InvaderEntity.h"		//Cirkulärt beroende kräver att dessa inkluderas i game.cpp istället för game.h, 
//samt att framåtdeklarationer av typerna Entity, EnttiyType och EntityFaction.

#include <iostream>

using namespace std;
using namespace sf;

namespace
{
	enum class GameState { ingame, paused, gameOver };
	GameState currentState = GameState::ingame;

	const float ENEMY_SPAWN_DELTA = 2.0f;	//placeholder
	const float ENEMY_DELTA_DECREASE_RATE = 0.99f;

	const int ENEMY_VALUE = 100;
	const int BULLET_COST = 10;

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
	mSpawnDelta(ENEMY_SPAWN_DELTA),
	mScore(0),
	mFont(loadFont("SHOWG.TTF")),
	mPauseText(),
	mGoText(),
	mRestartText(),
	mScoreText()
{
	setFrameRate(FRAMERATE);
	initRand();
	textInit();

	createShip();
}

void Game::run()
{
	Clock clock;
	float deltaTime;

	while (mRenderWindow.isOpen())
	{
		switch (currentState)
		{
		case GameState::ingame:
			deltaTime = clock.restart().asSeconds();
			handleWindowEvents();
			update(deltaTime);
			drawIngame();
			break;

		case GameState::paused:
			clock.restart();
			handleWindowEvents();
			drawPaused();
			break;

		case GameState::gameOver:
			deltaTime = clock.restart().asSeconds();
			handleWindowEvents();
			update(deltaTime);
			drawGameOver();
			break;
		}
	}
}

RenderWindow& Game::getRenderWindow()
{
	return mRenderWindow;
}

void Game::drawIngame()
{
	drawEntities();
	mRenderWindow.draw(mScoreText);
	display();
}

void Game::drawPaused()
{
	drawEntities();
	mRenderWindow.draw(mPauseText);
	mRenderWindow.draw(mScoreText);
	display();
}

void Game::drawGameOver()
{
	editText(mFinalScoreText, "Final Score: " + to_string(mScore), Vector2f(mRenderWindow.getSize().x * 0.5f, 300), Color::White, 50);
	drawEntities();
	mRenderWindow.draw(mGoText);
	mRenderWindow.draw(mRestartText);
	mRenderWindow.draw(mFinalScoreText);
	display();
}

void Game::update(float deltaTime)
{
	destroyOldEntities();
	addNewEntities();
	updateTime(deltaTime);
	updateEntities(deltaTime);
	updateScore();
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

	Image image;
	image.loadFromFile(filename);
	image.createMaskFromColor(Color::Magenta);	//Needed for transparancy in images using a color.
	Texture texture;
	texture.loadFromImage(image);
	texture.setSmooth(true);
	TextureResource* textureResource = new TextureResource(filename, texture);
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
	int x = randValue(0, getRenderWindow().getSize().x);
	int y = -50;	//Temp y-axis spawnPos.
	Vector2f spawnPos((float)x, (float)y);
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

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				if (currentState == GameState::paused)
				{
					currentState = GameState::ingame;
				}
				else if (currentState == GameState::ingame)
				{
					currentState = GameState::paused;
				}
				else if (currentState == GameState::gameOver)
				{
					destroyAllEntities();
					mRenderWindow.close();
				}
			}
			else if (currentState == GameState::gameOver && event.key.code == Keyboard::Space)
			{
				restartGame();
				currentState = GameState::ingame;
			}
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
	if (mSpawnDelta < mTime)
	{
		createInvader();
		mTime = 0;
		mSpawnDelta *= ENEMY_DELTA_DECREASE_RATE;
		cout << mSpawnDelta << endl;
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

void Game::drawEntities()
{
	clearWindow();

	for (auto entity : mEntities)
	{
		entity->draw();
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

void Game::initRand()
{
	srand((unsigned int)time(0));
}

void Game::increaseScore()
{
	mScore += ENEMY_VALUE;
}

void Game::decreaseScore()
{
	mScore -= BULLET_COST;
}

void Game::restartGame()
{
	destroyAllEntities();
	createShip();
	mSpawnDelta = ENEMY_SPAWN_DELTA;
	mScore = 0;
	updateScore();
}

void Game::destroyAllEntities()
{
	for (auto e : mEntities)
	{
		delete e;
	}
	mEntities.clear();

	for (auto e : mOldEntities)
	{
		delete e;
	}
	mOldEntities.clear();

	for (auto e : mNewEntities)
	{
		delete e;
	}
	mNewEntities.clear();
}

void Game::editText(Text& text, string newText, Vector2f pos, Color color, unsigned int size)
{
	text.setString(newText);
	text.setFont(mFont);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setOrigin(text.getLocalBounds().width * 0.5f, text.getLocalBounds().height * 0.5f);
	text.setPosition(pos);
}

void Game::textInit()
{
	editText(mPauseText, "Paused", mRenderWindow.getView().getCenter(), Color::Red, 64);
	editText(mGoText, "Game Over", mRenderWindow.getView().getCenter(), Color::Red, 72);
	editText(mRestartText, "Press 'Space' to restart or 'Escape' to quit.", Vector2f(mGoText.getPosition().x, mGoText.getPosition().y + 70), Color::White, 20);
	mScoreText.setFont(mFont);
	mScoreText.setString("Score: ");
	mScoreText.setCharacterSize(30);
	mScoreText.setPosition(Vector2f(20, 20));
}

Font Game::loadFont(string fileName)
{
	Font font;
	font.loadFromFile(fileName);
	return font;
}

void Game::GameOver()
{
	currentState = GameState::gameOver;
}

void Game::updateScore()
{
	mScoreText.setString(mScoreText.getString().substring(0, 7) + to_string(mScore));
}