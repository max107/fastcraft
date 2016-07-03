//
// Created by max on 26.06.16.
//

#include "Object.h"

namespace fastcraft {

    void Object::render() {

    }

    void Object::update(float deltaTime) {

    }

    void Object::setPosition(int x, int y, int z) {
        _position = glm::vec3(x, y, z);
    }

    void Object::setPosition(glm::vec3 position) {
        _position = position;
    }

    void Object::updatePosition() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(_position.x, _position.y, _position.z);
    }

    glm::vec3 Object::getPosition() {
        return _position;
    }

    void Object::setSettings(Settings settings) {
        _settings = settings;
    }

    Settings Object::getSettings() {
        return _settings;
    }

}
