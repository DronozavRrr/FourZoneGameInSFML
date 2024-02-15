#include "Trap.h"
#include "Player.h"
#include "Bullet.h"
#include "Resources.h"

void Trap::Update(const sf::Time& elapsed)
{
	const auto& pos = sprite->getPosition();
	if (pos.x < zoneBounds.getPosition().x || pos.x > zoneBounds.getPosition().x + zoneBounds.width)
		direction.x *= -1.f;
}