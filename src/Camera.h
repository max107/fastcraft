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
        Camera(Settings settings);

        void setPosition(int x, int y, int z);

        void setPosition(glm::vec3 position);

        void setDrawDistance(float zfar);

        void setFov(float fov);

        void render();

        void setDirection(glm::vec3 direction);

        void setRight(glm::vec3 right);

        Settings getSettings();

        void initShader();

        void loadShaderMatrix();

        void handleMouseMove(int xrel, int yrel);

        void handleInput(SDL_Event &event, float deltaTime);

    private:
        float yaw;
        float pitch;

        glm::mat4 _projection_matrix;
        // камера находится в точке (0,0,5)
        // она смотрит на точку (0,0,0)
        // вектор, идущий из центра камеры к ее верху, равен (0, 1, 0)
        // то есть, камера расположена горизонтально
        glm::mat4 _view_matrix = glm::lookAt(glm::vec3(0, 0, 5),
                                             glm::vec3(0, 0, 0),
                                             glm::vec3(0, 1, 0));
        glm::mat4 _model_matrix = glm::mat4(1.f);
        glm::mat4 _mvp;

        GLint _matrix_id;

        Settings _settings;
        glm::vec3 _position;

        float _fov = 45.0f;
        float _draw_distance = 500.f;

        glm::vec3 _front;
        glm::vec3 _right;
        glm::vec3 _up;
    };

}

#endif //FASTCRAFT_CAMERA_H
