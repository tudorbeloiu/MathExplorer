// Beloiu Tudor Andrei - Grupa 132
// Proiect POO
#include "HeaderFiles/MainMenu.h"

int main()
{

    srand(static_cast<unsigned>(time(0))); // Generate the seed for random

    MainMenu mainMenu(800, 600);
    while (mainMenu.getMenuWindow().isOpen())
    {
        // update main menu
        mainMenu.update();

        // render the main menu
        mainMenu.render();
    }

    return 0;
}