#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

namespace Zenon {

    void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

<<<<<<< HEAD
    sf::Font &AssetManager::GetFont(std::string name) {
        return this->_fonts.at(name);
    }

    void AssetManager::LoadBuffer(std::string name, std::string fileName) {
        sf::SoundBuffer buffer;

        if (buffer.loadFromFile(fileName)) {
            this->m_buffers[name] = buffer;
        }
    }

    sf::SoundBuffer& AssetManager::GetBuffer(std::string name) {
        return this->m_buffers.at(name);
    }
=======
	sf::Font &AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
>>>>>>> eb2f958d50a72c57f68e71ec1fe5e69ae78d0e7c
}