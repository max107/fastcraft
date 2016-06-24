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

    private:
        GLuint texture = 0;
    };

}

#endif //FASTCRAFT_BLOCK_H
