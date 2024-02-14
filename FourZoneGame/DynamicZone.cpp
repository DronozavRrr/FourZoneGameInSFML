#include "DynamicZone.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

void DynamicZone::Update(const shared_ptr<Player>& player)
{
	player->SetSliding(false);
	player->Shoot(this->GetBounds());

	

	
	for (auto& entity : entities)
	{
		// mob intersects player
		if (entity->Intersect(player))
		{
			if (player->attackClock.getElapsedTime() >= player->attackCooldown)
			{
				std::cout << "mob intersects player" << std::endl;
				player->SetHealth(player->GetHealth() - 10);
				player->attackClock.restart();

				if (player->GetHealth() <= 0)
				{
					//конец игры или респавн, что по логике реализуем
				}
			}
		}

		// player bullets intersects mobs
		for (auto& playerEntity : player->GetEntites())
		{
			if (entity->Intersect(playerEntity))
			{
				if (Utils::IsType<Entity, Bullet>(playerEntity.get()))
				{
					((Bullet*)playerEntity.get())->SetFlying(false);
					player->SetPoints(player->GetPoints() + 1);
					std::cout << "player bullets intersects mobs" << std::endl;
					/*entity->Erase(1);*/
				}
			}
		}

		// mob bullets intersects player
		if (!entity->GetEntites().empty())
		{
			for (auto& ent : entity->GetEntites())
			{
				if(ent->Intersect(player))
					if (Utils::IsType<Entity, Bullet>(ent.get()))
					{
						std::cout << "mob bullets intersects player" << std::endl;
						((Bullet*)ent.get())->SetFlying(false);
						player->SetHealth(player->GetHealth() - 10);

						if (player->GetHealth() <= 0)
						{
							//конец игры или респавн, что по логике реализуем
						}
					}
			}
		}
	}
}
