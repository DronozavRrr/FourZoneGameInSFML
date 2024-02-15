#include "StaticZone.h"
#include "Player.h"
#include "Trap.h"
#include "Bullet.h"
#include "Game.h"
#include "Bonus.h"
#include "Resources.h"

void StaticZone::Update(const shared_ptr<Player>& player)
{
	player->SetSliding(false);
	player->SetVisible(true);
	player->Shoot(this->GetBounds());

	// todo
	for (uint32_t i = 0; i < entities.size(); i++)
	{
		auto& entity = entities[i];
		// mob intersects player
		if (entity->Intersect(player))
		{
			if (Utils::IsType<Entity, Trap>(entity.get()))
			{
				Resources::LoadGlobalSound("injured")->play();
				player->SetHealth(player->GetHealth() - 20);

				Erase(i);

				if (player->GetHealth() <= 0)
				{
					//to do : end game
				}
				i--;

				continue;
			}
			
			if (Utils::IsType<Entity, Bonus>(entity.get()))
			{
				((Bonus*)entity.get())->Update(player);
				Erase(i);
				i--;
				continue;
			}
		}
	}
}