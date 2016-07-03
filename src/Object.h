//
// Created by max on 26.06.16.
//

#ifndef FASTCRAFT_OBJECT_H
#define FASTCRAFT_OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Settings.h"

namespace fastcraft {

    class Object {
    public:
        virtual void render();

        virtual void update(float deltaTime);

        virtual void setPosition(int x, int y, int z);

        virtual void setPosition(glm::vec3 position);

        virtual void updatePosition();

        virtual glm::vec3 getPosition();

        virtual void setSettings(Settings settings);

        virtual Settings getSettings();

    private:
        Settings _settings;
        glm::vec3 _position;
    };

}

#endif //FASTCRAFT_OBJECT_H
