#include "Game.h"
#include "Resources.h"
#include "DynamicZone.h"
#include "Utils.h"
#include "Player.h"
#include "SlideZone.h"
#include "Enemy.h"
#include "Trap.h"
#include "StaticZone.h"
#include "InvisibleZone.h"
#include "LifeBonus.h"
#include "PointsBonus.h"
#include <random>

Game::Game(uint32_t width, uint32_t height)
{
    window = unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width, height), "Four Zone Game"));
    clock = unique_ptr<sf::Clock>(new sf::Clock());
    gameTimer = unique_ptr<sf::Clock>(new sf::Clock());
    window->setFramerateLimit(60);

    Resources::Init();
    const auto& windowSize = Utils::ToVector2f(window->getSize());

    // init player
    const auto& playerSprite = Resources::LoadSprite("player texture", "res/img/player.png");
    const auto& shotSound = Resources::LoadSound("shot", "res/sounds/shot2.wav");
    player = shared_ptr<Player>(new Player(playerSprite, shotSound));
    // set origin before any transformation
    player->SetOrigin({ player->GetBounds().getSize().x * 0.5f, player->GetBounds().getSize().y * 0.5f });
    player->SclaleRelativeWindow({ 0.05, 0.05 }, Utils::ToVector2f(window->getSize()));
    player->SetPosition({ Utils::RandomBetween(0.f, (windowSize.x - player->GetBounds().getSize().x)), Utils::RandomBetween(0.f, windowSize.y - player->GetBounds().getSize().y) });
    player->SetDirection({ 1.f, 0.f });
    player->SetZoneBounds({sf::Vector2f(0.f, 0.f), Utils::GetWindowSize(*window)});
    const auto& localPlayerRect = player->GetLocalBounds();
    player->SetGunPoint({ localPlayerRect.left + localPlayerRect.width * 0.8f, localPlayerRect.top + localPlayerRect.height * 0.7f});

    // init bullet
    Resources::LoadTexture("bullet", "res/img/bullet.png");

    //init trap
    Resources::LoadTexture("trap", "res/img/trap.png");
    Resources::LoadSound("dead", "res/sounds/dead.wav");
    Resources::LoadSound("win", "res/sounds/win.wav");
    Resources::LoadSound("injured", "res/sounds/injured.wav");

    // init zones
    zones.resize(4);

    // invisible
    auto& invisibleZone = zones[ZONE_TYPE::INVISIBLE];
    auto sprite = Resources::LoadSprite("invisible sprite", "res/img/invisible_zone.png");
    sprite->setColor(sf::Color(Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, 255));
    auto sound = Resources::LoadSound("invisible sound", "res/sounds/invisible.wav");
    sound->setVolume(10);
    invisibleZone = shared_ptr<InvisibleZone>(new InvisibleZone(sprite, sound));

    // dynamic
    auto& dynamicZone = zones[ZONE_TYPE::DYNAMIC];
    sprite = Resources::LoadSprite("dynamic sprite", "res/img/dynamic_zone.png");
    sprite->setColor(sf::Color(Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, 255));
    sound = Resources::LoadSound("dynamic sound", "res/sounds/dynamic.wav");
    sound->setVolume(10);
    dynamicZone = shared_ptr<DynamicZone>(new DynamicZone(sprite, sound));

    // static 
    auto& staticZone = zones[ZONE_TYPE::STATIC];
    sprite = Resources::LoadSprite("static sprite", "res/img/static_zone.png");
    sprite->setColor(sf::Color(Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, 255));
    sound = Resources::LoadSound("static sound", "res/sounds/static.wav");
    sound->setVolume(10);
    staticZone = shared_ptr<StaticZone>(new StaticZone(sprite, sound));

    // slide zone
    auto& slideZone = zones[ZONE_TYPE::SLIDE];
    sprite = Resources::LoadSprite("slide sprite", "res/img/slide_zone.png");
    sprite->setColor(sf::Color(Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, 255));
    sound = Resources::LoadSound("slide zone", "res/sounds/slide.wav");
    sound->setVolume(10);
    slideZone = shared_ptr<SlideZone>(new SlideZone(sprite, sound));

    std::vector<int> indices = { 0, 1, 2, 3 };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    
    std::vector<sf::Vector2f> positions;
    positions.resize(4);
    positions[0] = { 0.f, 0.f };
    positions[1] = { windowSize.x * 0.5f, 0.f };
    positions[2] = { windowSize.x * 0.5f, windowSize.y * 0.5f };
    positions[3] = { 0.f, windowSize.y * 0.5f };
  
    for (size_t i = 0; i < zones.size(); i++)
    {
        auto& zone = zones[i];
        zone->SclaleRelativeWindow({ 0.5, 0.5 }, Utils::ToVector2f(window->getSize()));
        zone->SetPosition(positions[indices[i]]);
        zone->SetWindowBounds({ windowSize.x, windowSize.y });
        auto bound = zone->GetBounds();

        // bonuses
        uint32_t numLBs = Utils::RandomBetween(1, 3);
        uint32_t numPBs = Utils::RandomBetween(1, 5);
        for (uint32_t j = 0; j < numLBs; j++)
        {
            auto sprite = Resources::LoadSprite("lb", "res/img/lb.png");
            auto sound = Resources::LoadSound("lb sound", "res/sounds/lb.wav");
            sound->setVolume(1);
         
            LifeBonus* lb = new LifeBonus(sprite, sound);
            lb->SclaleRelativeWindow({ 0.03, 0.04 }, Utils::ToVector2f(window->getSize()));
            lb->SetZoneBounds(bound);
            sprite->setPosition(Utils::RandomBetween(bound.left, bound.left + bound.width - sprite->getGlobalBounds().getSize().x), Utils::RandomBetween(bound.top, bound.top + bound.height - sprite->getGlobalBounds().getSize().y));
            zone->Add(lb);
        }

        for (uint32_t j = 0; j < numPBs; j++)
        {
            auto sprite = Resources::LoadSprite("pb", "res/img/pb.png");
            auto sound = Resources::LoadSound("pb sound", "res/sounds/pb.wav");
            sound->setVolume(1);

            PointsBonus* lb = new PointsBonus(sprite, sound);
            lb->SclaleRelativeWindow({ 0.02, 0.03 }, Utils::ToVector2f(window->getSize()));
            lb->SetZoneBounds(bound);
            sprite->setPosition(Utils::RandomBetween(bound.left, bound.left + bound.width - sprite->getGlobalBounds().getSize().x), Utils::RandomBetween(bound.top, bound.top + bound.height - sprite->getGlobalBounds().getSize().y));
            zone->Add(lb);
        }
    }

    // Dynamic Zone
    // enemy
    zones[ZONE_TYPE::DYNAMIC]->RandDefaultEnemies(5);

    //StaticZone
    for (size_t i = 0; i < 8; i++)
    {
        auto bound = zones[ZONE_TYPE::STATIC]->GetBounds();
        const auto& sprite = Resources::GetSprite("trap");
        const auto& sound = Resources::GetSound("shot");
        Trap* trap = new Trap(sprite, sound);
        trap->SclaleRelativeWindow({ 0.05, 0.05 }, Utils::ToVector2f(window->getSize()));
        trap->SetZoneBounds(zones[ZONE_TYPE::STATIC]->GetBounds());
        sprite->setPosition(Utils::RandomBetween(bound.left, bound.left + bound.width - sprite->getGlobalBounds().getSize().x), Utils::RandomBetween(bound.top, bound.top + bound.height - sprite->getGlobalBounds().getSize().y));
        zones[ZONE_TYPE::STATIC]->Add(trap);
    }
}

