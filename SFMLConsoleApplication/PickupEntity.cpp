#include "PickupEntity.h"
#include "ShipEntity.h"

namespace
{
	const int MIN_VELOCITY = 2;
	const int MAX_VELOCITY = 200;
	const float POWER_UP_RADIUS = 32.0f;
	const float POWER_DOWN_RADIUS = 32.0f;
}

PickupEntity::PickupEntity(Game* game, Vector2f position, PickupType type) :
	mPickupType(type),
	mVelocity(getRandVelocity()),
	Entity(game, getSpriteName(type), position, getRadius(type), EntityType::EFFECT, EntityFaction::NEUTRAL)
{
	mGame->add(this);
	
}

void PickupEntity::collide(Entity* other)
{
	if (other->getType() == EntityType::SHIP && other->getFaction() == EntityFaction::FRIEND)
	{
		ShipEntity* ship = dynamic_cast<ShipEntity*>(other);

		switch (mPickupType)
		{
		case PickupType::PowerUp:
			ship->addFirePower();
			break;
		case PickupType::PowerDown:
			ship->decreaseFirePower();
			break;
		default:
			cout << "Error: Effect for pickup of type '" << (int)mPickupType << "' was not found." << endl;
			break;
		}

		die();
	}
}

void PickupEntity::update(float deltaTime)
{
	mSprite.move(Vector2f(0, 1) * (float)mVelocity * deltaTime);

	if (getPosition().y > mRadius + mGame->getRenderWindow().getSize().y)
	{
		die();
	}
}

PickupType PickupEntity::getRandPickup()
{
	return (PickupType)(rand() % (int)PickupType::Count);	//Temporary equal chance for all powerups to drop.
}

string PickupEntity::getSpriteName(PickupType type)
{
	switch (type)
	{
	case PickupType::PowerUp:
		return "PowerUp.png";
		break;

	case PickupType::PowerDown:
		return "PowerDown.png";
		break;

	default:
		cout << "Error: filename for sprite corresponding to pickup of type '" << (int)type << "' was not found." << endl;
		return "invalid";
		break;
	}
}

float PickupEntity::getRadius(PickupType type)
{
	switch (type)
	{
	case PickupType::PowerUp:
		return POWER_UP_RADIUS;
		break;

	case PickupType::PowerDown:
		return POWER_DOWN_RADIUS;
		break;

	default:
		cout << "Error: radius for pickup of type '" << (int)type << "' was not found." << endl;
		return 0.0f;
		break;
	}

}

int PickupEntity::getRandVelocity()
{
	return rand() % MAX_VELOCITY + MIN_VELOCITY;
}

PickupEntity::~PickupEntity()
{
	//cout << "Destroyed pickup." << endl;
}
