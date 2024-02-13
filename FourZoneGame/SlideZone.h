#pragma once
#include "Zone.h"

class Player;

class SlideZone : public Zone
{
public:
	SlideZone(const shared_ptr<sf::Sprite>& spr, const shared_ptr<sf::Sound>& snd) : Zone(spr, snd) {}
public:
	void Update(const sf::Time& elapsed) override;
	void Update(const shared_ptr<Player>& player) override;
};

