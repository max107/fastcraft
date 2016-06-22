//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_PLAYER_H
#define FASTCRAFT_PLAYER_H

#include <SFML/System.hpp>
#include "Camera.h"

namespace fastcraft {

    class Player {
    public:
        Player(Camera *camera);

        ~Player();

        void handleUpdate(sf::Time time);

    private:
        Camera *_camera;
    };

}

#endif //FASTCRAFT_PLAYER_H
