#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Player.h"

class Game
{
private:
    sf::RenderWindow *window;
    sf::VideoMode myScreenSize;
    std::optional<sf::Event> myEvent; // Changed sf::Event logic in SFML 3.0 (now requires optional from std namespace)

    sf::Texture backgroundTexture;
    sf::Sprite *background;

    sf::Texture back_decorTexture;
    sf::Sprite *back_decor;

    sf::Texture battlegroundTexture;
    sf::Sprite *battleground;

    sf::Texture front_decorTexture;
    sf::Sprite *front_decor;

    sf::Texture back_landTexture;
    sf::Sprite *back_land;

    // For cron
    sf::Text timerText;
    sf::Font timerFont;
    sf::Clock gameTimer;
    int remainingTimeToInt;
    float timerSpeed = 1.f;
    bool gameIsRunning = true;
    std::stringstream ssTime;

    sf::RenderWindow *scoreWindow;
    std::optional<sf::Event> scoreWindowEvent;

    sf::Text scoreText;
    sf::Font scoreFont;

    int playerScore;

    sf::Text currentScoreText;
    std::stringstream ssScore;

    Player *player;

    void initWindow();
    void initPlayer();
    void initWorld();
    void initTimerText();
    void initTimerFont();
    void initScoreWindow();
    void initScoreTextAndFontForScoreWindow();
    void initScoreText();

public:
    Game();

    // Updates
    void update();
    void updatePlayer(const sf::Sprite &back_decor, const sf::Sprite &front_decor, sf::RenderTarget *target);
    void updateTimer();
    void pollEvents();
    void updateScoreWindow();

    // Render
    void render();
    void renderPlayer();
    void renderWorld(); // Everything about background etc
    void renderTimerText();
    void renderScoreWindow(); // this one is to render on "Score window"
    void renderScoreText();   // this one is to render on "window"

    // Getters
    const sf::RenderWindow &getWindow() const;
    bool getGameIsRunning();

    void displayScoreOnWindow();
    void run();

    virtual ~Game();
};

#endif