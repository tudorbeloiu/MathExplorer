#include "../HeaderFiles/Player.h"

Player::Player()
{
    this->animationState = IDLE;
    this->initTexture();
    this->initSprite();
    this->playerSpeed = 4.f;
}

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
    this->player->setScale({2.5f, 2.5f});
}

void Player::updateMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->player->move({-this->playerSpeed, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->player->move({this->playerSpeed, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->player->move({0.f, -this->playerSpeed});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->player->move({0.f, this->playerSpeed});
    }
}

void Player::updateCollision(const sf::Sprite& back_decor, const sf::Sprite& front_decor,sf::RenderTarget *target){
    sf::FloatRect playerBounds = this->player->getGlobalBounds();
    sf::FloatRect back_decorBounds = back_decor.getGlobalBounds();
    sf::FloatRect front_decorBounds = front_decor.getGlobalBounds();

    sf::Vector2f newPos = this->player->getPosition();
    if(playerBounds.position.x <= 113){
        if(playerBounds.position.y <= 160)
            newPos.y = 160;
    }
    else if(playerBounds.position.x >113 && playerBounds.position.x <= 626){
        if(playerBounds.position.y <= 185)
            newPos.y = 185;
    }
    else if(playerBounds.position.x >626 && playerBounds.position.x <= 756){
        if(playerBounds.position.y <= 144){
            newPos.y = 144;
        }
    }
    else if(playerBounds.position.x> 756 && playerBounds.position.x <= 948){
        if(playerBounds.position.y <= 172)
            newPos.y = 172;
    }
    else{
        if(playerBounds.position.y <=148)
            newPos.y = 148;
    }
    
    if(playerBounds.position.x + playerBounds.size.x <= 156){
        if(playerBounds.position.y >=508)
            newPos.y = 508;
    }
    else if(playerBounds.position.x + playerBounds.size.x > 156 && playerBounds.position.x + playerBounds.size.x <=196){
        if(playerBounds.position.y >= 524)
            newPos.y = 524;
    }
    else if(playerBounds.position.x + playerBounds.size.x > 196 && playerBounds.position.x + playerBounds.size.x <= 1100){
        if(playerBounds.position.y >= 526)
            newPos.y = 526;
    }
    else{
        if(playerBounds.position.y >=514)
            newPos.y = 514;
    }
    
    if(playerBounds.position.x + playerBounds.size.x >= target->getSize().x+20){
        newPos.x = target->getSize().x - playerBounds.size.x+20;
    }
    if(playerBounds.position.x <= -20.f){
        newPos.x = -20.f;
    }
    this->player->setPosition(newPos);
    std::cout << playerBounds.position.x << " " << playerBounds.position.y << '\n';
    
}

void Player::update(const sf::Sprite& back_decor,const  sf::Sprite& front_decor,sf::RenderTarget *target)
{
    this->updateMovement();
    this->updateCollision(back_decor,front_decor,target);
}

void Player::render(sf::RenderTarget *target)
{
    if (this->player)
    {
        target->draw(*this->player);
    }
}

void Player::setSpawnPoint(sf::Vector2f spawnPoint){
    this->player->setPosition(spawnPoint);
}

Player::~Player()
{
    delete this->player;
}
