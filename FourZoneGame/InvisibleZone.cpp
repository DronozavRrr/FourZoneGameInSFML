#include "InvisibleZone.h"
#include "Player.h"
#include "Bonus.h"

void InvisibleZone::Update(const shared_ptr<Player>& player)
{
	player->SetVisible(false);
	player->SetSliding(false);

	for (uint32_t i = 0; i < entities.size(); i++)
	{
		auto& entity = entities[i];

		if (entity->Intersect(player))
		{
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
