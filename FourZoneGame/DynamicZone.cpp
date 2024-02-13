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

		}

		// player bullets intersects mobs
		for (auto& playerEntity : player->GetEntites())
		{
			if (entity->Intersect(playerEntity))
			{
				if (Utils::IsType<Entity, Bullet>(playerEntity.get()))
				{
					((Bullet*)playerEntity.get())->SetFlying(false);
				}
				// if type == mob -> points++
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
						((Bullet*)ent.get())->SetFlying(false);
						// player.life--
					}
			}
		}
	}
}
