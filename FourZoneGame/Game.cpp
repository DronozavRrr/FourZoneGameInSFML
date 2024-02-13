#include "Game.h"
#include "Resources.h"
#include "DynamicZone.h"
#include "Utils.h"
#include "Player.h"
#include "SlideZone.h"

Game::Game(uint32_t width, uint32_t height)
{
    window = unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width, height), "Four Zone Game"));
    clock = unique_ptr<sf::Clock>(new sf::Clock());

    Resources::Init();

    // init player
    const auto& playerSprite = Resources::LoadSprite("player texture", "res/img/player.png");
    const auto& shotSound = Resources::LoadSound("shot", "res/sounds/shot2.wav");
    player = shared_ptr<Player>(new Player(playerSprite, shotSound));
    // set origin before any transformation
    player->SetOrigin({ player->GetBounds().getSize().x * 0.5f, player->GetBounds().getSize().y * 0.5f });
    player->SclaleRelativeWindow({ 0.05, 0.05 }, Utils::ToVector2f(window->getSize()));
    player->SetPosition({100, 100});
    player->SetDirection({ 1.f, 0.f });
    player->SetZoneBounds({sf::Vector2f(0.f, 0.f), Utils::GetWindowSize(*window)});
    const auto& localPlayerRect = player->GetLocalBounds();
    player->SetGunPoint({ localPlayerRect.left + localPlayerRect.width * 0.8f, localPlayerRect.top + localPlayerRect.height * 0.7f});

    // init bullet
    Resources::LoadTexture("bullet", "res/img/bullet.png");

    // init zones
    zones.resize(4);
    for (size_t i = 0; i < 3; i++)
    {   
        const auto& sprite = Resources::GetSprite(Resources::PLACEHOLDER);
        sprite->setColor(sf::Color(Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, Utils::Uniliteral() * 255.f, 255));
        const auto& sound = Resources::LoadSound("sound zone " + std::to_string(i), "res/sounds/sound" + std::to_string(i + 1) + ".ogg");
        sound->setVolume(0);
        auto& zone = zones[i];
        zone = shared_ptr<DynamicZone>(new DynamicZone(sprite, sound));
        zone->SclaleRelativeWindow({ 0.5, 0.5 }, Utils::ToVector2f(window->getSize()));
    }

    const auto& windowSize = window->getSize();
    zones[ZONE_TYPE::INVISIBLE]->SetPosition({ 0.f, 0.f });
    zones[ZONE_TYPE::DYNAMIC]->SetPosition({ windowSize.x * 0.5f, 0.f });
    zones[ZONE_TYPE::STATIC]->SetPosition({ 0.f,  windowSize.y * 0.5f });

    // SLIDE ZONE
    auto& slideZone = zones[ZONE_TYPE::SLIDE];
    const auto& sprite = Resources::LoadSprite("slize zone background", "res/img/player.png");
    const auto& sound = Resources::LoadSound("slide zone sound", "res/sounds/sound" + std::to_string(4) + ".ogg");
    slideZone = shared_ptr<SlideZone>(new SlideZone(sprite, sound));
    slideZone->SclaleRelativeWindow({ 0.5, 0.5 }, Utils::ToVector2f(window->getSize()));
    slideZone->SetPosition({ windowSize.x * 0.5f, windowSize.y * 0.5f });
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
                Resources::Clean();
                window->close();            
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
        if (elapsed.asMilliseconds() < 5)
        {
            sf::sleep(sf::milliseconds(5) - elapsed);
            Update(elapsed);
            Draw(elapsed);
        }

      
    }
}

void Game::Update(const sf::Time& elapsed)
{
    for (auto& zone : zones)
    {
        // game logics 
        zone->Update(elapsed);
        player->Update(elapsed);
       
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

    player->Draw(window);

    // draw fps
    DrawFPS(elapsed);

    window->display();
}

void Game::DrawFPS(const sf::Time& elapsed)
{
    sf::Text text(sf::String(" " + std::to_string(elapsed.asMicroseconds()) + " ms"), *Resources::GetFont("font"), 28);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
    window->draw(text);
}
