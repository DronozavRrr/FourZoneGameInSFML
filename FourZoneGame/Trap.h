#pragma once
#include "Entity.h"
#include "Player.h"

class Trap : public Entity
{
private:
	sf::Vector2f direction{ 0.f, 0.f };
public:
	Trap(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& sound) : Entity(sprite, sound) {}

	void Update(const sf::Time& elapsed) override;
	void SetDirection(const sf::Vector2f& v) { direction = v; }
};

