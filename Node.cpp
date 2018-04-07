#include "Node.hpp"

namespace Zenon
{
    Node::Node():m_parent(nullptr)
    {
        m_globalValue = 0.0;
        m_localValue = 0.0;
        m_isOpen = false;
        m_isClosed = false;
        m_isObstacle = false;
    }
    
    std::vector<std::pair<Node*, float>>& Node::GetNeighbors()
    {
	return m_neighbors;
    }   
    
    void Node::SetCoordinates(sf::Vector2f l_coordinates)
    {
        m_realCoordinates = l_coordinates;
    }
    sf::Vector2f Node::GetCoordinates()
    {
        return m_realCoordinates;
    }
    
    void Node::SetParent(Node* l_parent)
    {
        m_parent = l_parent;
    }
    
    Node* Node::GetParent() const
    {
        return m_parent;
    }
    
    void Node::SetOpen(bool l_val)
    {
        m_isOpen = l_val;
    }
    void Node::SetClosed(bool l_val)
    {
        m_isClosed = l_val;
    }
    bool Node::IsOpen()
    {
        return m_isOpen;
    }
    bool Node::IsClosed()
    {
        return m_isClosed;
    }
    
    void Node::Setvalues(float l_globalVal, float l_localVal)
    {
        m_localValue = l_localVal;
        m_globalValue = l_globalVal;
    }
    float Node::GetGlobalValue() const
    {
        return m_globalValue;
    }
    float Node::GetLocalValue() const
    {
        return m_localValue;
    }
    
    void Node::AddNeighbor(Node* l_neighbor, float l_distance)
    {
        m_neighbors.push_back(std::make_pair(l_neighbor, l_distance));
    }
    
    void Node::SetObstacle(bool l_value)
    {
        m_isObstacle = l_value;
    }
    bool Node::IsObstacle()
    {
        return m_isObstacle;
    }
    
    int Node::HowManyNeighbors()
    {
        return m_neighbors.size();
    }
    
    void Node::ResetNode()
    {
        m_globalValue = 0.0;
        m_localValue = 0.0;
        m_isOpen = false;
        m_isClosed = false;
        m_parent = nullptr;
    }
    
}