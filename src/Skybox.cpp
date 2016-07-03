//
// Created by Максим Фалалеев on 27/06/16.
//

#include "Skybox.h"

namespace fastcraft {

    Skybox::Skybox() {

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
        shader = new Shader("../resources/shader/skybox.vert", "../resources/shader/skybox.frag");

        std::vector<const GLchar *> faces;
        faces.push_back("../resources/skybox/xpos.png");
        faces.push_back("../resources/skybox/xneg.png");
        faces.push_back("../resources/skybox/ypos.png");
        faces.push_back("../resources/skybox/yneg.png");
        faces.push_back("../resources/skybox/zpos.png");
        faces.push_back("../resources/skybox/zneg.png");
        texture = loadTextures(faces);

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

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube), &cube, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
        glBindVertexArray(0);
    }

    void Skybox::setSkyboxRotation(glm::vec3 front, glm::vec3 up) {
        _front = front;
        _up = up;
    }

    glm::mat4 Skybox::getMVPMatrix() {
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> N units
        glm::mat4 _projection_matrix = glm::perspective(glm::radians(getSettings().fov),
                                                        static_cast<float>(getSettings().width) /
                                                        static_cast<float>(getSettings().height),
                                                        0.1f, getSettings().draw_distance);
        glm::mat4 _view_matrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), _front, _up);
        // Compute the MVP matrix from keyboard and mouse input
        return _projection_matrix * _view_matrix * glm::mat4(1.f);
    }

    void Skybox::render() {
        GLint OldCullFaceMode, OldDepthFuncMode;
        glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
        glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
        glCullFace(GL_FRONT);
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);

        // skybox cube
        shader->enable();
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        shader->setUniformInt("skybox", 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glDepthMask(GL_TRUE);
        shader->setUniformMatrix("mvp", getMVPMatrix());
        shader->disable();

        glCullFace(OldCullFaceMode);
        glDepthFunc(OldDepthFuncMode);
    }

}