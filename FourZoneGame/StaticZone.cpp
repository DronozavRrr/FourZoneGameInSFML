#include "StaticZone.h"
#include "Player.h"
#include "Trap.h"
#include "Bullet.h"
#include "Game.h"

void StaticZone::Update(const shared_ptr<Player>& player)
{
	player->SetSliding(false);
	player->Shoot(this->GetBounds());

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		auto& entity = *it;
		// mob intersects player
		if (entity->Intersect(player))
		{
			player->SetHealth(player->GetHealth() - 20);
			
			entities.erase(it);

			if (player->GetHealth() <= 0)
			{
				//to do : end game
			}
		}

	}
}