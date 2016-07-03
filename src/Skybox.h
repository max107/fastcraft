//
// Created by Максим Фалалеев on 27/06/16.
//

#ifndef FASTCRAFT_SKYBOX_H
#define FASTCRAFT_SKYBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Texture.h"
#include "Object.h"
#include "VertexArray.h"
#include "Shader.h"

namespace fastcraft {

    class Skybox : public Object {
    public:
        Skybox();

        void render();

        void setSkyboxRotation(glm::vec3 front, glm::vec3 up);

        void setup();

    private:
        glm::mat4 getMVPMatrix();
        glm::vec3 _front;
        glm::vec3 _up;
        float _size = 1.f;
        VertexArray *vao;
        GLuint skyboxVAO, skyboxVBO;
        GLuint texture = 0;
        Shader *shader;

        GLuint loadTextures(std::vector<const GLchar *> faces);
    };

}

#endif //FASTCRAFT_SKYBOX_H
