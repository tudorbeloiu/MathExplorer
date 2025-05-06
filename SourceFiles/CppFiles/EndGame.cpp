#include "../HeaderFiles/EndGame.h"

EndGame::EndGame() : scoreText(scoreFont)
{
    this->initScoreWindow();
    this->initBackgroundScoreWindow();
}

void EndGame::initScoreWindow()
{
    this->scoreWindow = new sf::RenderWindow(sf::VideoMode({800, 600}), "Your score", sf::Style::Close | sf::Style::Titlebar);
    this->scoreWindow->setFramerateLimit(60);
    this->scoreWindow->setVerticalSyncEnabled(false);
}

void EndGame::initScoreTextAndFontForScoreWindow(int playerScore)
{
    if (!this->scoreFont.openFromFile("Fonts/planes.ttf"))
    {
        throw LoadFontException("Failed to load font from Fonts/planes.ttf");
    }

    this->scoreText.setFont(this->scoreFont);
    this->scoreText.setCharacterSize(76);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setOutlineColor(sf::Color(128, 0, 0, 255));
    this->scoreText.setOutlineThickness(3.5f);

    std::stringstream ss;
    if (playerScore <= 20)
    {
        ss << "You can do better!\n"
           << "Your score: " << playerScore;
    }
    else
    {
        ss << "Congratulations!\n"
           << "Your score: " << playerScore;
    }

    this->scoreText.setString(ss.str());

    sf::Vector2u scoreWindowSize = this->scoreWindow->getSize();

    sf::FloatRect scoreTextBounds = this->scoreText.getGlobalBounds();

    this->scoreText.setOrigin(sf::Vector2f({scoreTextBounds.position.x + scoreTextBounds.size.x / 2.f, scoreTextBounds.position.y + scoreTextBounds.size.y / 2.f}));

    this->scoreText.setPosition(sf::Vector2f({scoreWindowSize.x / 2.f, scoreWindowSize.y / 2.f}));
}

void EndGame::initBackgroundScoreWindow()
{
    if (!this->battlegroundTexture.loadFromFile("Textures/battleground.png"))
    {
        throw LoadTextureException("Error loading texture from Textures/battleground.png");
    }

    this->backgroundScoreWindow = new sf::Sprite(this->battlegroundTexture);
}

void EndGame::renderEndGame()
{
    this->scoreWindow->clear();

    // display the score
    this->renderBackgroundScoreWindow();
    this->displayScoreOnWindow();

    this->scoreWindow->display();
}

void EndGame::renderBackgroundScoreWindow()
{
    this->scoreWindow->draw(*this->backgroundScoreWindow);
}

void EndGame::displayScoreOnWindow() // display the score on Score window
{
    this->scoreWindow->draw(this->scoreText);
}

void EndGame::updateScoreWindow()
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

sf::RenderWindow *EndGame::getScoreWindowTarget()
{
    return this->scoreWindow;
}

EndGame::~EndGame()
{
    delete this->scoreWindow;
    delete this->backgroundScoreWindow;
}