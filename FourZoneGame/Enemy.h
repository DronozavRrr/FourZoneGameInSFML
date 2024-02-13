#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(const shared_ptr<sf::Sprite>& spr, const shared_ptr<sf::Sound>& snd) : Entity(spr, snd) 
	{
		clock = unique_ptr<sf::Clock>(new sf::Clock());
	}
public:
private:
	unique_ptr<sf::Clock> clock;
};

