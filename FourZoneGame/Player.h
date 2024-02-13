#pragma once
#include "library.h"
#include "Entity.h"

class Zone;

class Player : public Entity
{
public:
	Player() = delete;
	Player(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& snd) : Entity(sprite, snd) {}

	void Update(const sf::Time& elapsed) override;
	void Update(const shared_ptr<Zone>& zone);
	void SetDirection(const sf::Vector2f& dir) { direction = dir; }

	void Shoot(const sf::FloatRect& zoneBounds);

	bool isVisible() const { return Visible; }
	bool isSlliding() const { return Sliding; }
	bool isShooting() const { return Shooting; }

	void SetSliding(bool flag) { Sliding = flag; }
	void SetShooting(bool flag) { Shooting = flag; }
private:
	bool Visible = true;
	bool Sliding = false;
	bool Shooting = false;

	const float  speedFactor{ 0.05f };
	sf::Vector2f velocity{ 0.f, 0.f };
	sf::Vector2f direction{ 0.f, 0.f };
};
