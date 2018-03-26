#include "DEFINITIONS.hpp"
#include "Maps.hpp"
#include <iostream>
#include <SFML/Window/Sensor.hpp>
#include <SFML/Graphics.hpp>


namespace Zenon{
Maps::Maps(GameDataRef l_data, const char *name):m_data(l_data)
{
    std::cout<<"Se crea un mapa "<<std::endl;
    doc.LoadFile(name);
    map=doc.FirstChildElement("map");
    
    //Alturas y anchuras del mapa y del tile
    map->QueryIntAttribute("width",&_width);
    map->QueryIntAttribute("height",&_height);
    map->QueryIntAttribute("tilewidth",&_tilewidth);   
    map->QueryIntAttribute("tileheight",&_tileheigth);
    
    //Directorio de la imagen
    img=map->FirstChildElement("tileset")->FirstChildElement("image");
    _filename = img->Attribute("source");
    std::cout<<_filename<<std::endl;
    
    layer=map->FirstChildElement("layer");
    
    //Contar el numero de capas
    while(layer)
    {
        _numLayers++;
        layer=layer->NextSiblingElement("layer");
        std::cout<<"Capas: "<<_numLayers<<std::endl;
    }
    
    data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    layer2=map->FirstChildElement("layer");
    _tilemap = new int** [_numLayers];

    
    
    for (int l=0; l<_numLayers;l++)
    {
        _tilemap[l] = new int* [_height];
        if(l>=1)//Para que en la primera capa no lo haga
        {
            layer2 = layer2->NextSiblingElement("layer");
            data[l] = layer2->FirstChildElement("data")->FirstChildElement("tile");
        }
        for(int h=0;h<_height;h++)
        {
            _tilemap[l][h] = new int [_width]; 
            for(int w=0; w<_width;w++)
            {
                _tilemap[l][h][w] = 0;
                data[l]->QueryIntAttribute("gid",&_tilemap[l][h][w]);
                data[l] = data[l]->NextSiblingElement("tile");
            }
        }
    }
    
    _tilemapSprite = new sf::Sprite*** [_numLayers]; //Reservamos primera dimension _tilemapSprite[layer]
    m_data->assets.LoadTexture("Tileset", TILESET_FILEPATH);
    _tilesetTexture = m_data->assets.GetTexture("Tileset");
    
    _tilesetSprite = new sf::Sprite* [_height];
    _tilesetParedes = new sf::Sprite* [_height];
    
    for(int i=0; i<_height;i++){
        _tilesetSprite[i] = new sf::Sprite [_width];
        for(int j=0;j<_width;j++)
        {
            int gid = _tilemap[0][i][j];
            if(gid!=0)
            {
                std::cout<<gid<<std::endl;
                _tilesetSprite[i][j].setTexture(_tilesetTexture);
                std::cout<<"Estoy pintando en: "<<gid/16<<" y "<<gid%16<<std::endl;
                _tilesetSprite[i][j].setTextureRect(sf::IntRect(((gid%16)-1)*32,(gid/16)*32,32,32));
                _tilesetSprite[i][j].setPosition(sf::Vector2f(j*32,i*32));
            }
        }
    }
    
    for(int i=0; i<_height;i++){
        _tilesetParedes[i] = new sf::Sprite [_width];
        for(int j=0;j<_width;j++)
        {
            int gid = _tilemap[1][i][j];
            if(gid!=0)
            {
                std::cout<<gid<<std::endl;
                _tilesetParedes[i][j].setTexture(_tilesetTexture);
                std::cout<<"Estoy pintando en: "<<gid/16<<" y "<<gid%16<<std::endl;
                _tilesetParedes[i][j].setTextureRect(sf::IntRect(((gid%16)-1)*32,(gid/16)*32,32,32));
                _tilesetParedes[i][j].setPosition(sf::Vector2f(j*32,i*32));
            }
        }
    }
    

    dibujado = false;
    
}

Maps::~Maps()
{
}

void Maps::Draw()
{
    if(!dibujado)
    {
        for(int i=0;i<_height;i++){
            for(int j=0;j<_width;j++){
                m_data->window.draw(_tilesetSprite[i][j]);
                m_data->window.draw(_tilesetParedes[i][j]);
            }
        }
        std::cout<<"Dibujo el mapa"<<std::endl;
        dibujado = true;
    }
}

bool Maps::IsDrawn()
{
    return dibujado;
}

std::vector<sf::Vector2f> Maps::GetPlacerLocation()
{
    std::vector<sf::Vector2f> PlacerLocations;
    objectsLayer = map->FirstChildElement("objectgroup")->FirstChildElement("object");
    
    int i = 0;
    
    while(objectsLayer)
    {
        float x = atof(objectsLayer->Attribute("x"));
        float y = atof(objectsLayer->Attribute("y"));
        PlacerLocations.push_back(sf::Vector2f(x,y));
        objectsLayer = objectsLayer->NextSiblingElement("object");
    }
    
    return PlacerLocations;
}

}
