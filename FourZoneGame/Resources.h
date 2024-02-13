#pragma once
#include "library.h"

class Resources
{
public:
	Resources() = delete;
	Resources(const Resources& copy) = delete;
private:
	static std::map<uint32_t, shared_ptr<sf::Texture>> Textures;
	static std::map<uint32_t, shared_ptr<sf::SoundBuffer>> SoundBuffers;
	static std::map<uint32_t, shared_ptr<sf::Font>> Fonts;
public:
	static const char* PLACEHOLDER;
	static void Init();
	static void Clean();

	static shared_ptr<sf::Texture> LoadTexture(const string& name, const string& path, bool smooth = false);
	static shared_ptr<sf::Texture> LoadTexture(const string& name, const sf::Texture* texture, bool smooth = false);
	static shared_ptr<sf::Texture> GetTexture(const string& name);

	static shared_ptr<sf::Sprite>  LoadSprite(const string& name, const string& path);
	static const sf::Sprite*       LoadSpritePtr(const string& name, const string& path);
	static shared_ptr<sf::Sprite>  GetSprite(const string& textureName);

	static shared_ptr<sf::SoundBuffer> LoadSoundBuffer(const string& name, const string& path);
	static shared_ptr<sf::SoundBuffer> GetSoundBuffer(const string& name);
	static shared_ptr<sf::Sound>       LoadSound(const string& name, const string& path);
	static shared_ptr<sf::Sound>       GetSound(const string& name);

	static shared_ptr<sf::Font>       LoadFont(const string& name, const string& path);
	static shared_ptr<sf::Font>       GetFont(const string& name);
};

