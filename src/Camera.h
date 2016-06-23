//
// Created by Максим Фалалеев on 22/06/16.
//

#ifndef FASTCRAFT_CAMERA_H
#define FASTCRAFT_CAMERA_H

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fastcraft {

    class Camera {
    public:
        Camera(sf::Window &window);

        void setDrawDistance(float zfar);

        void setFov(float fov);

        void handleUpdate(glm::vec3 position, glm::vec3 direction, glm::vec3 right);

    protected:
        glm::mat4 _projection_matrix;
        glm::mat4 _view_matrix;
        glm::mat4 _model_matrix;

    private:
        sf::Window const &_window;
        float _fov = 45.0f;
        float _draw_distance = 500.f;
    };

}

#endif //FASTCRAFT_CAMERA_H
