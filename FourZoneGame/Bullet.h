#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(const shared_ptr<sf::Sprite>& sprite, const shared_ptr<sf::Sound>& snd) : Entity(sprite, snd) {}
	virtual void SetSpeed(const sf::Vector2f& sp) { speed = sp; }
	virtual void SetDirection(const sf::Vector2f& dir) { direction = dir; }
	virtual sf::Vector2f GetDirection() const { return direction; }
	virtual bool IsFlying() const { return isFlying; }
	virtual void SetFlying(bool flag) { isFlying = flag; }
public:
	void Update(const sf::Time& elapsed) override;
protected:
	bool isFlying = true;;

	sf::Vector2f direction{ 0.f, 0.f };
	sf::Vector2f speed{ 2.f, 2.f };
	sf::Vector2f velocity{ 0.f, 0.f };
};

