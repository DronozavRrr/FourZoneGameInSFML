#include "Zone.h"
#include "Player.h"

void Zone::Update(const sf::Time& elapsed)
{
	for (auto& entity : entities)
	{
		entity->Update(elapsed);
	}
}

void Zone::Update(const shared_ptr<Player>& player)
{
	
}
