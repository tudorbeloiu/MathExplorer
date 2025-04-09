#include "../HeaderFiles/Game.h"

Game::Game() : timerText(timerFont), scoreText(scoreFont), currentScoreText(timerFont)
{
    this->remainingTimeToInt = 10;
    this->playerScore = 0;
    this->initWindow();
    this->initWorld();
    this->initPlayer();
    this->gameIsRunning = true;
    this->ssTime << "Time left: " << this->remainingTimeToInt;
    this->ssScore << "Score: " << this->playerScore;
    this->initTimerFont();
    this->initTimerText();
    this->initScoreText();
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

void Game::initScoreWindow()
{
    this->scoreWindow = new sf::RenderWindow(sf::VideoMode({800, 600}), "Your score", sf::Style::Close | sf::Style::Titlebar);
    this->scoreWindow->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
    this->player = new Player();
    this->player->setSpawnPoint(sf::Vector2f({450.f, 500.f}));
}

void Game::initScoreTextAndFontForScoreWindow()
{
    if (!this->scoreFont.openFromFile("Fonts/planes.ttf"))
    {
        throw LoadFontException("Failed to load font from Fonts/planes.ttf");
    }

    this->scoreText.setFont(this->scoreFont);
    this->scoreText.setCharacterSize(80);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setOutlineColor(sf::Color(128, 0, 0, 255));
    this->scoreText.setOutlineThickness(3.5f);

    std::stringstream ss;
    ss << "Congratulations!\n"
       << "Your score: " << this->playerScore;

    this->scoreText.setString(ss.str());

    sf::Vector2u scoreWindowSize = this->scoreWindow->getSize();

    sf::FloatRect scoreTextBounds = this->scoreText.getGlobalBounds();

    this->scoreText.setOrigin(sf::Vector2f({scoreTextBounds.position.x + scoreTextBounds.size.x / 2.f, scoreTextBounds.position.y + scoreTextBounds.size.y / 2.f}));

    this->scoreText.setPosition(sf::Vector2f({scoreWindowSize.x / 2.f, scoreWindowSize.y / 2.f}));
}

void Game::initTimerFont()
{
    if (!this->timerFont.openFromFile("Fonts/timer.otf"))
    {
        throw LoadFontException("Failed to load font from Fonts/timer.otf");
    }
}

void Game::initTimerText()
{
    this->timerText.setFont(this->timerFont);
    this->timerText.setFillColor(sf::Color::White);
    this->timerText.setCharacterSize(35);
    this->timerText.setOutlineThickness(2.f);

    this->timerText.setString(ssTime.str());

    this->timerText.setPosition(sf::Vector2f({10.f, 660.f}));
}

void Game::initScoreText()
{
    this->currentScoreText.setFont(this->timerFont);
    this->currentScoreText.setFillColor(sf::Color::White);
    this->currentScoreText.setCharacterSize(35);
    this->currentScoreText.setOutlineThickness(2.f);

    this->currentScoreText.setString(ssScore.str());
    this->currentScoreText.setPosition(sf::Vector2f({1050.f, 660.f}));
}

void Game::initBackgroundScoreWindow()
{
    this->backgroundScoreWindow = new sf::Sprite(this->battlegroundTexture);
}

void Game::initWorld()
{

    // Initialize background with its assets

    sf::Vector2u windowSize = this->window->getSize();

    if (!this->backgroundTexture.loadFromFile("Textures/background.png"))
    {
        throw LoadTextureException("Error loading texture from Textures/background.png");
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
        throw LoadTextureException("Error loading texture from Textures/back_decor.png");
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
        throw LoadTextureException("Error loading texture from Textures/battleground.png");
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
        throw LoadTextureException("Error loading texture from Textures/front_decor.png");
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
        throw LoadTextureException("Error loading texture from Textures/back_land.png");
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

void Game::updatePlayer(const sf::Sprite &back_decor, const sf::Sprite &front_decor, sf::RenderTarget *target)
{
    if (this->player)
    {
        this->player->update(back_decor, front_decor, target);
    }
}

void Game::updateTimer()
{
    if (this->gameTimer.getElapsedTime().asSeconds() >= this->timerSpeed)
    {
        this->remainingTimeToInt--;

        std::stringstream ssTimeNew;
        ssTimeNew << "Time left: " << this->remainingTimeToInt;

        this->timerText.setString(ssTimeNew.str());
        this->gameTimer.restart();
    }
}

void Game::updateScoreWindow()
{
    while (this->scoreWindowEvent = this->scoreWindow->pollEvent())
    {
        if (this->scoreWindowEvent->is<sf::Event::Closed>())
        {
            this->scoreWindow->close();
            break;
        }
        if (const auto &keyCodeWindow = this->scoreWindowEvent->getIf<sf::Event::KeyPressed>())
        {
            if (keyCodeWindow->code == sf::Keyboard::Key::Escape)
            {
                this->scoreWindow->close();
                break;
            }
        }
    }
}

void Game::update()
{
    this->pollEvents();
    this->updatePlayer(*back_decor, *front_decor, this->window);
    if (this->remainingTimeToInt > 0)
    {
        this->updateTimer();
    }
    else
    {
        this->gameIsRunning = false;
    }
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

void Game::renderTimerText()
{
    this->window->draw(this->timerText);
}

void Game::renderScoreText()
{
    this->window->draw(this->currentScoreText);
}

void Game::renderBackgroundScoreWindow()
{
    this->scoreWindow->draw(*this->backgroundScoreWindow);
}

void Game::renderScoreWindow()
{
    this->scoreWindow->clear();

    // display the score
    this->renderBackgroundScoreWindow();
    this->displayScoreOnWindow();

    this->scoreWindow->display();
}

void Game::render()
{
    this->window->clear(); // First we clean the window

    // Draw world stuff
    this->renderWorld();
    this->renderPlayer();

    // Draw all the stuff
    this->renderTimerText();
    this->renderScoreText();

    this->window->display(); // Display the new frame
}

void Game::displayScoreOnWindow() // display the score on Score window
{
    this->scoreWindow->draw(this->scoreText);
}

// Getters
const sf::RenderWindow &Game::getWindow() const
{
    return *this->window;
}

bool Game::getGameIsRunning()
{
    return this->gameIsRunning;
}

void Game::run()
{
    while (this->window->isOpen() && this->gameIsRunning == true)
    {
        this->update();
        this->render();
    }

    if (this->remainingTimeToInt <= 0)
    {
        this->initScoreWindow();
        this->initBackgroundScoreWindow();
        this->initScoreTextAndFontForScoreWindow();
        while (this->scoreWindow->isOpen())
        {
            this->updateScoreWindow();

            this->renderScoreWindow();
        }
        delete this->backgroundScoreWindow;
    }
}

Game::~Game()
{
    delete this->player;
    delete this->front_decor;
    delete this->back_decor;
    delete this->back_land;
    delete this->battleground;
    delete this->background;
    delete this->scoreWindow;
    delete this->window;
}