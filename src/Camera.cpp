//
// Created by Максим Фалалеев on 22/06/16.
//

#include "Camera.h"

namespace fastcraft {

    Camera::Camera() {

    }

    void Camera::setup() {
        setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
        glm::vec3 target(0.0f, 0.0f, 0.0f);
        _front = glm::normalize(getPosition() - target);
        shader = new Shader("../resources/shader/main.vert", "../resources/shader/main.frag");
    }

    glm::vec3 Camera::getFront() {
        return _front;
    }

    glm::vec3 Camera::getUp() {
        return _up;
    }

    void Camera::render() {
        shader->enable();

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(getSettings().width) / getSettings().height;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, getSettings().draw_distance); // 1500.f

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> N units
        _projection_matrix = glm::perspective(glm::radians(getSettings().fov),
                                              static_cast<float>(getSettings().width) /
                                              static_cast<float>(getSettings().height),
                                              0.1f, getSettings().draw_distance);
        // Camera matrix
        // 1 - Camera is here
        // 2 - and looks here : at the same position, plus "direction"
        // 3 - Head is up (set to 0,-1,0 to look upside-down)
        _view_matrix = glm::lookAt(getPosition(), getPosition() + _front, _up);

        // Compute the MVP matrix from keyboard and mouse input
        _mvp = _projection_matrix * _view_matrix * _model_matrix;
        shader->setUniformMatrix("mvp", _mvp);
        shader->disable();
    }

    void Camera::handleInput(float deltaTime) {
        int speed = 100;
        GLfloat velocity = speed * deltaTime;

        const Uint8 *keystates = SDL_GetKeyboardState(NULL);

        if (keystates[SDL_SCANCODE_LSHIFT] || keystates[SDL_SCANCODE_RSHIFT]) {
            velocity = velocity * 4;
        }

        glm::vec3 position = getPosition();
        if (keystates[SDL_SCANCODE_W]) {
            position += _front * velocity;
        } else if (keystates[SDL_SCANCODE_S]) {
            position -= _front * velocity;
        }

        if (keystates[SDL_SCANCODE_A]) {
            position += _right * velocity;
        } else if (keystates[SDL_SCANCODE_D]) {
            position -= _right * velocity;
        }

        if (!_fly) {
            position.y = 0.0f;
        }
        setPosition(position);
    }

    void Camera::update(float deltaTime) {
        int xrel, yrel;
        SDL_GetRelativeMouseState(&xrel, &yrel);
        handleMouseMove(xrel, yrel);
        handleInput(deltaTime);
    }

    GLfloat Camera::getSensitivity() {
        GLfloat sensitivity = getSettings().mouse_sensitivity;
        if (sensitivity == 0) {
            sensitivity = 1;
        }
        sensitivity /= 100;
        return sensitivity;
    }

    void Camera::handleMouseMove(int xrel, int yrel) {
        // printf("Mouse moved by %d,%d\n", xrel, yrel);

        GLfloat sensitivity = getSensitivity();

        float xoffset = xrel * sensitivity;
        float yoffset = yrel * sensitivity;

        yaw += xoffset;
        pitch += yoffset;
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        glm::vec3 front(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                        -sin(glm::radians(pitch)),
                        sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        _front = glm::normalize(front);
        _right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), _front));
        _up = glm::cross(_front, _right);
    }
}
