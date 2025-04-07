#include "../HeaderFiles/MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
    this->initMainMenuVideo();
    this->initFont();
    this->initText();
}

void MainMenu::initMainMenuVideo()
{
    this->MENU = new sf::RenderWindow(sf::VideoMode({800, 600}), "Main menu", sf::Style::Close | sf::Style::Titlebar);
    this->MENU->setFramerateLimit(60);
    this->MENU->setVerticalSyncEnabled(false);
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

    // Play(Game class)
    this->mainMenuText[0].setFillColor(sf::Color(128, 0, 0));
    this->mainMenuText[0].setPosition({350, 200});

    // About
    this->mainMenuText[1].setFillColor(sf::Color::White);
    this->mainMenuText[1].setPosition({350, 300});

    // Exit
    this->mainMenuText[2].setFillColor(sf::Color::White);
    this->mainMenuText[2].setPosition({350, 400});

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
                            ABOUT->display();
                        }
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

void MainMenu::render()
{
    this->MENU->clear();

    this->draw(*MENU);

    this->MENU->display();
}

const sf::RenderWindow &MainMenu::getMenuWindow() const
{
    return *this->MENU;
}

MainMenu::~MainMenu()
{
    delete this->MENU;
}