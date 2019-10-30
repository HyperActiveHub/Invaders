#pragma once
#include <string>
#include "TextureResource.h"
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Entity;			//Fram�tdeklaration av typerna i Entity.h
enum class EntityType;
enum class EntityFaction;


typedef vector<Entity*> EntityVector;
typedef vector<TextureResource*> TextureResourceVector;



class Game
{
public:

	Game();
	bool isVisible(Entity* entity);
	sf::RenderWindow& getRenderWindow();
	sf::Texture& getTexture(std::string filename);
	void run();
	void add(Entity* entity);
	void remove(Entity* entity);
	void shipHit();
	void increaseScore();
	void decreaseScore();
	void GameOver();
private:
	sf::RenderWindow mRenderWindow;
	TextureResourceVector mTextureResources;
	EntityVector mEntities;
	EntityVector mNewEntities;		//Mellanlagring av nya och gamla objekt (objekter som kommer att l�ggas till eller tas bort 
	EntityVector mOldEntities;		//under n�sta iteration av loopen. Detta g�rs f�r att kunna g� igenom mEntities utan att st�ta
									//p� borttagna/nya objekt
	float mTime;
	float mSpawnDelta;
	EntityVector getVisibleEntities();
	void createShip();
	void createInvader();
	void spawnInvader(float deltaTime);
	void spawnShip();
	void destroyOldEntities();
	void addNewEntities();
	bool overlap(Entity*, Entity*);
	void collideEntities();
	bool isOld(Entity* entity);
	void handleWindowEvents();
	void clearWindow();
	void display();
	void setFrameRate(unsigned int);
	void updateTime(float deltaTime);
	void updateEntities(float deltaTime);
	void updateScore();
	void drawEntities();
	void initRand();
	void restartGame();
	void destroyAllEntities();
	void drawIngame();
	void drawPaused();
	void drawGameOver();
	void update(float deltaTime);
	int randValue(int min, int max);
	int mScore;
	void editText(Text& text, string newText, Vector2f pos, Color color, unsigned int size);
	void textInit();
	Font mFont;
	Font loadFont(string fileName);
	Text mPauseText;
	Text mGoText;
	Text mRestartText;
	Text mScoreText;
	Text mFinalScoreText;
};