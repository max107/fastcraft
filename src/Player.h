//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_PLAYER_H
#define FASTCRAFT_PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

namespace fastcraft {

    class Player : public Camera {

    public:
        Player(Settings settings) : Camera(settings) { }
    };

}

#endif //FASTCRAFT_PLAYER_H
