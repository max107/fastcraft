//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_PLAYER_H
#define FASTCRAFT_PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

namespace fastcraft {

    class Player {
    public:
        Player(sf::Window &window);

        ~Player();

        void handleUpdate(float deltaTime);

    private:
        // Initial position : on +Z
        glm::vec3 position;

        // Initial horizontal angle : toward -Z
        float _horizontal_angle = 3.14f;
        // Initial vertical angle : none
        float _vertical_angle = 0.f;

        sf::Vector2i _mouse_position;
        sf::Vector2i _last_mouse_position;
        sf::Window const &_window;
        Camera *_camera;
    };

}

#endif //FASTCRAFT_PLAYER_H
