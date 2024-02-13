#include "Enemy.h"

void Enemy::Update(const sf::Time& elapsed)
{
	sf::Vector2f speed = { 1.f, 1.f };
	
	// check global bounds
	// todo : 
	const auto& pos = sprite->getPosition();
	if (pos.x < zoneBounds.getPosition().x || pos.x > zoneBounds.getPosition().x + zoneBounds.width)
		direction.x *= -1.f;
	if (pos.y < zoneBounds.getPosition().y || pos.y > zoneBounds.getPosition().y + zoneBounds.height)
		velocity.y *= -1.f;

	velocity.x = speed.x * direction.x;
	velocity.y = speed.y * direction.y;

	sprite->move(velocity);

	// rotation
	float angle = Utils::ToDegrees(Utils::Angle(direction));
	sprite->setRotation(angle);
}
