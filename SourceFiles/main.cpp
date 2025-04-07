#include "HeaderFiles/Game.h"

int main()
{

    srand(static_cast<unsigned>(time(0))); // Generate the seed for random

    Game game;

    while (game.getWindow().isOpen())
    {
        // Game update
        game.update();

        // Game render
        game.render();
    }

    return 0;
}