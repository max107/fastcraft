//
// Created by max on 26.06.16.
//

#ifndef FASTCRAFT_OBJECT_H
#define FASTCRAFT_OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace fastcraft {

    class Object {
    public:
        virtual void render();

        virtual void update(float deltaTime);

        virtual void setPosition(int x, int y, int z);

        virtual void setPosition(glm::vec3 position);

        virtual void updatePosition();

        virtual glm::vec3 getPosition();

    private:
        glm::vec3 _position;
    };

}

#endif //FASTCRAFT_OBJECT_H
