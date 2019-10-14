#include "ShipEntity.h"
#include <iostream>

namespace 
{
	const float RADIUS = 30.0f; //placeholder
	const float FIRE_DELTA = 0.5f;	
	const float VELOCITY = 300.0f;
}

ShipEntity::ShipEntity(Game* game, Vector2f position) : 
	Entity(game, "Ship.psd", position, RADIUS, EntityType::SHIP, EntityFaction::FRIEND),
	mFireDelta(FIRE_DELTA),
	mFireTime(0.0f),
	mVelocity(VELOCITY)
{
	std::cout << "Hello Ship." << std::endl;
}

ShipEntity::~ShipEntity()
{
	std::cout << "Goodbye Ship." << std::endl;
}

void ShipEntity::update(float deltaTime)
{
	Vector2f inputVector = input();
	constrainPosition(inputVector);
	handleMovement(inputVector, deltaTime);

	Entity::update(deltaTime);
}

void ShipEntity::collide(Entity* other)
{
	//game over?
	string str = typeid(*other).name();
	str.replace(0, 6, "");	//remove "class" from type-name.
	std::cout << "Player collided with " << str << std::endl;
}

Vector2f ShipEntity::input()
{
	Vector2f input;
	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		input.y = -1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		input.y = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		input.x = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		input.x = -1;
	}
	return input;
}

void ShipEntity::constrainPosition(Vector2f& input)
{
	if (input.x > 0 && getPosition().x > mGame->getRenderWindow().getSize().x - mRadius)
	{
		input.x = 0;
	}
	else if (input.x < 0 && getPosition().x < mRadius)
	{
		input.x = 0;
	}
	if (input.y > 0 && getPosition().y > mGame->getRenderWindow().getSize().y - mRadius)
	{
		input.y = 0;
	}
	else if (input.y < 0 && getPosition().y < mRadius)
	{
		input.y = 0;
	}
}

void ShipEntity::handleMovement(Vector2f input, float deltaTime)
{
	mSprite.move(input * mVelocity * deltaTime);
}

void handleFire(float deltaTime)
{
	
}