void Game::Run()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && event.key.code == sf::Keyboard::Escape))
            {
                Close();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                // rotate
                sf::Vector2i posi = sf::Mouse::getPosition(*window);
                sf::Vector2f mpos = { float(posi.x), float(posi.y) };
              
                sf::Vector2f center = player->GetSprite()->getTransform().transformPoint(player->center);                
                player->SetDirection(mpos - player->GetSprite()->getPosition());
            } 

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(!player->isShooting())
                    player->SetShooting(true);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if (player->isShooting())
                    player->SetShooting(false);
            }
        }
        
        sf::Time elapsed = clock->restart();
        Update(elapsed);
        Draw(elapsed);

        if (!player->IsAlive())
        {
            Resources::LoadGlobalSound("dead")->play();;
            DrawMessageBox("player is dead. Points : " + std::to_string(player->GetPoints()));
            Close();
        }

        if (gameTimer->getElapsedTime().asSeconds() > GameTime)
        {
            Resources::LoadGlobalSound("win")->play();
            DrawMessageBox("player is win. Points : " + std::to_string(player->GetPoints()));
            Close();
        }
    }
}

void Game::Update(const sf::Time& elapsed)
{
    player->Update(elapsed);
    for (uint32_t i = 0; i < zones.size(); i++)
    {
        auto& zone = zones[i];
        // game logics 
        zone->Update(elapsed);
       
        if (zone->Intersect(player))
        {
            zone->Update(player);     
        }   

        if (zone->Contains(player))
        {
            if (!zone->IsSoundPlayed())
                zone->PlaySound();
        }
        else
            zone->PauseSound();
        // todo : add bounds music
    } 
}

