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
    MainMenu(); // private constructor to respect Meyers's Singleton
    sf::RenderWindow *MENU;
    sf::Font font;
    std::vector<sf::Text> mainMenuText;
    std::optional<sf::Event> menuEvent;

    sf::Texture backgroundTexture;
    sf::Sprite *backgroundSprite;
    static bool chooseImpossibleType;

    sf::Text optionRom;
    sf::Text optionEng;

    std::vector<sf::Text> chooseOption;
    int optionLanguage = 0;

    bool drawOnlyAbout = false;
    bool pressed = false;

    std::string aboutMessageRomanian;
    std::string aboutMessageEnglish;
    Player *player;

    int mainMenuSelected;

    void initFont();
    void initText();
    void initMainMenuVideo();
    void initBackgroundTexture();
    void initPlayer();

public:
    MainMenu(const MainMenu &) = delete;
    MainMenu &operator=(const MainMenu &) = delete; // delete copy constr and = constr

    static MainMenu &getInstance();

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
    std::string wrapText(sf::Text &aboutText, std::string &input, float maxWidth);

    static bool getChooseImpossibleType();

    const sf::RenderWindow &getMenuWindow() const;

    ~MainMenu();
};

#endif