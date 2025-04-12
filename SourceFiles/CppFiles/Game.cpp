#include "../HeaderFiles/Game.h"

Game::Game() : timerText(timerFont), scoreText(scoreFont), currentScoreText(timerFont)
{
    this->remainingTimeToInt = 60;
    this->playerScore = 0;
    this->spawnerTime = 3.0f;
    this->initWindow();
    this->initWorld();
    this->initPlayer();
    this->gameIsRunning = true;
    this->ssTime << "Time left: " << this->remainingTimeToInt;
    this->ssScore << "Score: " << this->playerScore;
    this->initTimerFont();
    this->initTimerText();
    this->initScoreText();
    this->maxNumberChests = 5;
    this->overlayChest = nullptr;
    this->overlayActive = false;
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

bool Game::stillInteracting()
{
    this->player->updateMovement(dt);
    sf::Vector2f velocity = this->player->getVelocity();
    sf::FloatRect playerBounds = this->player->getSprite().getGlobalBounds();
    sf::FloatRect overlayChestBounds = this->overlayChest->getSprite().getGlobalBounds();
    sf::FloatRect nextPos = playerBounds;

    nextPos = playerBounds;
    overlayChestBounds.size.x -= 62.f;
    overlayChestBounds.size.y -= 30.f;
    overlayChestBounds.position.x += 31.f;
    overlayChestBounds.position.y += 15.f;

    nextPos.position.x += velocity.x;
    nextPos.position.y += velocity.y;

    if (nextPos.findIntersection(overlayChestBounds))
    {
        return true;
    }
    return false;
}

void Game::updatePlayer(sf::RenderTarget *target)
{
    this->player->updateMovement(dt);
    sf::Vector2f velocity = this->player->getVelocity();
    sf::FloatRect playerBounds = this->player->getSprite().getGlobalBounds();
    sf::FloatRect nextPos = playerBounds;

    bool collisionHandled = false;

    // std::cout << "Velocity.x: " << velocity.x << " Velocity.y: " << velocity.y << '\n';

    for (auto chest : this->chestsArray)
    {
        sf::FloatRect playerBounds = this->player->getSprite().getGlobalBounds();
        sf::FloatRect chestBounds = chest->getSprite().getGlobalBounds();
        nextPos = playerBounds;
        chestBounds.size.x -= 62.f;
        chestBounds.size.y -= 30.f;
        chestBounds.position.x += 31.f;
        chestBounds.position.y += 15.f;

        nextPos.position.x += velocity.x;
        nextPos.position.y += velocity.y;

        if (nextPos.findIntersection(chestBounds))
        {
            if (velocity.y > 0)
            {
                if (playerBounds.position.y + playerBounds.size.y >= chestBounds.position.y + chestBounds.size.y / 2.f &&
                    playerBounds.position.y + playerBounds.size.y - chestBounds.position.y - chestBounds.size.y / 2.f <= 10.f)
                {
                    this->overlayChest = chest;
                    overlayActive = true;
                }
            }

            // bottom
            else if (velocity.y < 0)
            {
                if (playerBounds.position.y + playerBounds.size.y <= chestBounds.position.y + chestBounds.size.y + 42.f &&
                    chestBounds.position.y + chestBounds.size.y - playerBounds.position.y - playerBounds.size.y <= -30.f)
                {
                    velocity.y = 0;
                    // this->player->setPosition({playerBounds.position.x, chestBounds.position.y + chestBounds.size.y - playerBounds.size.y + 40.f});
                    overlayActive = false;
                }
            }
            // right
            else if (velocity.x > 0)
            {
                if (playerBounds.position.y + playerBounds.size.y <= chestBounds.position.y + chestBounds.size.y + 30.f &&
                    playerBounds.position.y + playerBounds.size.y >= chestBounds.position.y + 20.f)
                {
                    if (playerBounds.position.x + playerBounds.size.x >= chestBounds.position.x)
                    {
                        this->overlayChest = chest;
                        overlayActive = true;
                    }
                }
            }
            // left
            else if (velocity.x < 0)
            {
                if (playerBounds.position.y + playerBounds.size.y <= chestBounds.position.y + chestBounds.size.y + 30.f &&
                    playerBounds.position.y + playerBounds.size.y >= chestBounds.position.y + 20.f)
                {
                    if (playerBounds.position.x <= chestBounds.position.x + chestBounds.size.x)
                    {
                        this->overlayChest = chest;
                        overlayActive = true;
                    }
                }
            }
        }
    }

    if (!overlayActive)
    {
        this->overlayChest = nullptr;
    }
    else
    {
        sf::FloatRect overlayChestBounds = this->overlayChest->getSprite().getGlobalBounds();
        playerBounds = this->player->getSprite().getGlobalBounds();

        overlayChestBounds.size.x += 40.f;
        overlayChestBounds.position.x += 35.f;

        if (velocity.y > 0)
        {
            if (playerBounds.position.y + playerBounds.size.y >= overlayChestBounds.size.y + overlayChestBounds.position.y + 10.f && playerBounds.position.y + playerBounds.size.y - overlayChestBounds.position.y - overlayChestBounds.size.y <= 12.f)
            {
                if (playerBounds.position.x + playerBounds.size.x >= overlayChestBounds.position.x && playerBounds.position.x + playerBounds.size.x <= overlayChestBounds.size.x + overlayChestBounds.position.x)
                {
                    velocity.y = 0;
                }
            }
        }
    }

    this->player->getSprite().move(velocity);
    this->player->updateAnimations();
    this->player->updateCollision(this->window);
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
    this->updatePlayer(this->window);
    if (this->chestsArray.size() < this->maxNumberChests)
    {
        this->chestSpawner();
    }
    if (this->interactWithChest() != nullptr)
    {
        // if player interacts with a chest, we render the animation for that chest
        this->interactWithChest()->update();
    }
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

void Game::renderChests()
{
    for (int i = 0; i < this->chestsArray.size(); i++)
    {
        this->chestsArray[i]->render(*this->window);
    }
}

void Game::render()
{
    this->window->clear(); // First we clean the window

    // Draw world stuff
    this->renderWorld();
    this->renderChests();
    this->renderPlayer();

    if (this->overlayActive && this->stillInteracting())
    {
        this->window->draw(this->overlayChest->getSprite());
    }

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
        dt = dt_clock.restart().asSeconds();
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

// chest
sf::Vector2u Game::avoidCollisionSpawn(Chest *chest, Player *player)
{
    bool ok = false;
    unsigned int pozX;
    unsigned int pozY;
    sf::Vector2u newPosition;
    do
    {
        pozY = this->generateRandomNumber(210, 505);
        pozX = this->generateRandomNumber(2, 1280 - 125);

        chest->setPosition(static_cast<sf::Vector2f>(sf::Vector2u({pozX, pozY})));
        ok = true;

        sf::FloatRect newChestBounds = chest->getSprite().getGlobalBounds();
        sf::FloatRect playerBounds = player->getSprite().getGlobalBounds();

        for (int i = 0; i < this->chestsArray.size(); i++)
        {
            sf::FloatRect chestBounds = this->chestsArray[i]->getSprite().getGlobalBounds();

            if (newChestBounds.findIntersection(chestBounds))
            {
                ok = false;
                break;
            }
        }
        if (ok == true)
        {
            if (newChestBounds.findIntersection(playerBounds))
            {
                ok = false;
            }
        }

    } while (ok == false);

    newPosition.x = pozX;
    newPosition.y = pozY;
    return newPosition;
}

void Game::initChest(int difficulty)
{

    sf::Vector2u chestCoords;

    if (difficulty == 1)
    {
        this->chest = new EasyChest("Textures/Chest/easychest.png", 5, 50.f, 1);
        chestCoords = this->avoidCollisionSpawn(this->chest, this->player);
    }
    else if (difficulty == 2)
    {
        this->chest = new MediumChest("Textures/Chest/mediumchest.png", 10, 30.f, 2);
        chestCoords = this->avoidCollisionSpawn(this->chest, this->player);
    }
    else if (difficulty == 3)
    {
        this->chest = new HardChest("Textures/Chest/hardchest.png", 15, 20.f, 3);
        chestCoords = this->avoidCollisionSpawn(this->chest, this->player);
    }
    // std::cout << chestCoords.x << " " << chestCoords.y << " " << &this->chest << '\n';
    chest->setPosition(static_cast<sf::Vector2f>(chestCoords));
    chestsArray.push_back(chest);
}

void Game::chestSpawner()
{
    if (this->chestsTimer.getElapsedTime().asSeconds() >= this->spawnerTime)
    {
        int generatedType = this->generateChestType();

        this->initChest(generatedType);

        this->chestsTimer.restart();
    }
}

int Game::generateChestType()
{
    // easy chest = spawn chance 50%
    // medium chest = spawn chance 30%
    // hard chest = spawn chance 20%

    int myNumber = this->generateRandomNumber(0, 100);

    if (myNumber <= 50)
    {
        return 1;
    }
    else if (myNumber > 50 && myNumber <= 80)
    {
        return 2;
    }
    else
        return 3;
}

Chest *Game::interactWithChest()
{
    sf::FloatRect playerBounds = this->player->getSprite().getGlobalBounds();
    sf::Vector2f playerCenter = playerBounds.position + playerBounds.size / 2.f;

    for (int i = 0; i < this->chestsArray.size(); i++)
    {
        sf::FloatRect chestBounds = this->chestsArray[i]->getSprite().getGlobalBounds();
        sf::Vector2f chestCenter = chestBounds.position + chestBounds.size / 2.f;

        float dx = playerCenter.x - chestCenter.x;
        float dy = playerCenter.y - chestCenter.y;

        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < 10.f)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                return this->chestsArray[i];
                break;
            }
        }
    }
    return nullptr;
}

// Modern generate random number functions
int Game::generateRandomNumber(int min, int max)
{
    // create a static random device, used only once to seed the generator
    static std::random_device rd;

    // initialize a "Mersenne Twister" random number generator with the random device seed
    static std::mt19937 gen(rd());

    // create an uniform int distribution between given parameters
    // this ensures that every number in the range has an equal chance
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

Game::~Game()
{
    for (int i = 0; i < chestsArray.size(); i++)
    {
        delete this->chestsArray[i];
    }
    delete this->player;
    delete this->front_decor;
    delete this->back_decor;
    delete this->back_land;
    delete this->battleground;
    delete this->background;
    delete this->scoreWindow;
    delete this->window;
}