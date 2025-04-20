#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Game.h"
#include "Exceptions.h"

class MainMenu
{
private:
    sf::RenderWindow *MENU;
    sf::Font font;
    std::vector<sf::Text> mainMenuText;
    std::optional<sf::Event> menuEvent;

    sf::Texture backgroundTexture;
    sf::Sprite *backgroundSprite;

    std::string aboutMessage;

    int mainMenuSelected;

    void initFont();
    void initText();
    void initMainMenuVideo();
    void initBackgroundTexture();

public:
    MainMenu(float width, float height);

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();

    void pollEvents();

    void update();
    void render();
    void renderBackground();

    int mainMenuPressed()
    {
        return this->mainMenuSelected;
    }
    std::string wrapText(sf::Text& aboutText, std::string& input, float maxWidth);

    const sf::RenderWindow &getMenuWindow() const;

    ~MainMenu();
};

#endif