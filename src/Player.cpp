//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Player.h"

#include <iostream>

namespace fastcraft {

    Player::Player(Camera *camera, sf::Window &window) : _camera(camera), _window(window) {

    }

    Player::~Player() {
        delete _camera;
    }

    void Player::handleUpdate(float deltaTime) {
        /*
        // Initial position : on +Z
        glm::vec3 position = glm::vec3( 0, 0, 5 );
        // Initial horizontal angle : toward -Z
        float horizontalAngle = 3.14f;
        // Initial vertical angle : none
        float verticalAngle = 0.0f;
        // Initial Field of View
        float initialFoV = 45.0f;

        float speed = 3.0f; // 3 units / second
        float mouseSpeed = 0.005f;

        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(_window);
        float _horizontal_angle = 0.f;
        float _vertical_angle = 0.f;



        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::highp_vec3 _direction = glm::vec3(std::cos(_vertical_angle) * std::sin(_horizontal_angle),
                                               std::sin(_vertical_angle),
                                               std::cos(_vertical_angle) * std::cos(_horizontal_angle));

        // Right vector
        glm::highp_vec3 _right = glm::vec3(std::sin(_horizontal_angle - 3.14f / 2.0f),
                                           0,
                                           std::cos(_horizontal_angle - 3.14f / 2.0f));

        // Up vector
        glm::highp_vec3 _up = glm::cross(_right, _direction);

        glm::mat4 view;
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                           glm::vec3(0.0f, 0.0f, 0.0f) + _direction,
                           _up);

        // Get mouse position
        double xpos, ypos;
        sf::Mouse::setPosition(sf::Vector2i(_window.getSize().x / 2, _window.getSize().y / 2), _window);
        lastMousePosition = sf::Mouse::getPosition(_window);

        // Compute new orientation
        _horizontal_angle += (lastMousePosition.x - currentMousePosition.x) / 1000.0f;
        _vertical_angle -= (lastMousePosition.y - currentMousePosition.y) / 1000.0f;

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

        float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        ViewMatrix = glm::lookAt(
                position,           // Camera is here
                position+_direction, // and looks here : at the same position, plus "direction"
                _up                  // Head is up (set to 0,-1,0 to look upside-down)
        );
         */
    }

}
