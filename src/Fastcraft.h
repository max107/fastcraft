//
// Created by Максим Фалалеев on 23/06/16.
//

#ifndef FASTCRAFT_FASTCRAFT_H
#define FASTCRAFT_FASTCRAFT_H

#include <iostream>
#include <vector>
#include <chrono>

#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Skybox.h"
#include "Player.h"
#include "Settings.h"
#include "Block.h"

using namespace std::chrono;

namespace fastcraft {

    class Fastcraft {
    public:
        Fastcraft();

        ~Fastcraft();

        bool init();

        bool start();

        void render();

    private:
        SDL_GLContext _gl_context;
        Settings settings;
        int _show_cursor = SDL_DISABLE;
        high_resolution_clock::time_point time_prev;
        bool isRunning = true;
        SDL_Window *window;
        SDL_Renderer *renderer;

        Player *_player;
        Skybox *_skybox;
        Block *_block;

        void update(float deltaTime);

        float getDelta();
    };

}

#endif //FASTCRAFT_FASTCRAFT_H
