#include "Bullet.h"
#include "Utils.h"

void Bullet::Update(const sf::Time& elapsed)
{
	velocity = { 0.f, 0.f };

	// in normalized
	velocity = direction;
	velocity.x *= speed.x;
	velocity.y *= speed.y;

	// todo : 
	const auto& pos = sprite->getPosition();
	if (pos.x < zoneBounds.getPosition().x || pos.y < zoneBounds.getPosition().y || pos.x > zoneBounds.getPosition().x + zoneBounds.width || pos.y > zoneBounds.getPosition().y + zoneBounds.height)
		this->isFlying = false;

	sprite->move(velocity);
}
