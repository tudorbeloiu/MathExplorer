#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <random>
#include <algorithm>
#include <string>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Chest.h"
#include "Exceptions.h"
#include "EasyChest.h"
#include "MediumChest.h"
#include "HardChest.h"
#include "Paper.h"

class Game
{
private:
    Game(); // private constructor for unique instance
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
    static int remainingTimeToInt;
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

    sf::Sprite *backgroundScoreWindow;

    Player *player;
    sf::Clock dt_clock;
    float dt;

    // Chest implementation in game
    Chest *chest;
    std::vector<Chest *> chestsArray;
    sf::Clock chestsTimer;
    const int spawnerTime = 3.0f;
    const int maxNumberChests = 5;

    Chest *overlayChest;
    bool renderChestOverlay = false;
    bool overlayActive;

    sf::Clock chestAnimationTimer;
    Chest *openChest;

    int chestIsAlreadyOpen;

    // Question spawn
    std::unique_ptr<Paper> questionPaper;
    bool renderNow;
    std::string inputBuffer;
    bool renderWrongAnswer;

    bool disablePlayerMovement = false;
    std::string question;

    void initWindow();
    void initPlayer();
    void initWorld();
    void initTimerText();
    void initTimerFont();
    void initScoreWindow();
    void initScoreTextAndFontForScoreWindow();
    void initScoreText();
    void initBackgroundScoreWindow();
    void initChest(int difficulty);
    void initQuestionPaper(std::string questionText);

public:
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete; // delete constructors

    static Game &getGameInstance(); // unique game instance

    // Updates
    void update();
    void updatePlayer(sf::RenderTarget *target);
    void updateTimer();
    void pollEvents();
    void updateScoreWindow();
    void updateChest();
    void updateScoreText();

    // Render
    void render();
    void renderPlayer();
    void renderWorld(); // Everything about background etc
    void renderTimerText();
    void renderScoreWindow(); // this one is to render on "Score window"
    void renderScoreText();   // this one is to render on "window"
    void renderBackgroundScoreWindow();
    void renderChests();

    // Getters
    const sf::RenderWindow &getWindow() const;
    bool getGameIsRunning();

    void displayScoreOnWindow();
    static int generateRandomNumber(int min, int max);
    int generateChestType();
    void chestSpawner();
    sf::Vector2u avoidCollisionSpawn(Chest *chest, Player *player);

    bool stillInteracting();
    bool interactWithChest();
    void deleteChest(Chest *chest);
    bool validateBuffer(std::string inputText);

    void run();

    virtual ~Game();
};

#endif