//
// Created by Максим Фалалеев on 23/06/16.
//

#ifndef FASTCRAFT_FASTCRAFT_H
#define FASTCRAFT_FASTCRAFT_H

#include <iostream>
#include <chrono>
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Player.h"
#include "Settings.h"
#include "Block.h"

using namespace std::chrono;

namespace fastcraft {

    class Fastcraft {
    public:
        Fastcraft();

        bool init();

        bool start();

        void render();

    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 right;

        Settings settings;

        int _show_cursor = SDL_DISABLE;

        high_resolution_clock::time_point time_prev;

        bool isRunning = true;

        SDL_Window *window;

        SDL_Renderer *renderer;

        void update(float deltaTime);

        void handleInput(float deltaTime);

        float getDelta();

        Player *_player;
        Camera *_camera;
        Block *_block;
    };

}

#endif //FASTCRAFT_FASTCRAFT_H
