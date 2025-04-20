#include "../HeaderFiles/MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
    this->initMainMenuVideo();
    this->initBackgroundTexture();
    this->initFont();
    this->initText();
    this->aboutMessage =
        "Put your math skills to the test in this fast-paced\nchallenge!\n"
        "You have 60 seconds to open as many chests\nas you can, each one asking a different math\nquestion.\n"
        "Chests come in three difficulty levels:\n"
        "  Easy Chest: simple additions and subtractions\n"
        "  Medium Chest: whole-number multiplications and\ndivisions\n"
        "  Hard Chest: quadratic equations.If the\ndiscriminant (D) is negative, type \"impossible\"\n(case-insensitive).\n"
        "  If D g.e than 0, both solutions x1 and x2 will always be\nint numbers, enter them as x1,x2\nwith x1 less than x2.\n"
        "To open a chest, press G. If you don t know the\nanswer, just press R to skip it and move on;\nthe timer keeps running!\n"
        "Rack up as many points as possible and compete\nwith friends while sharpening your mind.\n                  Good luck!";
}

void MainMenu::initMainMenuVideo()
{
    this->MENU = new sf::RenderWindow(sf::VideoMode({800, 600}), "Main menu", sf::Style::Close | sf::Style::Titlebar);
    this->MENU->setFramerateLimit(60);
    this->MENU->setVerticalSyncEnabled(false);
}

void MainMenu::initBackgroundTexture()
{
    if (!this->backgroundTexture.loadFromFile("Textures/battleground.png"))
    {
        std::cout << "Error initializing background texture!" << '\n';
    }
    else
    {
        this->backgroundSprite = new sf::Sprite(this->backgroundTexture);
    }
}

void MainMenu::initFont()
{
    if (!this->font.openFromFile("Fonts/planes.ttf"))
    {
        std::cout << "Error opening the font!" << '\n';
    }
}

void MainMenu::initText()
{
    this->mainMenuText.clear();
    this->mainMenuText.push_back(sf::Text(this->font, "Play", 50));
    this->mainMenuText.push_back(sf::Text(this->font, "About", 50));
    this->mainMenuText.push_back(sf::Text(this->font, "Exit", 50));

    // Find the middle x in main menu window

    sf::Vector2u menuWindowSize = this->MENU->getSize();
    sf::FloatRect optionSize = this->mainMenuText[0].getGlobalBounds();

    this->mainMenuText[0].setOrigin(sf::Vector2f({optionSize.position.x + optionSize.size.x / 2.f, optionSize.position.y + optionSize.size.y / 2.f}));

    // Play(Game class)
    this->mainMenuText[0].setFillColor(sf::Color(128, 0, 0));
    this->mainMenuText[0].setPosition({menuWindowSize.x / 2.f, 200});

    optionSize = this->mainMenuText[1].getGlobalBounds();
    this->mainMenuText[1].setOrigin(sf::Vector2f({optionSize.position.x + optionSize.size.x / 2.f, optionSize.position.y + optionSize.size.y / 2.f}));

    // About
    this->mainMenuText[1].setFillColor(sf::Color::White);
    this->mainMenuText[1].setPosition({menuWindowSize.x / 2.f, 300});

    optionSize = this->mainMenuText[2].getGlobalBounds();
    this->mainMenuText[2].setOrigin(sf::Vector2f({optionSize.position.x + optionSize.size.x / 2.f, optionSize.position.y + optionSize.size.y / 2.f}));

    // Exit
    this->mainMenuText[2].setFillColor(sf::Color::White);
    this->mainMenuText[2].setPosition({menuWindowSize.x / 2.f, 400});

    this->mainMenuSelected = 0;
}

void MainMenu::draw(sf::RenderWindow &MENU)
{
    for (int i = 0; i < 3; i++)
    {
        MENU.draw(this->mainMenuText[i]);
    }
}

void MainMenu::moveUp()
{
    if (this->mainMenuSelected - 1 >= 0)
    {
        this->mainMenuText[this->mainMenuSelected].setFillColor(sf::Color::White);

        this->mainMenuSelected--;
        if (this->mainMenuSelected == -1)
        {
            this->mainMenuSelected = 2;
        }
        this->mainMenuText[this->mainMenuSelected].setFillColor(sf::Color(128, 0, 0));
    }
}

