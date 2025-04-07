#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>

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

    Player *player;

    void initWindow();
    void initPlayer();
    void initWorld();

public:
    Game();

    // Updates
    void update();
    void updatePlayer(const sf::Sprite &back_decor, const sf::Sprite &front_decor, sf::RenderTarget *target);
    void pollEvents();

    // Render
    void render();
    void renderPlayer();
    void renderWorld(); // Everything about background etc

    // Getters
    const sf::RenderWindow &getWindow() const;

    virtual ~Game();
};

#endif