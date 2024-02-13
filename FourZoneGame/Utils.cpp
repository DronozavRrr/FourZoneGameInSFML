#include "Utils.h"

const double Utils::PI = 3.14159265358979323846;


uint32_t Utils::Hash(const string& str)
{
	uint32_t hash = 0;

	for (auto& it : str) 
	{
		hash = 37 * hash + 17 * static_cast<char>(it);
	}

	return hash;
}

float Utils::Uniliteral()
{
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float Utils::Biliteral()
{
    return 2.0f * Uniliteral() - 1.0f;
}

float Utils::RandomBetween(float min, float max)
{
	float t = Uniliteral();
	return (1.0f - t) * min + max * t;
}

sf::Vector2f Utils::GetWindowSize(const sf::RenderWindow& window)
{
	const auto& size = window.getSize();
	return sf::Vector2f(float(size.x), float(size.y));
}

float Utils::Length(const sf::Vector2f& v)
{
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

sf::Vector2f Utils::Normalize(const sf::Vector2f& v)
{
    float length = Length(v);
    return { v.x / length, v.y / length };
}

float Utils::Dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float Utils::Angle(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    const auto& t1 = Normalize(v1);
    const auto& t2 = Normalize(v2);
    float cos = Dot(t1, t2);
    return float(acos(cos));
}

float Utils::Angle(const sf::Vector2f& direction)
{
	return std::atan2f(direction.y, direction.x);
}

float Utils::ToDegrees(float radians)
{
    // Conversion using the conversion factor
    return radians * (180.f / PI);
}

bool Utils::Contains(const sf::FloatRect& r1, const sf::FloatRect& r2)
{
	float left = r1.left;
	float right = r1.left + r1.width;
	float top = r1.top;
	float bottom = r1.top + r1.height;

	bool l = left < r2.left;
	bool r = right > (r2.left + r2.width);
	bool t = top < r2.top;
	bool b = bottom > (r2.top + r2.height);

	return l && r && t && b;
}

sf::FloatRect Utils::GetTransformRect(const shared_ptr<sf::Sprite>& sprite)
{
	sf::FloatRect rect;
	const auto&& local = sprite->getLocalBounds();
	return rect;
}

std::string Utils::doubleToString(double number, uint32_t precision)
{
	std::string str = std::to_string(number);
	return str.substr(0, str.find('.') + 1 + precision);
}

sf::Vector2f Utils::getTranslate(const sf::Transform& transform)
{
	const auto& mat = transform.getMatrix();
	return { mat[12], mat[13] };
}
