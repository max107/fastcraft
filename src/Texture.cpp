//
// Created by max on 02.07.16.
//

#include "Texture.h"

namespace fastcraft {

    GLuint Texture::load(std::string path) {
        // Load an OpenGL texture.
        // We could directly use a sf::Texture as an OpenGL texture (with its Bind() member function),
        // but here we want more control on it (generate mipmaps, ...) so we create a new one from an image
        GLuint texture = 0;

        // You should probably use CSurface::OnLoad ... ;)
        //-- and make sure the Surface pointer is good!
        SDL_Surface *Surface = IMG_Load(path.c_str());

        int imageMode = GL_RGB;
        if (Surface->format->BytesPerPixel == 4) {
            imageMode = GL_RGBA;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, imageMode, Surface->w, Surface->h, 0, imageMode, GL_UNSIGNED_BYTE,
                     Surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        return texture;
    }

}