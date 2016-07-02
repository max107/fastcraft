//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_BLOCK_H
#define FASTCRAFT_BLOCK_H

#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Object.h"
#include "VertexArray.h"

namespace fastcraft {

    class Block : public Object {

    public:
        Block();

        ~Block();

        void render();

        void enableTexture();

        void disableTexture();

        GLuint loadTexture(std::string path);

        void setTexture(std::string path);

        void setSize(GLfloat size);

    private:
        VertexArray *vao;

        GLuint texture = 0;

        GLfloat _size = 16.0f;
    };

}

#endif //FASTCRAFT_BLOCK_H
