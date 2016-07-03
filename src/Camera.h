//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_CAMERA_H
#define FASTCRAFT_CAMERA_H

#include <iostream>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"
#include "Settings.h"
#include "Shader.h"

namespace fastcraft {

    class Camera : public Object {
    public:
        Camera();

        GLfloat getSensitivity();

        void setup();

        void render();

        void handleMouseMove(int xrel, int yrel);

        void handleInput(float deltaTime);

        void update(float deltaTime);

        glm::vec3 getFront();

        glm::vec3 getUp();

    private:
        float yaw = 0.f;
        float pitch = 0.f;
        Shader *shader;
        glm::mat4 _projection_matrix;
        // камера находится в точке (0,0,5)
        // она смотрит на точку (0,0,0)
        // вектор, идущий из центра камеры к ее верху, равен (0, 1, 0)
        // то есть, камера расположена горизонтально
        glm::mat4 _view_matrix = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 _model_matrix = glm::mat4(1.f);
        glm::mat4 _mvp;
        glm::vec3 _front;
        glm::vec3 _right;
        glm::vec3 _up;
        bool _fly = true;
    };

}

#endif //FASTCRAFT_CAMERA_H
