#include "../HeaderFiles/Player.h"

void Player::initTexture()
{
    if (!this->playerTextureIdle.loadFromFile("Textures/Player/idle.png"))
    {
        std::cout << "Error initializing player idle texture!" << '\n';
    }
    if (!this->playerTextureWalk.loadFromFile("Textures/Player/walk.png"))
    {
        std::cout << "Error initializing player walking texture!" << '\n';
    }
}

void Player::initSprite()
{
    this->player = new sf::Sprite(this->playerTextureIdle);
    this->currentFrame = sf::IntRect({0, 3 * 48}, {40, 48}); // Last row, first column
    this->player->setTextureRect(this->currentFrame);
}

void Player::updateAnimationsForMainMenu()
{
    if (this->animationTimer.getElapsedTime().asSeconds() >= this->animationSpeed)
    {
        this->frameIndex++;
        if (this->frameIndex >= 4)
        {
            this->frameIndex = 0;
        }
        this->currentFrame = sf::IntRect({this->frameIndex * 40, 3 * 48}, {40, 48});
        this->player->setTextureRect(this->currentFrame);
        this->animationTimer.restart();
    }
}

void Player::updateAnimations()
{
    if (this->animationTimer.getElapsedTime().asSeconds() >= this->animationSpeed)
    {
        this->frameIndex++;
        if (this->frameIndex >= 4)
        {
            this->frameIndex = 0;
        }
        switch (this->animationState)
        {
        case MOVING_LEFT:
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 0 * 48}, {40, 48});
            break;
        case MOVING_RIGHT:
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 1 * 48}, {40, 48});
            break;
        case MOVING_UP:
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 2 * 48}, {40, 48});
            break;
        case MOVING_DOWN:
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 3 * 48}, {40, 48});
            break;
        default:
            break;
        }
        this->animationTimer.restart();
    }
}

void Player::updateMovement(float dt)
{
    this->velocity.y = 0.f;
    this->velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        this->velocity.x += -this->movementSpeed * dt;
        this->animationState = MOVING_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        this->velocity.x += this->movementSpeed * dt;
        this->animationState = MOVING_RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        this->velocity.y += -this->movementSpeed * dt;
        this->animationState = MOVING_UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        this->velocity.y += this->movementSpeed * dt;
        this->animationState = MOVING_DOWN;
    }
    if (this->velocity == sf::Vector2f(0.f, 0.f))
    {
        this->currentFrame = sf::IntRect({0, 3 * 48}, {40, 48});
        this->player->setTexture(this->playerTextureIdle);
        this->player->setTextureRect(this->currentFrame);
    }
    else
    {
        this->player->setTexture(this->playerTextureWalk);
        this->player->setTextureRect(this->currentFrame);
    }
}

void Player::updateCollision(sf::RenderTarget *target)
{
    sf::FloatRect playerBounds = this->player->getGlobalBounds();

    sf::Vector2f newPos = this->player->getPosition();
    if (playerBounds.position.x <= 113)
    {
        if (playerBounds.position.y <= 160)
            newPos.y = 160;
    }
    else if (playerBounds.position.x > 113 && playerBounds.position.x <= 626)
    {
        if (playerBounds.position.y <= 185)
            newPos.y = 185;
    }
    else if (playerBounds.position.x > 626 && playerBounds.position.x <= 756)
    {
        if (playerBounds.position.y <= 144)
        {
            newPos.y = 144;
        }
    }
    else if (playerBounds.position.x > 756 && playerBounds.position.x <= 948)
    {
        if (playerBounds.position.y <= 172)
            newPos.y = 172;
    }
    else
    {
        if (playerBounds.position.y <= 148)
            newPos.y = 148;
    }

    if (playerBounds.position.x + playerBounds.size.x <= 156)
    {
        if (playerBounds.position.y >= 508)
            newPos.y = 508;
    }
    else if (playerBounds.position.x + playerBounds.size.x > 156 && playerBounds.position.x + playerBounds.size.x <= 196)
    {
        if (playerBounds.position.y >= 524)
            newPos.y = 524;
    }
    else if (playerBounds.position.x + playerBounds.size.x > 196 && playerBounds.position.x + playerBounds.size.x <= 1100)
    {
        if (playerBounds.position.y >= 526)
            newPos.y = 526;
    }
    else
    {
        if (playerBounds.position.y >= 514)
            newPos.y = 514;
    }

    if (playerBounds.position.x + playerBounds.size.x >= target->getSize().x + 20)
    {
        newPos.x = target->getSize().x - playerBounds.size.x + 20;
    }
    if (playerBounds.position.x <= -20.f)
    {
        newPos.x = -20.f;
    }
    this->player->setPosition(newPos);
}

void Player::render(sf::RenderTarget *target)
{
    if (this->player)
    {
        target->draw(*this->player);
    }
}

void Player::setSpawnPoint(sf::Vector2f spawnPoint)
{
    this->player->setPosition(spawnPoint);
}

sf::Sprite &Player::getSprite()
{
    return *this->player;
}

sf::Vector2f Player::getVelocity()
{
    return this->velocity;
}

void Player::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Player::setPosition(sf::Vector2f setPos)
{
    this->player->setPosition(setPos);
}

Player::~Player()
{
    delete this->player;
}
