//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Camera.h"

namespace fastcraft {

    Camera::Camera(sf::Window &window) : _window(window) {
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // glOrtho(0, window.getSize().x, 0, window.getSize().y, 0, 1);

        GLfloat ratio = static_cast<float>(_window.getSize().x) / _window.getSize().y;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, _draw_distance); // 1500.f

        _model_matrix = glm::mat4(1.0);
        _projection_matrix = glm::perspective(glm::radians(_fov), 4.0f / 3.0f, 0.1f, _draw_distance);
    }

    void Camera::setFov(float fov) {
        _fov = fov;
    }

    void Camera::setDrawDistance(float zfar) {
        _draw_distance = zfar;
    }

    void Camera::handleUpdate(glm::vec3 position, glm::vec3 direction, glm::vec3 right) {
        // fov is a zoom
        float FoV = _fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

        // Up vector
        glm::vec3 up = glm::cross(right, direction);

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        _projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, _draw_distance);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(position, position + direction, up);

        // Compute the MVP matrix from keyboard and mouse input
        glm::mat4 MVP = _projection_matrix * _view_matrix * _model_matrix;

        // Send our transformation to GPU
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(MVP));
    }

}
