#pragma once
#include "Zone.h"

class Player;

class InvisibleZone : public Zone
{
public:
	InvisibleZone(const shared_ptr<sf::Sprite>& spr, const shared_ptr<sf::Sound>& snd) : Zone(spr, snd) {}
public:
	void Update(const shared_ptr<Player>& player) override;
};

