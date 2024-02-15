#pragma once
#include "Bonus.h"
#include "Player.h"

class PointsBonus : public Bonus
{
public:
	PointsBonus(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& sound) : Bonus(sprite, sound) {}

	void Update(const shared_ptr<Player>& player) override
	{
		Resources::LoadGlobalSound("pb sound")->play();
		player->SetPoints(player->GetPoints() + 1);
	}
};


#pragma once
