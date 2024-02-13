#include "Player.h"
#include "Utils.h"
#include "Bullet.h"
#include "Zone.h"
#include "Resources.h"

void Player::Update(const sf::Time& elapsed)
{
	if (!isSlliding())
		velocity = { 0.f, 0.f };

	auto&& temp = elapsed.asMilliseconds() * speedFactor;
	//sf::Vector2f speed = { temp, temp };
	sf::Vector2f speed = { 1.f, 1.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y = -speed.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y = speed.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -speed.x;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = speed.x;
	}

	// check global bounds
	// todo : 
	const auto& pos = sprite->getPosition();
	if (pos.x < 0.f)
		velocity.x = speed.x;
	if (pos.y < 0.f)
		velocity.y = speed.y;
	if (pos.x > zoneBounds.width)
		velocity.x = -speed.y;
	if (pos.y > zoneBounds.height)
		velocity.y = -speed.y;

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

void Player::Shoot(const sf::FloatRect& zoneBounds)
{
	auto pos = sprite->getTransform().transformPoint(this->GetShotPoint());
	if (!zoneBounds.contains(pos))
		return;

	if (Shooting)
	{
		// load res
		const auto& sprite = Resources::GetSprite("bullet");
		const auto& sound = Resources::GetSound("shot");

		auto* bullet = new Bullet(sprite, sound);
		// define position
		bullet->SetPosition(pos);

		// other geometry
		bullet->SetZoneBounds(zoneBounds);
		bullet->SetDirection(Utils::Normalize(direction));
		bullet->SclaleRelativeWindow({ 0.01f, 0.01f }, this->zoneBounds.getSize());
		bullet->SetSpeed({ 1.f, 1.f });
		// rotate bullet sprite
		float angle = Utils::ToDegrees(Utils::Angle(direction));
		bullet->GetSprite()->setRotation(angle);
		// sound
		bullet->PlaySound();

		Add(bullet);
		Shooting = false;
	}
}
