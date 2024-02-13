#pragma once
#include "library.h"
#include "Utils.h"

class Entity
{
public:
	Entity() = default;
	Entity(const shared_ptr<sf::Sprite>& spr, const shared_ptr<sf::Sound>& snd) : sprite(spr), sound(snd) {}
	Entity(const Entity& copy) = default;
	virtual ~Entity() = default;

	virtual void Update(const sf::Time& elapsed) {}
	virtual void Draw(const unique_ptr<sf::RenderWindow>& renderer) const
	{
		renderer->draw(*sprite);
		for (const auto& entity : entities)
		{
			entity->Draw(renderer);
		}
	}

	void Erase(size_t index) { entities.erase(entities.begin() + index); }
	void Add(Entity* entity) { entities.push_back(shared_ptr<Entity>(entity)); }
	vector<shared_ptr<Entity>>& GetEntites() { return entities; }

	virtual void                   SetZoneBounds(const sf::FloatRect& bounds);
	virtual sf::FloatRect          GetZoneBounds() const;
	virtual sf::FloatRect          GetBounds() const { return sprite->getGlobalBounds(); }
	virtual sf::FloatRect          GetLocalBounds() const { return sprite->getLocalBounds(); };
	virtual shared_ptr<sf::Sprite> GetSprite() const { return sprite; }
	virtual void                   SetSprite(const shared_ptr<sf::Sprite>& _sprite) { sprite = sprite; }
	virtual void                   SetPosition(const sf::Vector2f& pos) { sprite->setPosition(pos); }
	virtual void                   SetOrigin(const sf::Vector2f& pos) { sprite->setOrigin(pos); }

	virtual sf::Vector2f GetRelativeWindowScale(const sf::Vector2f& windowSize) const;
	virtual void	     SclaleRelativeWindow(const sf::Vector2f& scale, const sf::Vector2f& windowSize);

	virtual bool Intersect(const shared_ptr<Entity>& entity) const;
	virtual bool Contains(const shared_ptr<Entity>& entity) const;

	// Sound
	virtual void SetSound(const shared_ptr<sf::Sound>& s) { sound = s; }
	virtual void PauseSound() { sound->pause(); }
	virtual void PlaySound() { sound->play(); }
	virtual bool IsSoundPlayed() { return (sound->getStatus() == sf::Sound::Playing) ? true : false; }
protected:
	vector<shared_ptr<Entity>> entities;
	shared_ptr<sf::Sprite>     sprite;
	shared_ptr<sf::Sound>      sound;
	sf::FloatRect              zoneBounds{ {0.f, 0.f}, {0.f, 0.f} };
};

