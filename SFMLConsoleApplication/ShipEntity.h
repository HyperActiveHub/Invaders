#pragma once
#include "SFML\Graphics.hpp"
#include "Entity.h"

using namespace sf;

class ShipEntity : public Entity
{
public:
	ShipEntity(Game* game, Vector2f position);
	~ShipEntity();
	virtual void update(float deltaTime) override;
	virtual void collide(Entity* other) override;

private:
	Vector2f input();
	void constrainPosition(Vector2f& input);
	void handleMovement(Vector2f input, float deltaTime);

	void handleFire(float deltaTime);
	float mFireDelta;
	float mFireTime;
	float mVelocity;

};

