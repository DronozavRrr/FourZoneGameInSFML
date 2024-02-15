#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Resources.h"

void Enemy::Update(const sf::Time& elapsed)
{
	sf::Vector2f speed = { 3.f, 3.f };

	const auto& pos = sprite->getPosition();
	if (pos.x < zoneBounds.getPosition().x || pos.x > zoneBounds.getPosition().x + zoneBounds.width)
		direction.x *= -1.f;
	if (pos.y < zoneBounds.getPosition().y || pos.y > zoneBounds.getPosition().y + zoneBounds.height)
		direction.y *= -1.f;

	velocity.x = speed.x * direction.x;
	velocity.y = speed.y * direction.y;

	sprite->move(velocity);

	// rotation
	float angle = Utils::ToDegrees(Utils::Angle(direction));
	sprite->setRotation(angle);

	// check bullets
	for (uint32_t i = 0; i < entities.size(); i++)
	{
		auto& entity = entities[i];
		entity->Update(elapsed);

		if (Utils::IsType<Entity, Bullet>(entity.get()))
		{
			Bullet* ptr = (Bullet*)(entity.get());
			if (!ptr->IsFlying())
			{
				Erase(i);
				i--;
			}
		}
	}
}

void Enemy::Shoot(const shared_ptr<Player>& player)
{
	auto pos = sprite->getTransform().transformPoint(this->GetGunPoint());  // добавить как-то вычисление координат пуль у каждого моба
	if (!zoneBounds.contains(pos))
		return;

	if (this->getElapsed().asSeconds() > 3)
	{
		// load res
		const auto& sprite = Resources::GetSprite("bullet");
		const auto& sound = Resources::GetSound("shot");

		auto* bullet = new Bullet(sprite, sound);
		// define position
		bullet->SetPosition(pos);
		// other geometry
		bullet->SetZoneBounds(zoneBounds);
		sf::Vector2f dir = player->GetSprite()->getPosition() - pos;
		bullet->SetDirection(Utils::Normalize(dir));
		bullet->SclaleRelativeWindow({ 0.01f, 0.01f }, this->windowBounds);
		// rotate bullet sprite
		float angle = Utils::ToDegrees(Utils::Angle(dir));
		bullet->GetSprite()->setRotation(angle);
		// sound
		bullet->PlaySound();
		Add(bullet);

		this->RestartClock();
	}
}
