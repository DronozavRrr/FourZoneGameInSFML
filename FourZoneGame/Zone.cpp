#include "Zone.h"
#include "Player.h"
#include "Resources.h"
#include "Enemy.h"

void Zone::Update(const sf::Time& elapsed)
{
	for (auto& entity : entities)
	{
		entity->Update(elapsed);
	}
}

void Zone::Update(const shared_ptr<Player>& player)
{
	
}

void Zone::RandDefaultEnemies(uint32_t count)
{
	for (size_t i = 0; i < count; i++)
	{
        auto bounds = GetBounds();
        const auto& sprite = Resources::GetSprite("player texture");
        sprite->setOrigin({ sprite->getGlobalBounds().getSize().x * 0.5f, sprite->getGlobalBounds().getSize().y * 0.5f });
        sprite->setPosition(Utils::RandomBetween(bounds.left, bounds.left + bounds.width), Utils::RandomBetween(bounds.top, bounds.top + bounds.height));
        sprite->setColor(sf::Color(Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, 255));
        const auto& sound = Resources::GetSound("shot");
        Enemy* enemy = new Enemy(sprite, sound);
        enemy->SclaleRelativeWindow({ 0.05, 0.05 }, windowBounds);
        enemy->SetZoneBounds(bounds);
        enemy->SetWindowBounds(windowBounds);
        enemy->SetDirection({ Utils::Uniliteral(), Utils::Uniliteral() });
        enemy->StartClock();
        const auto& localRect = sprite->getLocalBounds();
        enemy->SetGunPoint({ localRect.left + localRect.width * 0.8f, localRect.top + localRect.height * 0.7f });
        Add(enemy);
	}
}
