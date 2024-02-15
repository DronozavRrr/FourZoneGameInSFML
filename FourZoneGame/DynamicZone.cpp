#include "DynamicZone.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Resources.h"
#include "Bonus.h"

void DynamicZone::Update(const shared_ptr<Player>& player)
{
	player->SetSliding(false);
	player->SetVisible(true);
	player->Shoot(this->GetBounds());

	for (uint32_t i = 0; i < entities.size(); i++)
	{
		auto& entity = entities[i];

		if (Utils::IsType<Entity, Enemy>(entity.get()))
		{
			dynamic_cast<Enemy*>(entity.get())->Shoot(player);
		}

		// mob intersects player
		if (entity->Intersect(player))
		{
			if (Utils::IsType<Entity, Enemy>(entity.get()))
			{
				if (player->attackClock.getElapsedTime() >= player->attackCooldown)
				{
					std::cout << "mob intersects player" << std::endl;
					player->SetHealth(player->GetHealth() - 10);
					player->attackClock.restart();
					Resources::LoadGlobalSound("injured")->play();
				}
			}	

			if (Utils::IsType<Entity, Bonus>(entity.get()))
			{
				((Bonus*)entity.get())->Update(player);
				Erase(i);
				i--;

				continue;
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
					Erase(i);
					i--;

					break;
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
						Resources::LoadGlobalSound("injured")->play();
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

		if (entities.empty())
		{
			break;
		}
	}
}

void DynamicZone::Update(const sf::Time& elapsed)
{
	if (entities.empty())
	{
		this->RandDefaultEnemies(5);
	}

	for (auto& entity : entities)
	{
		entity->Update(elapsed);
	}
}
