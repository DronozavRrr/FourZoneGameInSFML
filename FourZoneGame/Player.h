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
	sf::Vector2f GetDirection() const { return direction; }

	void Shoot(const sf::FloatRect& zoneBounds);
	void SetGunPoint(const sf::Vector2f& dir) { shotPoint = dir; }
	sf::Vector2f GetShotPoint() const { return shotPoint; }

	bool isVisible() const { return Visible; }
	bool isSlliding() const { return Sliding; }
	bool isShooting() const { return Shooting; }

	void SetSliding(bool flag) { Sliding = flag; }
	void SetShooting(bool flag) { Shooting = flag; }
	
	int GetPoints() { return points; }
	void SetPoints(int point) { this->points = point; }

	int GetHealth() { return health; }
	void SetHealth(int health) { this->health = health; }


	sf::Clock attackClock;
	const sf::Time attackCooldown = sf::seconds(1); // ќпредел€ем интервал в одну секунду между атаками

	sf::Vector2f center;
private:
	bool Visible = true;
	bool Sliding = false;
	bool Shooting = false;

	int points = 0;
	int health = 100;

	const float  speedFactor{ 0.1f };
	sf::Vector2f velocity{ 0.f, 0.f };
	sf::Vector2f direction{ 0.f, 0.f };

	sf::Vector2f shotPoint{ 0.f, 0.f };	
};

