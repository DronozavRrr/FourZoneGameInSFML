#include "SlideZone.h"
#include "Player.h"

void SlideZone::Update(const sf::Time& elapsed)
{

}

void SlideZone::Update(const shared_ptr<Player>& player)
{
	player->SetSliding(true);
}
