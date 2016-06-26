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

namespace fastcraft {

    class Camera : public Object {
    public:
        Camera(Settings settings);

        void setPosition(int x, int y, int z);

        void setDrawDistance(float zfar);

        void setFov(float fov);

        void updatePosition(glm::vec3 position, glm::vec3 direction, glm::vec3 right);

        void render();

        Settings getSettings();

    private:
        glm::mat4 _projection_matrix;
        glm::mat4 _view_matrix;
        glm::mat4 _model_matrix;
        glm::mat4 _mvp;

        Settings _settings;
        glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);

        float _fov = 45.0f;
        float _draw_distance = 500.f;
    };

}

#endif //FASTCRAFT_CAMERA_H
