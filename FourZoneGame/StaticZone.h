#pragma once
#include "Zone.h"
#include "Trap.h"

class Player;

class StaticZone : public Zone
{
public:
	StaticZone(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& sound) : Zone(sprite, sound) {}
	void Update(const shared_ptr<Player>& player) override;
	//void GenerateTraps();
};

