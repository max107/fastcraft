//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_BLOCK_H
#define FASTCRAFT_BLOCK_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

namespace fastcraft {

    class Block {
    public:
        Block();

        ~Block();

        void render();

        GLuint loadTexture(sf::String path);

        void setPosition(int x, int y, int z);

    private:
        GLuint texture = 0;
    };

}

#endif //FASTCRAFT_BLOCK_H
