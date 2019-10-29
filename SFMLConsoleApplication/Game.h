#pragma once
#include <string>
#include "TextureResource.h"
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Entity;			//Framåtdeklaration av typerna i Entity.h
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
private:
	sf::RenderWindow mRenderWindow;
	TextureResourceVector mTextureResources;
	EntityVector mEntities;
	EntityVector mNewEntities;		//Mellanlagring av nya och gamla objekt (objekter som kommer att läggas till eller tas bort 
	EntityVector mOldEntities;		//under nästa iteration av loopen. Detta görs för att kunna gå igenom mEntities utan att stöta
									//på borttagna/nya objekt
	float mTime;
	float mSpawnDelta;
	float mSpawnTime;
	bool mGameOver;

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
	void initRand();
	int randValue(int min, int max);
};