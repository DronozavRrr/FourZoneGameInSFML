#pragma once
#include "library.h"

class Utils
{
public:
	Utils() = delete;
public:
    static const double PI;
public:
	static uint32_t Hash(const string& str);

    template<typename T>
    static std::string to_string(const sf::Vector2<T> vector)
    {
        return "[" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + "]";
    }

    static std::string to_string(const sf::FloatRect& rect)
    {
        return "[left : " + std::to_string(rect.left) +
            ", right : " + std::to_string(rect.left + rect.width) + ", top : "
            + std::to_string(rect.top) + ", bottom : " + std::to_string(rect.top + rect.height) + "]";
    }

    static std::string doubleToString(double number, uint32_t precision = 1);

    static sf::Vector2f GetWindowSize(const sf::RenderWindow& window);
    static sf::Vector2u ToVector2u(const sf::Vector2f& v) { return { uint32_t(v.x), uint32_t(v.y)}; }
    static sf::Vector2f ToVector2f(const sf::Vector2u& v) { return { float(v.x), float(v.y) }; }

    // math
    static float        Length(const sf::Vector2f& v);
    static sf::Vector2f Normalize(const sf::Vector2f& v);
    static float        Dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
    static float        Angle(const sf::Vector2f& v1, const sf::Vector2f& v2);
    static float        Angle(const sf::Vector2f& direction);
    static float        ToDegrees(float radians);
    static bool         Contains(const sf::FloatRect& r1, const sf::FloatRect& r2);

    // gets the next random value as a float within the range [ 0.0, 1.0]
    static float Uniliteral();
    // gets the next random value as a float within the range [-1.0, 1.0]
    static float Biliteral();
    // gets the next random value as a float between a specified min and max.
    static float RandomBetween(float min, float max);

    template<typename T, typename V>
    static bool IsType(T* object)
    {
        const auto* ptr = dynamic_cast<V*>(object);
        if (ptr != nullptr)
            return true;

        return false;
    }
};
