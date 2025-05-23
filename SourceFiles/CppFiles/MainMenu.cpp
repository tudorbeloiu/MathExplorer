#include "../HeaderFiles/MainMenu.h"

bool MainMenu::chooseImpossibleType = false;

MainMenu::MainMenu() : optionEng(font), optionRom(font)
{
    initMainMenuVideo();
    initBackgroundTexture();
    initFont();
    initText();
    initPlayer();
    chooseImpossibleType = false;
    pressed = false;
    drawOnlyAbout = false;
    optionLanguage = 0;
    aboutMessageRomanian = "- Pune-ti abilitatile de matematica la incercare in aceasta provocare rapida!\n"
                           "- Aveti 60 de secunde pentru a deschide cat mai multe cufere,\nfiecare afisand o alta intrebare de matematica."
                           "- Cuferele vin in trei niveluri de dificultate:\n"
                           "  =| Easy Chest: adunari si scaderi simple\n"
                           "  =| Cufar mediu: inmultiri si diviziuni cu numere intregi\n"
                           "  =| Hard Chest: ecuatii de gradul doi. Daca discriminantul (D) este negativ, tastati \"imposibil\"\n(indiferent de majuscule).\n"
                           "- Daca D e mai mare decat 0, ambele solutii x1 si x2 vor fi intotdeauna numere intregi,\nintroduceti-le ca x1,x2 cu x1 mai mic decat x2.\n"
                           "- Pentru a deschide un cufar, apasati G. Daca nu cunoasteti raspunsul, trebuie doar\nsa apasati R pentru a merge mai departe;\ncronometrul continua sa ruleze!\n"
                           "- Strangeti cat mai multe puncte si concurati cu prietenii in timp ce va antrenati mintea.\n";

    aboutMessageEnglish =
        "- Put your math skills to the test in this fast-paced challenge!\n"
        "- You have 60 seconds to open as many chests as you can,\neach one asking a different math question.\n"
        "- Chests come in three difficulty levels:\n"
        "  =| Easy Chest: simple additions and subtractions\n"
        "  =| Medium Chest: whole-number multiplications and divisions\n"
        "  =| Hard Chest: quadratic equations.If the discriminant (D) is negative, type \"impossible\"\n(case-insensitive).\n"
        "- If D g.e than 0, both solutions x1 and x2 will always be int numbers,\nenter them as x1,x2 with x1 less than x2.\n"
        "- To open a chest, press G. If you don t know the answer, just press R to skip it\nand move on; the timer keeps running!\n"
        "- Rack up as many points as possible and compete with friends while sharpening your mind.\n                  Good luck!";
}

MainMenu &MainMenu::getInstance()
{
    static MainMenu mainMenu; // unique mainmenu
    return mainMenu;
}