void MainMenu::moveDown()
{
    if (this->mainMenuSelected + 1 < 3)
    {
        this->mainMenuText[this->mainMenuSelected].setFillColor(sf::Color::White);

        this->mainMenuSelected++;
        if (this->mainMenuSelected == 3)
        {
            this->mainMenuSelected = 0;
        }
        this->mainMenuText[this->mainMenuSelected].setFillColor(sf::Color(128, 0, 0));
    }
}

void MainMenu::pollEvents()
{
    while (this->menuEvent = this->MENU->pollEvent())
    {
        if (this->menuEvent->is<sf::Event::Closed>())
        {
            this->MENU->close();
        }
        if (this->menuEvent->is<sf::Event::KeyReleased>())
        {
            if (const auto &keyCode = this->menuEvent->getIf<sf::Event::KeyReleased>())
            {
                if (keyCode->code == sf::Keyboard::Key::Up)
                {
                    this->moveUp();
                    break;
                }
                if (keyCode->code == sf::Keyboard::Key::Down)
                {
                    this->moveDown();
                    break;
                }
                if (keyCode->code == sf::Keyboard::Key::Enter)
                {
                    int choice = this->mainMenuPressed();

                    if (choice == 0)
                    {
                        Game game;
                        game.run();
                    }
                    if (choice == 1)
                    {
                        sf::RenderWindow *ABOUT = new sf::RenderWindow(sf::VideoMode({800, 600}), "About", sf::Style::Close | sf::Style::Titlebar);

                        sf::Texture aboutBackgroundTexture;
                        sf::Sprite *aboutBackground;

                        if (!aboutBackgroundTexture.loadFromFile("Textures/battleground.png"))
                        {
                            std::cout << "Error opening about background texture!" << '\n';
                        }
                        else
                        {
                            aboutBackground = new sf::Sprite(aboutBackgroundTexture);
                        }

                        sf::Font aboutFont;
                        sf::Text aboutText(aboutFont);
                        if (!aboutFont.openFromFile("Fonts/planes.ttf"))
                        {
                            throw LoadFontException("Failed to load font from Fonts/planes.ttf");
                        }
                        else
                        {
                            aboutText.setFont(aboutFont);
                            aboutText.setCharacterSize(27);
                            aboutText.setOutlineColor(sf::Color(128, 0, 0));
                            aboutText.setOutlineThickness(2.f);
                            aboutText.setPosition(sf::Vector2f({40.f, 10.f}));
                            aboutText.setString(this->aboutMessage);
                        }

                        while (ABOUT->isOpen())
                        {
                            std::optional<sf::Event> aboutEvent;

                            while (aboutEvent = ABOUT->pollEvent())
                            {
                                if (aboutEvent->is<sf::Event::Closed>())
                                {
                                    ABOUT->close();
                                }
                                if (const auto &keyCodeAbout = aboutEvent->getIf<sf::Event::KeyPressed>())
                                {
                                    if (keyCodeAbout->code == sf::Keyboard::Key::Escape)
                                    {
                                        ABOUT->close();
                                    }
                                }
                            }
                            ABOUT->clear();
                            ABOUT->draw(*aboutBackground);
                            ABOUT->draw(aboutText);
                            ABOUT->display();
                        }
                        delete aboutBackground;
                    }
                    if (choice == 2)
                    {
                        MENU->close();
                    }
                    break;
                }
            }
        }
    }
}

void MainMenu::update()
{
    this->pollEvents();
}

void MainMenu::renderBackground()
{
    this->MENU->draw(*this->backgroundSprite);
}

void MainMenu::render()
{
    this->MENU->clear();

    this->renderBackground();
    this->draw(*MENU);

    this->MENU->display();
}

const sf::RenderWindow &MainMenu::getMenuWindow() const
{
    return *this->MENU;
}

MainMenu::~MainMenu()
{
    delete this->backgroundSprite;
    delete this->MENU;
}