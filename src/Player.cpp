//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Player.h"

#include <iostream>

namespace fastcraft {

    Player::Player(sf::Window &window) : _window(window) {
        _camera = new Camera(window);
        position = glm::vec3(0, 0, 0);
    }

    Player::~Player() {
        delete _camera;
    }

    void Player::handleUpdate(float deltaTime) {
        float speed = 3.0f; // 3 units / second
        float mouseSpeed = 0.005f;

        // Compute new orientation
        _mouse_position = sf::Mouse::getPosition(_window);
        _horizontal_angle -= (_last_mouse_position.x - _mouse_position.x) / 1000.0f;
        _vertical_angle -= (_last_mouse_position.y - _mouse_position.y) / 1000.0f;

        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 _direction = glm::vec3(std::cos(_vertical_angle) * std::sin(_horizontal_angle),
                                         std::sin(_vertical_angle),
                                         std::cos(_vertical_angle) * std::cos(_horizontal_angle));

        // Right vector
        glm::vec3 _right = -glm::vec3(std::sin(_horizontal_angle - 3.14f / 2.0f),
                                     0,
                                     std::cos(_horizontal_angle - 3.14f / 2.0f));

        // Get mouse position
        _last_mouse_position = sf::Mouse::getPosition(_window);
        // sf::Mouse::setPosition(sf::Vector2i(_window.getSize().x / 2, _window.getSize().y / 2), _window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            std::cout << "W" << std::endl;
            position += _direction * deltaTime * speed;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            std::cout << "S" << std::endl;
            position -= _direction * deltaTime * speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            std::cout << "A" << std::endl;
            position -= _right * deltaTime * speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            std::cout << "D" << std::endl;
            position += _right * deltaTime * speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            std::cout << "Space" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            std::cout << "Shift" << std::endl;
        }

        _camera->handleUpdate(position, _direction, _right);
    }

}
