#include "../HeaderFiles/Paper.h"

Paper::Paper(std::string questionBuffer, sf::RenderTarget *target) : questionText(font), sprite(nullptr), inputText(font)
{
    this->initTexture();
    this->initSprite(target);
    this->questionBuffer = questionBuffer;
    this->initText();
}

void Paper::initTexture()
{
    if (!this->texture.loadFromFile("Textures/PaperSheet/hartie2.png"))
    {
        throw LoadTextureException("Failed to load hartie2.png");
    }
}
void Paper::initSprite(sf::RenderTarget *target)
{
    if (!this->sprite)
    {
        this->sprite = std::make_unique<sf::Sprite>(this->texture);
    }
    this->sprite->setScale({0.5, 0.5});
    sf::Vector2u tPos = target->getSize();
    sf::FloatRect spriteBounds = this->sprite->getGlobalBounds();
    this->sprite->setPosition(sf::Vector2f({tPos.x / 2.f - spriteBounds.size.x / 2.f, tPos.y / 2.f - spriteBounds.size.y / 2.f}));
}

void Paper::initText()
{
    if (!this->font.openFromFile("Fonts/timer.otf"))
    {
        throw LoadFontException("Failed to load timer.otf");
    }
    this->questionText.setFont(this->font);
    this->questionText.setCharacterSize(40);
    this->questionText.setFillColor(sf::Color(100, 0, 0, 255));
    this->questionText.setString(this->questionBuffer);
    sf::FloatRect spriteBounds = this->sprite->getGlobalBounds();
    sf::FloatRect qTextSize = this->questionText.getGlobalBounds();
    this->questionText.setPosition(sf::Vector2f({spriteBounds.position.x + spriteBounds.size.x / 2.f - qTextSize.size.x / 2.f, spriteBounds.position.y + 100.f}));

    this->inputText.setFont(this->font);
    this->inputText.setCharacterSize(30);
    this->inputText.setFillColor(sf::Color(50, 0, 0, 255));
    this->inputText.setString("");
    sf::FloatRect iTextSize = this->inputText.getGlobalBounds();
    this->inputText.setPosition(sf::Vector2f({spriteBounds.position.x + spriteBounds.size.x / 2.f - iTextSize.size.x / 2.f, spriteBounds.position.y + 300.f}));
}

void Paper::render(sf::RenderTarget *target)
{
    target->draw(*this->sprite);
    target->draw(this->questionText);
    sf::FloatRect iTextSize = this->inputText.getGlobalBounds();
    sf::FloatRect spriteBounds = this->sprite->getGlobalBounds();
    this->inputText.setPosition(sf::Vector2f({spriteBounds.position.x + spriteBounds.size.x / 2.f - iTextSize.size.x / 2.f, spriteBounds.position.y + 300.f}));
    target->draw(this->inputText);
}

void Paper::setInputText(std::string myInputText)
{
    this->inputText.setString(myInputText);
}
