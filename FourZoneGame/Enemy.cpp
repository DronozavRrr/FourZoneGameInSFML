#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Resources.h"

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

//void Enemy::Shoot(const sf::FloatRect& zoneBounds, const shared_ptr<Player>& player)
//{
//	auto pos = sprite->getTransform().transformPoint(this->GetShotPoint());  // добавить как-то вычисление координат пуль у каждого моба
//	if (!zoneBounds.contains(pos))
//		return;
//
//	if (Shooting)  // реализация стрельбы по времени можно без иф-а, но тогда условие на времени в игровом цикле бахнуть
//	{
//		// load res
//		const auto& sprite = Resources::GetSprite("bullet");
//		const auto& sound = Resources::GetSound("shot");
//
//		auto* bullet = new Bullet(sprite, sound);
//		// define position
//		bullet->SetPosition(pos);
//
//		// other geometry
//		bullet->SetZoneBounds(zoneBounds);
//		bullet->SetDirection(Utils::Normalize(direction));
//		bullet->SclaleRelativeWindow({ 0.01f, 0.01f }, this->zoneBounds.getSize());
//		bullet->SetSpeed({ 1.f, 1.f });
//		// rotate bullet sprite
//		float angle = Utils::ToDegrees(Utils::Angle(direction));
//		bullet->GetSprite()->setRotation(angle);
//		// sound
//		bullet->PlaySound();
//
//		Add(bullet);
//		Shooting = false;
//	}
//}