void Game::Draw(const sf::Time& elapsed)
{
    window->clear();

    for (auto& zone : zones)
    {
        zone->Draw(window);
    }

    if(player->isVisible())
        player->Draw(window);

    // draw 
    DrawPointsAndHealth(player, elapsed);

    window->display();
}

void Game::DrawPointsAndHealth(const shared_ptr<Player>& player, const sf::Time& elapsed)
{
    int health = player->GetHealth();
    sf::Text text(sf::String(std::to_string(health) + "% hp"), *Resources::GetFont("font"), 28);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    const auto& wp = Utils::ToVector2f(window->getSize());
    text.setPosition({ wp.x * 0.01f, wp.y * 0.01f });
    window->draw(text);
    int points = player->GetPoints();
    sf::Text text2(sf::String(std::to_string(points) + " points"), *Resources::GetFont("font"), 28);
    text2.setFillColor(sf::Color::Yellow);
    text2.setStyle(sf::Text::Bold);
    text2.setPosition(text.getGlobalBounds().getPosition().x + text.getGlobalBounds().width + wp.x * 0.01f, wp.y * 0.01f);
    window->draw(text2);

    sf::Text text3(sf::String(Utils::doubleToString(GameTime - gameTimer->getElapsedTime().asSeconds()) + " s left."), *Resources::GetFont("font"), 28);
    text3.setFillColor(sf::Color::Yellow);
    text3.setStyle(sf::Text::Bold);
    text3.setPosition(wp.x * 0.8f, wp.y * 0.01f);
    window->draw(text3);

    sf::Text text4(sf::String(" " + std::to_string(elapsed.asMilliseconds()) + " ms"), *Resources::GetFont("font"), 28);
    text4.setFillColor(sf::Color::Green);
    text4.setStyle(sf::Text::Bold);
    text4.setPosition(text3.getGlobalBounds().getPosition().x + text3.getGlobalBounds().width + wp.x * 0.01f, wp.y * 0.01f);

    window->draw(text4);
}

void Game::DrawMessageBox(const std::string& str)
{
    MessageBoxA(NULL, str.c_str(), "Game!!", MB_OKCANCEL | MB_ICONEXCLAMATION);
}

void Game::Close()
{
    Resources::Clean();
    window->close();
}

