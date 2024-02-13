#include <iostream>
#include "Game.h"
#include <random>

int main()
{
    srand(time(nullptr));

    Game game(1800, 900);
    game.Run();

    return 0;
}
