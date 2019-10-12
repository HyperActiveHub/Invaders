#include "Game.h"
#include <string>
#include "SFML/Graphics.hpp"
#pragma once
using namespace sf;

enum class EntityType { PROJECTILE, SHIP, EFFECT };
enum class EntityFaction { FRIEND, ENEMY, NEUTRAL };

class Entity
{
public:
	Entity(Game* game, std::string filename, Vector2f position, float radius, EntityType type, EntityFaction faction);
	//virtual ~Entity();
	virtual void update(float deltaTime);
	virtual void collide(Entity* other);
	float getRadius();
	Vector2f getPosition();
	EntityType getType();
	EntityFaction getFaction();
	void draw();

protected:
	void centerSprite();
	Game* mGame;
	Sprite mSprite;
	float mRadius;
	EntityType mType;
	EntityFaction mFaction;
};