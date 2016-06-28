//
// Created by Максим Фалалеев on 27/06/16.
//

#ifndef FASTCRAFT_SKYBOX_H
#define FASTCRAFT_SKYBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Object.h"

namespace fastcraft {

    class Skybox : public Object {
    public:
        void render();

        GLuint loadTexture(std::string path);

    private:
        GLuint texture = 0;
    };

}

#endif //FASTCRAFT_SKYBOX_H
