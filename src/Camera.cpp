//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Camera.h"

namespace fastcraft {

    Camera::Camera(Settings settings) {
        _settings = settings;

//        initShader();
    }

    void Camera::initShader() {
        Shader mainShader("../resources/shader/main.vert", "../resources/shader/main.frag");
        mainShader.use();
//        Get a handle for our "mvp" uniform
        _matrix_id = glGetUniformLocation(mainShader.getProgramId(), "position");
    }

    void Camera::loadShaderMatrix() {
        // Send our transformation to GPU
        glUniformMatrix4fv(_matrix_id, 1, GL_FALSE, &_mvp[0][0]);
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

    void Camera::render() {
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(_settings.width) / _settings.height;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, _draw_distance); // 1500.f

        // Up vector
        glm::vec3 up = glm::cross(_right, _direction);

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> N units
        _projection_matrix = glm::perspective(glm::radians(_fov), static_cast<float>(_settings.width) / static_cast<float>(_settings.height), 0.1f, _draw_distance);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(_position, _position + _direction, up);

        // Compute the MVP matrix from keyboard and mouse input
        _mvp = _projection_matrix * _view_matrix * _model_matrix;

//        std::cout << "Direction: " << _direction.x << _direction.y << std::endl;
//        std::cout << "Right: "  << _right.x << _right.y << std::endl;

        // Send our transformation to GPU
         glLoadMatrixf(glm::value_ptr(_mvp));
//        loadShaderMatrix();

        /* Make sure we're chaning the model view and not the projection */
        glMatrixMode(GL_MODELVIEW);
        /* Reset The View */
        glLoadIdentity();
    }

    void Camera::handleMouseMove(int mouseX, int mouseY, int mouseXRel, int mouseYRel) {

    }

    void Camera::setPosition(int x, int y, int z) {
        _position = glm::vec3(x, y, z);

        // Up vector
        glm::vec3 up = glm::cross(_right, _direction);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(_position, _position + _direction, up);
        // Compute the MVP matrix from keyboard and mouse input
        _mvp = _projection_matrix * _view_matrix * _model_matrix;
    }

    void Camera::setPosition(glm::vec3 position) {
        _position = position;

        // Up vector
        glm::vec3 up = glm::cross(_right, _direction);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(_position, _position + _direction, up);
        // Compute the MVP matrix from keyboard and mouse input
        _mvp = _projection_matrix * _view_matrix * _model_matrix;
    }

    Settings Camera::getSettings() {
        return _settings;
    }

    void Camera::setRight(glm::vec3 right) {
        _right = right;
    }
}
