#pragma once
#include "Zone.h"

class Player;

class DynamicZone : public Zone
{
public:
	DynamicZone(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& snd) : Zone(sprite, snd) {}
public:
	void Update(const shared_ptr<Player>& player) override;
};

