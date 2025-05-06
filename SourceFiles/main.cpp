// Beloiu Tudor Andrei - Grupa 132
// Proiect POO
#include "HeaderFiles/MainMenu.h"

int main()
{

    srand(static_cast<unsigned>(time(0))); // Generate the seed for random

    auto &mainMenu = MainMenu::getInstance();
    PlayerBuilder playerBuilder;

    while (mainMenu.getMenuWindow().isOpen())
    {
        // update main menu
        mainMenu.update();

        // render the main menu
        mainMenu.render();
    }

    return 0;
}