#include "DEFINITIONS.hpp"
#include "Maps.hpp"
#include <iostream>
#include <SFML/Window/Sensor.hpp>
#include <SFML/Graphics.hpp>


namespace Zenon {

    Maps::Maps(GameDataRef l_data, const char *name) : m_data(l_data) {

        //Abrimos el mapa e inicializamos las variables que necesitamos
        this->OpenMap(name);

        //Obtemos el numero de capas
        this->NumLayer();

        //Obtenemos GIDs
        this->GetGid();

        //Obtemos las distintas capas mediente los GIDs
        this->GetLayers();

        isDrawed = false;

        this->InitNodeMap();
        //this->GetPath(sf::Vector2f(250,600), sf::Vector2f(380,50));
        //this->GetPath(sf::Vector2f(100,300), sf::Vector2f(500,500));
    }

    void Maps::InitNodeMap() {
        //CREAR EL MAPA DE NODOS E INICIALIZARLO CORRECTAMENTE

        m_nodeMap = new Node ** [_height];
        for (int i = 0; i < _height; i++) {
            m_nodeMap[i] = new Node*[_width];

            for (int j = 0; j < _width; j++) {
                m_nodeMap[i][j] = new Node();
            }
        }

        //Aquí se supone que tengo una matriz de nodos sin inicializar nada

        //Ahora hemos de asignarles las coordenadas a los nodos con las posiciones de los sprites del tilemap
        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                m_nodeMap[i][j]->SetCoordinates(_tilesetSprite[i][j].getPosition());
                if (_tilemap[1][i][j] != 0) {
                    m_nodeMap[i][j]->SetObstacle(true); //Es una pared y esa mierda yo no la quiero evaluar
                }
            }
        }

        //INICIALIZACION DE VECINOS

        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                if (i == 0 && j == 0)//Esquina superior izquierda
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j + 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i + 1][j], 1);
                } else if (i == 0 && j == (_width - 1)) //Esquina superior derecha
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j - 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i + 1][j], 1);
                } else if (i == (_height - 1) && j == 0)//Esquina inferior izquierda
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i - 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j + 1], 1);
                } else if (i == (_height - 1) && j == (_width - 1))//Esquina inferior derecha
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j - 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i - 1][j], 1);
                } else if (i == 0 && j > 0 && j < _width - 1) //Estoy en la primera linea
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j - 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j + 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i + 1][j], 1);
                } else if (i == (_height - 1) && j > 0 && j < _width - 1) //Estoy en la ultima linea
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j - 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j + 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i - 1][j], 1);
                } else if (j == 0 && i > 0 && i < _height - 1) //Estoy en la primera columna
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i + 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i - 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j + 1], 1);
                } else if (j == (_width - 1) && i > 0 && i < _height - 1) //Estoy en la ultima columna
                {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i + 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i - 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j - 1], 1);
                } else {
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i + 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i - 1][j], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j + 1], 1);
                    m_nodeMap[i][j]->AddNeighbor(m_nodeMap[i][j - 1], 1);
                }

            }
        }
    }

    void Maps::ResetNodeMap() {
        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++)
                m_nodeMap[i][j]->ResetNode();
        }
        m_openNodes.clear();
        m_closedNodes.clear();
    }

    bool Maps::IsDrawed() {
        return isDrawed;
    }

    Maps::~Maps() {
    }

    void Maps::Draw() {
        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                m_data->window.draw(_tilesetSprite[i][j]);
                m_data->window.draw(_tilesetParedes[i][j]);
            }
        }

        for (int i = 0; i < m_path.size(); i++) {
            m_data->window.draw(m_path.at(i));
        }
    }

    std::vector<sf::Vector2f> Maps::GetPlacerLocation() {
        std::vector<sf::Vector2f> PlacerLocations;
        objectsLayer = map->FirstChildElement("objectgroup")->FirstChildElement("object");

        int i = 0;

        while (objectsLayer) {
            float x = atof(objectsLayer->Attribute("x"));
            float y = atof(objectsLayer->Attribute("y"));
            PlacerLocations.push_back(sf::Vector2f(x, y));
            objectsLayer = objectsLayer->NextSiblingElement("object");
        }

        return PlacerLocations;
    }

    bool Maps::GetPath(sf::Vector2f l_initPoint, sf::Vector2f l_endPoint, std::vector<sf::Vector2f>& path) {
        this->ResetNodeMap();
        //Ahora toca averiguar en que nodo caen nuestras coordenadas
        
        std::cout<<_height*32<<std::endl;
        std::cout<<l_endPoint.y<<std::endl;
        if(l_endPoint.x<0 || l_endPoint.x>=_width*32 || l_endPoint.y<0 || l_endPoint.y>=_height*32)
        {
            std::cout<<"Mesalgoooo"<<std::endl;
            return false;
        }
        
        Node* startNode = nullptr;
        Node* endNode = nullptr;
        bool validator = false;

        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                if (!validator) {
                    if (this->isMyCoordinate(l_initPoint, m_nodeMap[i][j]->GetCoordinates())) {
                        validator = true;
                        startNode = m_nodeMap[i][j];
                    }
                }
            }
        }

        validator = false;

        for (int i = 0; i < _height; i++) {
            for (int j = 0; j < _width; j++) {
                if (!validator) {
                    if (this->isMyCoordinate(l_endPoint, m_nodeMap[i][j]->GetCoordinates())) {
                        validator = true;
                        endNode = m_nodeMap[i][j];
                    }
                }
            }
        }
        
        if(!validator)
        {
            return false;
        }

        if (endNode->IsObstacle())
            return false;

        if (endNode->GetCoordinates() == startNode->GetCoordinates()) {
            return false;
        }
        //Ya tenemos los nodos puestos, ahora ya podemos realizar el algoritmo de A*

        //ALGORITMO DE A*

        float local_Value, global_Value, heuristic;

        Node *currentNode, *neighborNode;

        std::make_heap(m_openNodes.begin(), m_openNodes.end(), CompareNodes());
        pushOpenNode(startNode);

        while (!m_openNodes.empty()) {
            std::sort(m_openNodes.begin(), m_openNodes.end(), CompareNodes());

            currentNode = m_openNodes.front();
            popOpenNode(currentNode);

            currentNode->SetClosed(true);
            currentNode->SetOpen(false);
            m_closedNodes.push_back(currentNode);

            if (currentNode == endNode) {
                this->ReconstructPath(currentNode, path);
                return true;
            }

            for (const auto& neighbor : currentNode->GetNeighbors()) {
                neighborNode = static_cast<Node*> (neighbor.first);
                local_Value = currentNode->GetLocalValue() + neighbor.second;

                if ((neighborNode->IsOpen() || neighborNode->IsClosed()) && neighborNode->GetLocalValue() <= local_Value) {
                    continue;
                }

                if (neighborNode->IsObstacle()) {
                    continue;
                }

                heuristic = this->distance_heuristic(neighborNode->GetCoordinates(), endNode->GetCoordinates());

                global_Value = heuristic + local_Value;
                neighborNode->Setvalues(global_Value, local_Value);
                neighborNode->SetParent(currentNode);

                if (neighborNode->IsClosed())
                    neighborNode->SetClosed(false);
                if (!neighborNode->IsOpen())
                    pushOpenNode(neighborNode);

            }

        }

        return false;
    }

    void Maps::ReconstructPath(Node* l_lastChild, std::vector<sf::Vector2f>& path) {
        Node* parent = static_cast<Node*> (l_lastChild->GetParent());
        /*
        m_path.clear();
        sf::CircleShape shape(10);
        shape.setFillColor(sf::Color(100, 250, 50));
        shape.setPosition(parent->GetCoordinates());

        m_path.push_back(shape);
         */

        path.push_back(parent->GetCoordinates());
        while (parent != nullptr) {
            /*
            sf::CircleShape shape(10);
            shape.setFillColor(sf::Color(100, 250, 50));
            shape.setPosition(parent->GetCoordinates());
            m_path.push_back(shape);
             * */
            path.push_back(parent->GetCoordinates());
            parent = static_cast<Node*> (parent->GetParent());
        }
    }

    bool Maps::isMyCoordinate(sf::Vector2f l_myCoordinate, sf::Vector2f l_mapNodeCoordinate) {
        float c_substractx = l_mapNodeCoordinate.x - l_myCoordinate.x;
        float c_substracty = l_mapNodeCoordinate.y - l_myCoordinate.y;

        float c_result = std::sqrt(c_substractx * c_substractx + c_substracty * c_substracty);

        if (c_result <= 32.0)
            return true;
        else
            return false;
    }

    void Maps::pushOpenNode(Node* l_node) {
        m_openNodes.push_back(l_node);
        std::push_heap(m_openNodes.begin(), m_openNodes.end(), CompareNodes());
        l_node->SetOpen(true);
    }

    void Maps::popOpenNode(Node* l_node) {
        std::pop_heap(m_openNodes.begin(), m_openNodes.end(), CompareNodes());
        m_openNodes.pop_back();
        l_node->SetOpen(false);
    }

    float Maps::distance_heuristic(sf::Vector2f l_myCoordinate, sf::Vector2f l_endNodeCoordinate) {
        float c_substractx = l_endNodeCoordinate.x - l_myCoordinate.x;
        float c_substracty = l_endNodeCoordinate.y - l_myCoordinate.y;
        float c_result = std::sqrt(c_substractx * c_substractx + c_substracty * c_substracty);
        return c_result;
    }

    void Maps::OpenMap(const char* name) {
        doc.LoadFile(name);
        map = doc.FirstChildElement("map");

        //Alturas y anchuras del mapa y del tile
        map->QueryIntAttribute("width", &_width);
        map->QueryIntAttribute("height", &_height);
        map->QueryIntAttribute("tilewidth", &_tilewidth);
        map->QueryIntAttribute("tileheight", &_tileheigth);

        //Directorio de la imagen
        img = map->FirstChildElement("tileset")->FirstChildElement("image");
        _filename = img->Attribute("source");

        layer = map->FirstChildElement("layer");
        data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        layer2 = map->FirstChildElement("layer");
    }

    void Maps::NumLayer() {
        //Contar el numero de capas
        while (layer) {
            _numLayers++;
            layer = layer->NextSiblingElement("layer");
        }
    }

    void Maps::GetGid() {
        _tilemap = new int** [_numLayers];

        for (int l = 0; l < _numLayers; l++) {
            _tilemap[l] = new int* [_height];
            if (l >= 1)//Para que en la primera capa no lo haga
            {
                layer2 = layer2->NextSiblingElement("layer");
                data[l] = layer2->FirstChildElement("data")->FirstChildElement("tile");
            }
            for (int h = 0; h < _height; h++) {
                _tilemap[l][h] = new int [_width];
                for (int w = 0; w < _width; w++) {
                    _tilemap[l][h][w] = 0;
                    if (data[l] != NULL) {
                        data[l]->QueryIntAttribute("gid", &_tilemap[l][h][w]);
                        data[l] = data[l]->NextSiblingElement("tile");
                    }
                }
            }
        }
    }

    void Maps::GetLayers() {
        _tilemapSprite = new sf::Sprite*** [_numLayers]; //Reservamos primera dimension _tilemapSprite[layer]
        _tilesetSprite = new sf::Sprite* [_height];
        _tilesetParedes = new sf::Sprite* [_height];


        for (int i = 0; i < _height; i++) {
            _tilesetSprite[i] = new sf::Sprite [_width];
            for (int j = 0; j < _width; j++) {
                int gid = _tilemap[0][i][j];
                if (gid > 0) {
                    _tilesetSprite[i][j].setTexture(m_data->assets.GetTexture("TILESET"));
                    _tilesetSprite[i][j].setTextureRect(sf::IntRect(((gid % 16) - 1)*32, (gid / 16)*32, 32, 32));
                    _tilesetSprite[i][j].setPosition(sf::Vector2f(j * 32, i * 32));

                }
            }
        }

        for (int i = 0; i < _height; i++) {
            _tilesetParedes[i] = new sf::Sprite [_width];
            for (int j = 0; j < _width; j++) {
                int gid = _tilemap[1][i][j];
                if (gid > 0) {
                    _tilesetParedes[i][j].setTexture(m_data->assets.GetTexture("TILESET"));
                    _tilesetParedes[i][j].setTextureRect(sf::IntRect(((gid % 16) - 1)*32, (gid / 16)*32, 32, 32));
                    _tilesetParedes[i][j].setPosition(sf::Vector2f(j * 32, i * 32));
                }
            }
        }

    }

}