//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Block.h"

namespace fastcraft {

    Block::Block() {

    }

    Block::~Block() {
        // Don't forget to destroy our texture
        glDeleteTextures(1, &texture);
    }

    void Block::render() {
        texture = loadTexture("../resources/texture.jpg");

        // Bind the texture
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
        static const GLfloat cube[] =
                {
                        // positions    // texture coordinates
                        -20, -20, -20, 0, 0,
                        -20, 20, -20, 1, 0,
                        -20, -20, 20, 0, 1,
                        -20, -20, 20, 0, 1,
                        -20, 20, -20, 1, 0,
                        -20, 20, 20, 1, 1,

                        20, -20, -20, 0, 0,
                        20, 20, -20, 1, 0,
                        20, -20, 20, 0, 1,
                        20, -20, 20, 0, 1,
                        20, 20, -20, 1, 0,
                        20, 20, 20, 1, 1,

                        -20, -20, -20, 0, 0,
                        20, -20, -20, 1, 0,
                        -20, -20, 20, 0, 1,
                        -20, -20, 20, 0, 1,
                        20, -20, -20, 1, 0,
                        20, -20, 20, 1, 1,

                        -20, 20, -20, 0, 0,
                        20, 20, -20, 1, 0,
                        -20, 20, 20, 0, 1,
                        -20, 20, 20, 0, 1,
                        20, 20, -20, 1, 0,
                        20, 20, 20, 1, 1,

                        -20, -20, -20, 0, 0,
                        20, -20, -20, 1, 0,
                        -20, 20, -20, 0, 1,
                        -20, 20, -20, 0, 1,
                        20, -20, -20, 1, 0,
                        20, 20, -20, 1, 1,

                        -20, -20, 20, 0, 0,
                        20, -20, 20, 1, 0,
                        -20, 20, 20, 0, 1,
                        -20, 20, 20, 0, 1,
                        20, -20, 20, 1, 0,
                        20, 20, 20, 1, 1
                };

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
    }

    void Block::setPosition(int x, int y, int z) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(x, y, z);
    }

    GLuint Block::loadTexture(std::string path) {
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