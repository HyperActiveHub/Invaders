#pragma once
#include "Entity.h"

class InvaderEntity : public Entity
{
public:
	InvaderEntity(Game *game, sf::Vector2f position, sf::Vector2f direction);
	virtual void update(float deltaTime) override;
	virtual void collide(Entity* other) override;

private:

	void handleMovement(float deltaTime);
	void handleFire(float deltaTime);
	float mFireDelta;
	float mFireTime;
	sf::Vector2f mDirection;
	float mVelocity;
};

