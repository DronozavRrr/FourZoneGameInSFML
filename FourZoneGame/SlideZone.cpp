#include "SlideZone.h"
#include "Player.h"
#include "Bonus.h"
#include "Resources.h"

void SlideZone::Update(const sf::Time& elapsed)
{

}

void SlideZone::Update(const shared_ptr<Player>& player)
{
	player->SetSliding(true);
	player->SetVisible(true);

	const auto& wbs = GetWindowBouds();
	const auto& pos = player->GetSprite()->getPosition();
	if (pos.x > wbs.x || pos.x < 0.f || pos.y > wbs.y || pos.y < 0.f)
	{
		Resources::LoadGlobalSound("injured")->play();
		player->Kill();
	}

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
