#ifndef ENDGAME_H
#define ENDGAME_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "Exceptions.h"

class EndGame
{
private:
    sf::RenderWindow *scoreWindow;
    std::optional<sf::Event> scoreWindowEvent;

    sf::Text scoreText;
    sf::Font scoreFont;

    sf::Sprite *backgroundScoreWindow;
    sf::Texture battlegroundTexture;

    void initScoreWindow();

public:
    EndGame();
    EndGame(const EndGame &) = delete;
    EndGame &operator=(const EndGame &) = delete;

    void renderEndGame();
    void renderBackgroundScoreWindow();

    void updateScoreWindow();

    void displayScoreOnWindow();

    sf::RenderWindow *getScoreWindowTarget();

    void initScoreTextAndFontForScoreWindow(int playerScore);
    void initBackgroundScoreWindow();

    virtual ~EndGame();
};

#endif