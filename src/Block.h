//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_BLOCK_H
#define FASTCRAFT_BLOCK_H

#include <GL/glew.h>

#include <SDL2/SDL_image.h>
#include <iostream>

namespace fastcraft {

    class Block {
    public:
        Block();

        ~Block();

        void render();

        GLuint loadTexture(std::string path);

        void setPosition(int x, int y, int z);

        void setTexture(std::string path);

        void setSize(GLfloat size);

    private:
        GLuint texture = 0;

        std::string _texture_path;

        GLfloat _size = 20.f;
    };

}

#endif //FASTCRAFT_BLOCK_H
