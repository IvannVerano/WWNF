#include "InputManager.hpp"

namespace Zenon {

    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window) {
        if (sf::Mouse::isButtonPressed(button)) {
            sf::IntRect playButtonRect(object.getGlobalBounds());

            if (playButtonRect.contains(sf::Mouse::getPosition(window))) {
                return true;
            }
        }

        return false;
    }
    
     bool InputManager::IsSpriteHovered(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window) {
            
         sf::IntRect playButtonRect(object.getGlobalBounds());

         if (playButtonRect.contains(sf::Mouse::getPosition(window))) {
                return true;
            }

        return false;
    }

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) {
        return sf::Mouse::getPosition(window);
    }
}