#include "../HeaderFiles/Paper.h"

Paper::Paper(std::string questionBuffer, sf::RenderTarget *target) : questionText(font), sprite(nullptr)
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
    this->sprite->setScale({0.6, 0.6});
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
    this->questionText.setString(this->questionBuffer);
    sf::FloatRect spriteBounds = this->sprite->getGlobalBounds();
    this->questionText.setPosition(sf::Vector2f({spriteBounds.position.x + spriteBounds.size.x / 4.f, spriteBounds.position.y + 50.f}));
}

void Paper::render(sf::RenderTarget *target)
{
    target->draw(*this->sprite);
}
