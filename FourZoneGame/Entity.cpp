#include "Entity.h"

void Entity::SetZoneBounds(const sf::FloatRect& bounds)
{
	zoneBounds = bounds;
}

sf::FloatRect Entity::GetZoneBounds() const
{
	return zoneBounds;
}

// relative to window size
sf::Vector2f Entity::GetRelativeWindowScale(const sf::Vector2f& windowSize) const
{
	const auto& size = sprite->getGlobalBounds().getSize();
	return { size.x / windowSize.x, size.y / windowSize.y };
}

void Entity::SclaleRelativeWindow(const sf::Vector2f& scale, const sf::Vector2f& windowSize)
{
	const auto& relativeWindowScale = GetRelativeWindowScale(windowSize);
	sprite->setScale((scale.x / relativeWindowScale.x), (scale.y / relativeWindowScale.y));
}

bool Entity::Intersect(const shared_ptr<Entity>& entity) const
{
	if (this->GetBounds().intersects(entity->GetBounds()))
		return true;

	return false;
}

bool Entity::Contains(const shared_ptr<Entity>& entity) const
{
	return Utils::Contains(this->GetBounds(), entity->GetBounds());
}
