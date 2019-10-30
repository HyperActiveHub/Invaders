#pragma once
#include "Game.h"
#include <string>
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

enum class EntityType { PROJECTILE, SHIP, EFFECT };
enum class EntityFaction { FRIEND, ENEMY, NEUTRAL };

class Entity
{
public:
	Entity(Game* game, std::string filename, Vector2f position, float radius, EntityType type, EntityFaction faction);
	virtual ~Entity();
	virtual void update(float deltaTime) = 0;
	virtual void collide(Entity* other);
	virtual void die();
	virtual void draw();
	float getRadius();
	Vector2f getPosition();
	EntityType getType();
	EntityFaction getFaction();

protected:
	void centerSprite();
	Game* mGame;
	Sprite mSprite;
	float mRadius;
	EntityType mType;
	EntityFaction mFaction;
};