void MainMenu::initMainMenuVideo()
{
    this->MENU = new sf::RenderWindow(sf::VideoMode({800, 600}), "Main menu", sf::Style::Close | sf::Style::Titlebar);
    this->MENU->setFramerateLimit(60);
    this->MENU->setVerticalSyncEnabled(false);
}
void MainMenu::initPlayer()
{
    this->player = PlayerBuilder<Player>().setMovementSpeed(0.f).setPlayerScale({2.7f, 2.7f}).setPlayerVelocity({0.f, 0.f}).setSPoint({30.f, 460.f}).build();
    // this->player = new Player();
    // sf::Vector2u mmBounds = this->MENU->getSize();
    // sf::Vector2f newPlayerPos = {20.f, 470.f};
    // this->player->setPosition(newPlayerPos);
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
                        sf::RenderWindow *ABOUT = new sf::RenderWindow(sf::VideoMode({1366, 768}), "About", sf::Style::Close | sf::Style::Titlebar);

                        this->chooseOption.push_back(optionEng);
                        this->chooseOption.push_back(optionRom);

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

                            sf::Vector2u aboutSize = ABOUT->getSize();
                            sf::FloatRect textBounds = this->chooseOption[0].getGlobalBounds();

                            this->chooseOption[0].setFont(font);
                            this->chooseOption[0].setCharacterSize(40);
                            this->chooseOption[0].setFillColor(sf::Color(128, 0, 0, 255));
                            this->chooseOption[0].setPosition(sf::Vector2f({aboutSize.x / 2.f - 180.f, aboutSize.y / 2.f}));
                            this->chooseOption[0].setString("ENGLISH");

                            this->chooseOption[1].setFont(font);
                            this->chooseOption[1].setCharacterSize(40);
                            this->chooseOption[1].setFillColor(sf::Color::White);
                            this->chooseOption[1].setPosition(sf::Vector2f({aboutSize.x / 2.f + 60.f, aboutSize.y / 2.f}));
                            this->chooseOption[1].setString("ROMANA");

                            aboutText.setFont(aboutFont);
                            aboutText.setCharacterSize(27);
                            aboutText.setFillColor(sf::Color::White);
                            aboutText.setPosition(sf::Vector2f(60.f, 30.f));
                            // aboutText.setOutlineColor(sf::Color::White);
                            // aboutText.setOutlineThickness(2.f);
                        }

                        while (ABOUT->isOpen())
                        {
                            std::optional<sf::Event> aboutEvent;

                            while (aboutEvent = ABOUT->pollEvent())
                            {
                                if (aboutEvent->is<sf::Event::Closed>())
                                {
                                    this->pressed = false;
                                    this->drawOnlyAbout = false;
                                    this->optionLanguage = 0;
                                    ABOUT->close();
                                }
                                if (const auto &keyCodeAbout = aboutEvent->getIf<sf::Event::KeyPressed>())
                                {
                                    if (keyCodeAbout->code == sf::Keyboard::Key::Escape)
                                    {
                                        this->pressed = false;
                                        this->drawOnlyAbout = false;
                                        this->optionLanguage = 0;
                                        ABOUT->close();
                                    }
                                    if (keyCodeAbout->code == sf::Keyboard::Key::Right || keyCodeAbout->code == sf::Keyboard::Key::Left)
                                    {
                                        if (this->optionLanguage == 0)
                                        {
                                            this->optionLanguage = 1;
                                            this->chooseOption[0].setFillColor(sf::Color::White);

                                            this->chooseOption[1].setFillColor(sf::Color(128, 0, 0, 255));
                                        }
                                        else if (this->optionLanguage == 1)
                                        {
                                            this->optionLanguage = 0;
                                            this->chooseOption[1].setFillColor(sf::Color::White);

                                            this->chooseOption[0].setFillColor(sf::Color(128, 0, 0, 255));
                                        }
                                    }
                                    if (keyCodeAbout->code == sf::Keyboard::Key::Enter && this->pressed == false)
                                    {
                                        this->drawOnlyAbout = true;
                                        this->pressed = true;
                                    }
                                }
                            }
                            ABOUT->clear();
                            ABOUT->draw(*aboutBackground);
                            if (this->drawOnlyAbout == false)
                            {
                                for (auto &textOption : chooseOption)
                                {
                                    ABOUT->draw(textOption);
                                }
                            }
                            else
                            {
                                if (this->optionLanguage == 0)
                                {
                                    aboutText.setString(this->aboutMessageEnglish);
                                    this->chooseImpossibleType = false;
                                }
                                else
                                {
                                    aboutText.setString(this->aboutMessageRomanian);
                                    this->chooseImpossibleType = true;
                                }
                                ABOUT->draw(aboutText);
                            }
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
bool MainMenu::getChooseImpossibleType()
{
    return chooseImpossibleType;
}
void MainMenu::update()
{
    this->pollEvents();
    this->player->updateAnimationsForMainMenu();
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
    this->MENU->draw(this->player->getSprite());

    this->MENU->display();
}

const sf::RenderWindow &MainMenu::getMenuWindow() const
{
    return *this->MENU;
}

MainMenu::~MainMenu()
{
    delete this->backgroundSprite;
    delete this->player;
    delete this->MENU;
}