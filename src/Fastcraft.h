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
        Settings settings;

        high_resolution_clock::time_point time_prev;

        bool quit = false;

        SDL_Window *window;

        SDL_Renderer *renderer;

        void update(double delta);

        void handleInput();

        double getDelta();
    };

}

#endif //FASTCRAFT_FASTCRAFT_H
