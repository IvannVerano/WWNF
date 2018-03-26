#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "tinyxml2.h"
#include <vector>


namespace Zenon{
    class Maps {
public:
    Maps(GameDataRef l_data, const char *name);
    ~Maps();
    void Draw();
    bool IsDrawn();
    std::vector<sf::Vector2f> GetPlacerLocation(); 
private:
    int _width;
    int _height;
    int _tilewidth;
    int _tileheigth;
    const char *_filename;
    int _numLayers;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *map;
    tinyxml2::XMLElement *img;
    tinyxml2::XMLElement *layer;
    tinyxml2::XMLElement *layer2;
    tinyxml2::XMLElement *objectsLayer;
    sf::Sprite ****_tilemapSprite;
    int *** _tilemap;
    tinyxml2::XMLElement *data[];
    sf::Texture _tilesetTexture;
    sf::Sprite **_tilesetSprite;
    sf::Sprite **_tilesetParedes;
    bool dibujado;
    GameDataRef m_data;
    
    
    
};
}



