//
// Created by Максим Фалалеев on 27/06/16.
//

#include "Skybox.h"

namespace fastcraft {

    Skybox::Skybox() {
        shader = new Shader("../resources/shader/skybox.vert", "../resources/shader/skybox.frag");
        setup();
    }

    GLuint Skybox::loadTextures(std::vector<const GLchar *> faces) {
        // Load an OpenGL texture.
        // We could directly use a sf::Texture as an OpenGL texture (with its Bind() member function),
        // but here we want more control on it (generate mipmaps, ...) so we create a new one from an image
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        for (GLuint i = 0; i < faces.size(); i++) {
            SDL_Surface *Surface = IMG_Load(faces[i]);

            int imageMode = GL_RGB;
            if (Surface->format->BytesPerPixel == 4) {
                imageMode = GL_RGBA;
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                         imageMode, Surface->w, Surface->h, 0,
                         imageMode, GL_UNSIGNED_BYTE, Surface->pixels);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        return texture;
    }

    void Skybox::setup() {
        std::vector<const GLchar *> faces;
        faces.push_back("../resources/skybox/xpos.png");
        faces.push_back("../resources/skybox/xneg.png");
        faces.push_back("../resources/skybox/ypos.png");
        faces.push_back("../resources/skybox/yneg.png");
        faces.push_back("../resources/skybox/zpos.png");
        faces.push_back("../resources/skybox/zneg.png");
        texture = loadTextures(faces);

        float _size = 50.f;
        // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
        static const GLfloat cube[] =
                {
                        // positions
                        -_size, -_size, -_size,
                        -_size, _size, -_size,
                        -_size, -_size, _size,
                        -_size, -_size, _size,
                        -_size, _size, -_size,
                        -_size, _size, _size,

                        _size, -_size, -_size,
                        _size, _size, -_size,
                        _size, -_size, _size,
                        _size, -_size, _size,
                        _size, _size, -_size,
                        _size, _size, _size,

                        -_size, -_size, -_size,
                        _size, -_size, -_size,
                        -_size, -_size, _size,
                        -_size, -_size, _size,
                        _size, -_size, -_size,
                        _size, -_size, _size,

                        -_size, _size, -_size,
                        _size, _size, -_size,
                        -_size, _size, _size,
                        -_size, _size, _size,
                        _size, _size, -_size,
                        _size, _size, _size,

                        -_size, -_size, -_size,
                        _size, -_size, -_size,
                        -_size, _size, -_size,
                        -_size, _size, -_size,
                        _size, -_size, -_size,
                        _size, _size, -_size,

                        -_size, -_size, _size,
                        _size, -_size, _size,
                        -_size, _size, _size,
                        -_size, _size, _size,
                        _size, -_size, _size,
                        _size, _size, _size
                };

//        GLfloat vertices[8 * 3] = {
//                -_size, -_size, _size,
//                _size, -_size, _size,
//                _size, _size, _size,
//                -_size, _size, _size,
//                -_size, -_size, -_size,
//                _size, -_size, -_size,
//                _size, _size, -_size,
//                -_size, _size, -_size
//        };
//
//        GLuint indices[6 * 6] = {
//                0, 1, 2, 2, 3, 0,
//                3, 2, 6, 6, 7, 3,
//                7, 6, 5, 5, 4, 7,
//                4, 0, 3, 3, 7, 4,
//                0, 1, 5, 5, 4, 0,
//                1, 5, 6, 6, 2, 1
//        };
//        vao = new VertexArray(vertices, indices, nullptr, nullptr, 8 * 3, 6 * 6);

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), &cube, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
        glBindVertexArray(0);
    }

    void Skybox::render(glm::mat4 mvp) {
        GLint OldCullFaceMode;
        glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
        GLint OldDepthFuncMode;
        glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

        glCullFace(GL_FRONT);
        glDepthFunc(GL_LEQUAL);

        glDepthMask (GL_FALSE);

        shader->enable();

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glUniform1i(glGetUniformLocation(shader->getProgramId(), "skybox"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glDepthMask(GL_TRUE);

        shader->setUniformMatrix("mvp", mvp);
        shader->disable();

        glCullFace(OldCullFaceMode);
        glDepthFunc(OldDepthFuncMode);
    }

}