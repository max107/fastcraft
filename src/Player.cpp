//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Player.h"

namespace fastcraft {

    Player::Player(Camera *camera) : _camera(camera) {

    }

    Player::~Player() {
        delete _camera;
    }

    void Player::handleUpdate(sf::Time time) {

    }

}
