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
        Player(Camera *camera, sf::Window &window);

        ~Player();

        void handleUpdate(float deltaTime);

        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;
    private:
        sf::Vector2i lastMousePosition;
        sf::Window &_window;
        Camera *_camera;
    };

}

#endif //FASTCRAFT_PLAYER_H
