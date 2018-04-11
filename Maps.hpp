#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "tinyxml2.hpp"
#include "Node.hpp"
#include <vector>
#include <stack>
#include <algorithm>


namespace Zenon {
    
    struct CompareNodes 
    {
        bool operator()(const Node* l_node1, const Node* l_node2) const 
        {
            return l_node1->GetGlobalValue() < l_node2->GetGlobalValue();
        }
    };
    
    
    class Maps {
    public:
        Maps(GameDataRef l_data, const char *name);
        ~Maps();
        void Draw();
        std::vector<sf::Vector2f> GetPlacerLocation();
        bool IsDrawed();
        
        //Funciones de A*
        bool GetPath(sf::Vector2f l_initPoint, sf::Vector2f l_endPoint, std::vector<sf::Vector2f>& path);
        void ReconstructPath(Node* l_lastChild, std::vector<sf::Vector2f>& path); 
        
        bool isMyCoordinate(sf::Vector2f l_myCoordinate, sf::Vector2f l_mapNodeCoordinate);
        void pushOpenNode(Node * l_node);
        void popOpenNode(Node * l_node);
        float distance_heuristic(sf::Vector2f l_myCoordinate, sf::Vector2f l_endNodeCoordinate);
        
        void InitNodeMap();
        void ResetNodeMap();
;
        
    private:
        GameDataRef m_data;
        int _width;
        int _height;
        int _tilewidth;
        int _tileheigth;
        const char *_filename;
        int _numLayers = 0;
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
        bool isDrawed;
        
        std::vector<Node*>m_openNodes;
        std::vector<Node*>m_closedNodes;
        
        std::vector<sf::CircleShape> m_path;
        
        Node *** m_nodeMap;
        
    };
}


