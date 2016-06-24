//
// Created by Максим Фалалеев on 23/06/16.
//

#include "Fastcraft.h"

namespace fastcraft {

    Fastcraft::Fastcraft() {

    }

    bool Fastcraft::init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
            std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("Fastcraft", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.width,
                                  settings.height, SDL_WINDOW_OPENGL);
        if (window == nullptr) {
            std::cout << "Failed to create window : " << SDL_GetError();
            return false;
        }

        // Init GLEW
        // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
#ifndef __APPLE__
        glewExperimental = GL_TRUE;
        if (!glewInit()) {
            std::cout << "Failed to init glew" << std::endl;
            return false;
        }
#endif

        // http://headerphile.com/sdl2/opengl-part-1-sdl-opengl-awesome/

        // Set our OpenGL version.
        // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

        // Turn on double buffering with a 24bit Z buffer.
        // You may need to change this to 16 or 32 for your system
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_GLContext SDL_GL_CreateContext(SDL_Window *window);

        int mods = 0;
        if (settings.vsync) {
            mods = SDL_RENDERER_PRESENTVSYNC;
        }
        renderer = SDL_CreateRenderer(window, -1, mods);
        if (renderer == nullptr) {
            std::cout << "Failed to create renderer : " << SDL_GetError();
            return false;
        }

        // Set size of renderer to the same as window
        SDL_RenderSetLogicalSize(renderer, settings.width, settings.height);

        // Set color of renderer to red
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);

        return true;
    }

    void Fastcraft::update(double delta) {
//    player.CheckFinishLine(topBar.GetRect().y + topBar.GetRect().h, windowRect);
//
//    for (auto &p : enemies) {
//        p.Update(delta);
//
//        if (player.CheckCollision(p))
//            player.ResetPosition(windowRect);
//
//        p.CheckBounds(windowRect);
//    }
    }

    // Returns time since last time this function was called in seconds with nanosecond precision
    double Fastcraft::getDelta() {
        // Gett current time as a std::chrono::time_point
        // which basically contains info about the current point in time
        auto timeCurrent = high_resolution_clock::now();

        // Compare the two to create time_point containing delta time in nanosecnds
        auto timeDiff = duration_cast<nanoseconds>(timeCurrent - time_prev);

        // Get the tics as a variable
        double delta = timeDiff.count();

        // Turn nanoseconds into seconds
        delta /= 1000000000;

        time_prev = timeCurrent;
        return delta;
    }

    void Fastcraft::handleInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_e:
                        _show_cursor = !_show_cursor;
                        SDL_ShowCursor(_show_cursor);
                        break;
                    case SDLK_RIGHT:
                        // Cover with green and update
//                    player.MoveRight();
                        break;
                    case SDLK_LEFT:
//                    player.MoveLeft();
                        break;
                    case SDLK_DOWN:
//                    player.MoveDown();
                        break;
                    case SDLK_UP:
//                    player.MoveUp();
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    bool Fastcraft::start() {
        SDL_ShowCursor(_show_cursor);
        SDL_CaptureMouse(SDL_TRUE);
        time_prev = high_resolution_clock::now();

        while (!quit) {
            handleInput();

            update(getDelta());
            if (settings.max_fps > 0 && getDelta() < (1000 / settings.max_fps)) {
                SDL_Delay((1000 / settings.max_fps) - getDelta());
            }
            render();
        }
        return EXIT_SUCCESS;
    }

    void Fastcraft::render() {
        // Clear the window and make it all red
        SDL_RenderClear(renderer);

        //    for (auto &p : enemies) {
        //        p.Render(renderer);
        //    }

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(settings.width) / settings.height;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 1500.f); // 1500.f
//        glm::mat4 _model_matrix = glm::mat4(1.0);
//        glm::mat4 _projection_matrix = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 1500.f);

        Block *block = new Block();
        block->setPosition(0, 0, -100);
        block->render();

        // Render the changes above
        SDL_RenderPresent(renderer);
    }

}