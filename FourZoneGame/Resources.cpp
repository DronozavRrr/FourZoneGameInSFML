#include "Resources.h"
#include "Utils.h"

std::map<uint32_t, shared_ptr<sf::Texture>> Resources::Textures = std::map<uint32_t, shared_ptr<sf::Texture>>();
std::map<uint32_t, shared_ptr<sf::SoundBuffer>> Resources::SoundBuffers = std::map<uint32_t, shared_ptr<sf::SoundBuffer>>();
std::map<uint32_t, shared_ptr<sf::Font>> Resources::Fonts = std::map<uint32_t, shared_ptr<sf::Font>>();
std::map<uint32_t, shared_ptr<sf::Sound>> Resources::Sounds = std::map<uint32_t, shared_ptr<sf::Sound>>();


const char* Resources::PLACEHOLDER = "placeholder";

void Resources::Init()
{  
    sf::Texture* placeholder = new sf::Texture();
    if (placeholder->loadFromFile("res/img/placeholder.png") == false)
        std::cout << "Error! Placeholer texture isnt loaded!\n";

    Textures[Utils::Hash(Resources::PLACEHOLDER)] = shared_ptr<sf::Texture>(placeholder);

    // default font
    LoadFont("font", "res/fonts/font.ttf");
}

void Resources::Clean()
{
    Textures.clear();
    SoundBuffers.clear();
    Fonts.clear();
}

shared_ptr<sf::Texture> Resources::LoadTexture(const string& name, const string& path, bool smooth)
{
    uint32_t id = Utils::Hash(name);

    // if texture already exists, return that handle
    if (Resources::Textures.find(id) != Resources::Textures.end())
        return Resources::Textures[id];

    auto* texture = new sf::Texture();
    if(texture->loadFromFile(path) == false)
    {
        std::cout << "Texture at path : " << path << " isnt loaded!\n";
        return Textures[Utils::Hash(Resources::PLACEHOLDER)];
    }

    std::cout << "Texture at path : " << path << " is successfully loaded\n";
    texture->setSmooth(smooth);
    Textures[id] = shared_ptr<sf::Texture>(texture);
    return Textures[id];
}

shared_ptr<sf::Texture> Resources::LoadTexture(const string& name, const sf::Texture* texturePtr, bool smooth)
{
    const shared_ptr<sf::Texture>& texture = GetTexture(name);
    if (texture.get() != nullptr)
    {
        return texture;
    }

    uint32_t id = Utils::Hash(name);
    texture->setSmooth(smooth);
    Textures[id] = texture;
    return Textures[id];
}

shared_ptr<sf::Texture> Resources::GetTexture(const string& name)
{
    uint32_t id = Utils::Hash(name);
    if (Resources::Textures.find(id) != Resources::Textures.end())
        return Resources::Textures[id];
    else
    {
        std::cout << "Texture " << name << " isnt founded!\n";
        return Textures[Utils::Hash(Resources::PLACEHOLDER)];
    }
}

shared_ptr<sf::Sprite> Resources::LoadSprite(const string& name, const string& path)
{
    return shared_ptr<sf::Sprite>(new sf::Sprite(*LoadTexture(name, path)));
}

const sf::Sprite* Resources::LoadSpritePtr(const string& name, const string& path)
{
    return new sf::Sprite(*LoadTexture(name, path));
}

shared_ptr<sf::Sprite> Resources::GetSprite(const string& textureName)
{
    const sf::Texture& texture = *GetTexture(textureName);
    auto* sprite = new sf::Sprite(texture);
    return shared_ptr<sf::Sprite>(sprite);
}

shared_ptr<sf::SoundBuffer> Resources::LoadSoundBuffer(const string& name, const string& path)
{
    uint32_t id = Utils::Hash(name);

    // if texture already exists, return that handle
    if (Resources::SoundBuffers.find(id) != Resources::SoundBuffers.end())
        return Resources::SoundBuffers[id];

    auto* soundBuffer = new sf::SoundBuffer();
    if (soundBuffer->loadFromFile(path) == false)
    {
        std::cout << "SoundBuffer at path : " << path << " isnt loaded!\n";
        // todo : add placeholder for sound
        return shared_ptr<sf::SoundBuffer>();
    }

    std::cout << "SoundBuffer at path : " << path << " is successfully loaded\n";
    SoundBuffers[id] = shared_ptr<sf::SoundBuffer>(soundBuffer);
    return SoundBuffers[id];
}

shared_ptr<sf::SoundBuffer> Resources::GetSoundBuffer(const string& name)
{
    uint32_t id = Utils::Hash(name);
    if (Resources::SoundBuffers.find(id) != Resources::SoundBuffers.end())
        return Resources::SoundBuffers[id];
    else
    {
        std::cout << "SoundBuffer " << name << " isnt founded!\n";
        return shared_ptr<sf::SoundBuffer>();
        // todo :
    }
}

shared_ptr<sf::Sound> Resources::GetSound(const string& name)
{
    return shared_ptr<sf::Sound>(new sf::Sound(*GetSoundBuffer(name)));
}

shared_ptr<sf::Sound> Resources::LoadGlobalSound(const string& name)
{
    uint32_t id = Utils::Hash(name);

    // if texture already exists, return that handle
    if (Resources::Sounds.find(id) != Resources::Sounds.end())
        return Resources::Sounds[id];

    const auto& sound = GetSound(name);
    Sounds[id] = sound;
    return sound;
}


shared_ptr<sf::Sound> Resources::LoadSound(const string& name, const string& path)
{
    return shared_ptr<sf::Sound>(new sf::Sound(*LoadSoundBuffer(name, path)));
}

shared_ptr<sf::Font> Resources::LoadFont(const string& name, const string& path)
{
    uint32_t id = Utils::Hash(name);

    // if texture already exists, return that handle
    if (Resources::Fonts.find(id) != Resources::Fonts.end())
        return Resources::Fonts[id];

    sf::Font* font = new sf::Font();
    if (!font->loadFromFile(path))
    {
        std::cout << "Font at path : " << path << "isnt loaded!\n";
        return shared_ptr<sf::Font>();
    }

    std::cout << "Font at path : " << path << " is successfully loaded\n";
    Fonts[id] = shared_ptr<sf::Font>(font);
    return Fonts[id];
}

shared_ptr<sf::Font> Resources::GetFont(const string& name)
{
    uint32_t id = Utils::Hash(name);
    if (Resources::Fonts.find(id) != Resources::Fonts.end())
        return Resources::Fonts[id];
    else
    {
        std::cout << "Font " << name << " isnt founded!\n";
        return shared_ptr<sf::Font>();
        // todo :
    }
}

