#include "../HeaderFiles/Game.h"

Game::Game()
{
    this->initWindow();
    this->initWorld();
    this->initPlayer();
}

void Game::initWindow()
{
    // Set game screen size
    myScreenSize = sf::VideoMode({1280, 720});

    // Initialize the window
    this->window = new sf::RenderWindow(myScreenSize, "Math Explorer", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
    this->player = new Player();
    this->player->setSpawnPoint(sf::Vector2f({450.f,500.f}));
}

void Game::initWorld()
{

    // Initialize background with its assets

    sf::Vector2u windowSize = this->window->getSize();

    if (!this->backgroundTexture.loadFromFile("Textures/background.png"))
    {
        std::cout << "Error initializing background texture!" << '\n';
    }
    else
    {
        
        this->background = new sf::Sprite(this->backgroundTexture);

        sf::Vector2u textureSize = this->backgroundTexture.getSize();

        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        float minScale = std::min(scaleX, scaleY);

        this->background->setScale({minScale, minScale});
    }
    if (!this->back_decorTexture.loadFromFile("Textures/back_decor.png"))
    {
        std::cout << "Error initializing back_decor texture!" << '\n';
    }
    else
    {
       
        this->back_decor = new sf::Sprite(this->back_decorTexture);

        sf::Vector2u textureSize = this->back_decorTexture.getSize();

        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        float minScale = std::min(scaleX, scaleY);

        this->back_decor->setScale({minScale, minScale});
    }
    if (!this->battlegroundTexture.loadFromFile("Textures/battleground.png"))
    {
        std::cout << "Error initializing battleground texture!" << '\n';
    }
    else
    {
       
        this->battleground = new sf::Sprite(this->battlegroundTexture);
       
        sf::Vector2u textureSize = this->battlegroundTexture.getSize();

        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        float minScale = std::min(scaleX, scaleY);

        this->battleground->setScale({minScale, minScale});
    }
    if (!this->front_decorTexture.loadFromFile("Textures/front_decor.png"))
    {
        std::cout << "Error initializing front_decor texture!" << '\n';
    }
    else
    {
        
        this->front_decor = new sf::Sprite(this->front_decorTexture);

        sf::Vector2u textureSize = this->front_decorTexture.getSize();

        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        float minScale = std::min(scaleX, scaleY);

        this->front_decor->setScale({minScale, minScale});
    }
    if (!this->back_landTexture.loadFromFile("Textures/back_land.png"))
    {
        std::cout << "Error loading back_land texture!" << '\n';
    }
    else
    {
      
        this->back_land = new sf::Sprite(this->back_landTexture);
       
        sf::Vector2u textureSize = this->back_landTexture.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.x) / textureSize.y;

        float minScale = std::min(scaleX, scaleY);
        this->back_land->setScale({minScale, minScale});
    }
}

void Game::pollEvents()
{
    while (this->myEvent = this->window->pollEvent())
    {
        if (this->myEvent->is<sf::Event::Closed>())
        {
            // If we press the X to close the window, the game stops
            this->window->close();
            break;
        }
        if (const auto &keyCode = this->myEvent->getIf<sf::Event::KeyPressed>())
        {
            if (keyCode->code == sf::Keyboard::Key::Escape)
            {
                this->window->close();
                break;
            }
        }
    }
}

void Game::updatePlayer(const sf::Sprite& back_decor, const sf::Sprite& front_decor,sf::RenderTarget *target)
{
    if (this->player)
    {
        this->player->update(back_decor,front_decor,target);
    }
}

void Game::update()
{
    this->pollEvents();
    this->updatePlayer(*back_decor,*front_decor,this->window);
}

// Render functions

void Game::renderWorld()
{
    this->window->draw(*this->background);
    this->window->draw(*this->battleground); // layer 1
    this->window->draw(*this->back_land);    // this needs to be under the back_decor and on top of battleground
    this->window->draw(*this->back_decor);
    this->window->draw(*this->front_decor);
}

void Game::renderPlayer()
{
    this->player->render(this->window);
}

void Game::render()
{
    this->window->clear(); // First we clean the window

    // Draw world stuff
    this->renderWorld();
    this->renderPlayer();

    // Draw all the stuff

    this->window->display(); // Display the new frame
}

// Getters
const sf::RenderWindow &Game::getWindow() const
{
    return *this->window;
}

Game::~Game()
{
    delete this->player;
    delete this->front_decor;
    delete this->back_decor;
    delete this->back_land;
    delete this->battleground;
    delete this->background;
    delete this->window;
}