#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
public:
	Enemy(const shared_ptr<sf::Sprite>& spr, const shared_ptr<sf::Sound>& snd) : Entity(spr, snd) 
	{
		clock = unique_ptr<sf::Clock>(new sf::Clock());
	}
public:
	void Update(const sf::Time& elapsed) override;
	void SetDirection(const sf::Vector2f& v) { direction = v; }
	void Shoot(const sf::FloatRect& zoneBounds, const shared_ptr<Player>& player);
private:
	unique_ptr<sf::Clock> clock;
	sf::Vector2f velocity{ 0.f, 0.f };
	sf::Vector2f direction{ 0.f, 0.f };
};

