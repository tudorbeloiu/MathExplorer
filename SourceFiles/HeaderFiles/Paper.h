#ifndef PAPER_H
#define PAPER_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Exceptions.h"

class Paper
{
private:
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;

    sf::Font font;
    sf::Text questionText;
    sf::Text inputText;
    std::string questionBuffer;

    void initTexture();
    void initSprite(sf::RenderTarget *target);
    void initText();

public:
    Paper(std::string questionBuffer, sf::RenderTarget *target);

    void render(sf::RenderTarget *target);
    void setInputText(std::string myInputText);

    virtual ~Paper() = default;
};

#endif