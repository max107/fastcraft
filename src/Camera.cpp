//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Camera.h"

namespace fastcraft {

    Camera::Camera(Settings settings) {
        _settings = settings;

        _position = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::vec3 target(0.0f, 0.0f, 0.0f);
        _front = glm::normalize(_position - target);

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
        _front = direction;
    }

    void Camera::render() {
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(_settings.width) / _settings.height;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, _draw_distance); // 1500.f

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> N units
        _projection_matrix = glm::perspective(glm::radians(_fov),
                                              static_cast<float>(_settings.width) / static_cast<float>(_settings.height),
                                              0.1f, _draw_distance);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(_position, _position + _front, _up);

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

    void Camera::handleInput(SDL_Event &event, float deltaTime) {
        int speed = 100;
        GLfloat velocity = speed * deltaTime;

        if (event.type == SDL_MOUSEMOTION) {
            printf("Mouse moved by %d,%d to (%d,%d)\n",
                   event.motion.xrel, event.motion.yrel,
                   event.motion.x, event.motion.y);

            handleMouseMove(event.motion.xrel, event.motion.yrel);
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                case SDLK_d:
//                    _position += glm::normalize(glm::cross(_front, _up)) * velocity;
                    _position -= _right * velocity;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
//                    _position -= glm::normalize(glm::cross(_front, _up)) * velocity;
                    _position += _right * velocity;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    _position -= _front * velocity;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    _position += _front * velocity;
                    break;
                default:
                    break;
            }
        }
    }

    void Camera::handleMouseMove(int xrel, int yrel) {
//        float x = xrel;
//        float y = yrel;

        float xoffset = xrel;
        float yoffset = yrel;

        GLfloat sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }

        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        _front = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                                              -sin(glm::radians(pitch)),
                                              sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
        _right = glm::normalize(glm::cross(up, _front));
        _up = glm::cross(_front, _right);
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
