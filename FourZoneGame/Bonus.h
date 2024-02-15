#pragma once
#include "Entity.h"

class Player;

class Bonus : public Entity
{
public:
	Bonus(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& sound) : Entity(sprite, sound) {}

	virtual void Update(const shared_ptr<Player>& player) {};
};

