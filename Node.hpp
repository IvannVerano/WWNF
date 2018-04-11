#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace Zenon
{
    class Node
    {
        public:
            Node();
            
            void SetCoordinates(sf::Vector2f l_coordinates);
            
            sf::Vector2f GetCoordinates();
            
            void SetParent(Node* l_parent);
            Node* GetParent() const;
            
            void AddNeighbor(Node* l_neighbor, float l_distance);
            
            void SetOpen(bool l_val);
            void SetClosed(bool l_val);
            bool IsOpen();
            bool IsClosed();
            
            void Setvalues(float l_globalVal, float l_localVal);
            float GetGlobalValue() const;
            float GetLocalValue() const;
            
            void SetObstacle(bool l_value);
            bool IsObstacle();
            
            int HowManyNeighbors();
            std::vector<std::pair<Node*, float>>& GetNeighbors();
            
            void ResetNode();
            
        private:
            sf::Vector2f m_realCoordinates;
            
            float m_globalValue, m_localValue;
            
            Node * m_parent;
            
            std::vector<std::pair <Node*,float>> m_neighbors;
            
            bool m_isOpen, m_isClosed;
            
            bool m_isObstacle;
    };
}