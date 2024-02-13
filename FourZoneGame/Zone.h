#pragma once
#include "Entity.h"
#include "library.h"

class Player;

class Zone : public Entity
{
public:
	Zone() {}
	Zone(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& snd) : Entity(sprite, snd) {}

	virtual void Update(const sf::Time& elapsed) override;
	virtual void Update(const shared_ptr<Player>& player);
};

