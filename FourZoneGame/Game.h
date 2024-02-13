#pragma once
#include "library.h"
class Zone;
class Player;

class Game
{
public:
	static enum ZONE_TYPE
	{
		INVISIBLE = 0,
		DYNAMIC = 1,
		STATIC = 2,
		SLIDE = 3
	};
private:
	unique_ptr<sf::RenderWindow> window;
	shared_ptr<Player> player;
	vector<shared_ptr<Zone>> zones;
	unique_ptr<sf::Clock> clock;
public:
	Game() = delete;
	Game(uint32_t width, uint32_t height);
	Game(const Game& g) = delete;
	~Game() = default;

	void Run();
private:
	void Update(const sf::Time& elapsedTime);
	void Draw(const sf::Time& elapsed);
	void DrawFPS(const sf::Time& elapsed);
	void DrawPoints(const shared_ptr<Player>& player);
};

