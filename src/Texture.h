//
// Created by max on 02.07.16.
//

#ifndef FASTCRAFT_TEXTURE_H
#define FASTCRAFT_TEXTURE_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace fastcraft {

    class Texture {
    public:
        static GLuint load(std::string path);
    };

}

#endif //FASTCRAFT_TEXTURE_H
