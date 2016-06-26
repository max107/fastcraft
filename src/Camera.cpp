//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Camera.h"

namespace fastcraft {

    Camera::Camera(Settings settings) {
        _settings = settings;

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(_settings.width) / settings.height;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, _draw_distance); // 1500.f
    }

    void Camera::setFov(float fov) {
        // fov is a zoom
        // fov - 5 * glfwGetMouseWheel();
        // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
        _fov = fov;
    }

    void Camera::setDrawDistance(float zfar) {
        _draw_distance = zfar;
    }

    void Camera::setDirection(glm::vec3 direction) {
        _direction = direction;
    }

    void Camera::updatePosition(glm::vec3 position, glm::vec3 direction, glm::vec3 right) {

    }

    void Camera::render() {
        // Up vector
        glm::vec3 up = glm::cross(_right, _direction);

        _model_matrix = glm::mat4(1.f);
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        _projection_matrix = glm::perspective(glm::radians(_fov), 4.0f / 3.0f, 0.1f, _draw_distance);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(_position, _position + _direction, up);

        // Compute the MVP matrix from keyboard and mouse input
        _mvp = _projection_matrix * _view_matrix * _model_matrix;

        // Send our transformation to GPU
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glLoadMatrixf(glm::value_ptr(_mvp));
    }

    void Camera::setPosition(int x, int y, int z) {
        _position = glm::vec3(x, y, z);
    }

    void Camera::setPosition(glm::vec3 position) {
        _position = position;
    }

    Settings Camera::getSettings() {
        return _settings;
    }

    void Camera::setRight(glm::vec3 right) {
        _right = right;
    }

}
