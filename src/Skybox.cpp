//
// Created by Максим Фалалеев on 27/06/16.
//

#include "Skybox.h"

namespace fastcraft {

    GLuint Skybox::loadTexture(std::string path) {
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

    void Skybox::render() {
        texture = loadTexture("../resources/skybox/xneg.png");

        // Bind the texture
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        float _size = 100.f;
        // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
        static const GLfloat cube[] =
                {
                        // positions    // texture coordinates
                        -_size, -_size, -_size, 0, 0,
                        -_size, _size, -_size, 1, 0,
                        -_size, -_size, _size, 0, 1,
                        -_size, -_size, _size, 0, 1,
                        -_size, _size, -_size, 1, 0,
                        -_size, _size, _size, 1, 1,

                        _size, -_size, -_size, 0, 0,
                        _size, _size, -_size, 1, 0,
                        _size, -_size, _size, 0, 1,
                        _size, -_size, _size, 0, 1,
                        _size, _size, -_size, 1, 0,
                        _size, _size, _size, 1, 1,

                        -_size, -_size, -_size, 0, 0,
                        _size, -_size, -_size, 1, 0,
                        -_size, -_size, _size, 0, 1,
                        -_size, -_size, _size, 0, 1,
                        _size, -_size, -_size, 1, 0,
                        _size, -_size, _size, 1, 1,

                        -_size, _size, -_size, 0, 0,
                        _size, _size, -_size, 1, 0,
                        -_size, _size, _size, 0, 1,
                        -_size, _size, _size, 0, 1,
                        _size, _size, -_size, 1, 0,
                        _size, _size, _size, 1, 1,

                        -_size, -_size, -_size, 0, 0,
                        _size, -_size, -_size, 1, 0,
                        -_size, _size, -_size, 0, 1,
                        -_size, _size, -_size, 0, 1,
                        _size, -_size, -_size, 1, 0,
                        _size, _size, -_size, 1, 1,

                        -_size, -_size, _size, 0, 0,
                        _size, -_size, _size, 1, 0,
                        -_size, _size, _size, 0, 1,
                        -_size, _size, _size, 0, 1,
                        _size, -_size, _size, 1, 0,
                        _size, _size, _size, 1, 1
                };

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Enable position and texture coordinates vertex components
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
        glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

        // Disable normal and color vertex components
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        // Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glTranslatef(0, 0, 100);
    }

}