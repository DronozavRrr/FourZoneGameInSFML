#pragma once
#include "Bonus.h"
#include "Resources.h"

class LifeBonus : public Bonus
{
public:
	LifeBonus(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& sound) : Bonus(sprite, sound) {}

	void Update(const shared_ptr<Player>& player) override
	{
		Resources::LoadGlobalSound("lb sound")->play();

		this->PlaySound();
		player->SetHealth(player->GetHealth() + 20);
	}
};


