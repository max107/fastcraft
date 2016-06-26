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

    void Fastcraft::update(float deltaTime) {
        handleInput(deltaTime);
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
    float Fastcraft::getDelta() {
        // Gett current time as a std::chrono::time_point
        // which basically contains info about the current point in time
        auto timeCurrent = high_resolution_clock::now();

        // Compare the two to create time_point containing delta time in nanosecnds
        auto timeDiff = duration_cast<nanoseconds>(timeCurrent - time_prev);

        // Get the tics as a variable
        float delta = timeDiff.count();

        // Turn nanoseconds into seconds
        delta /= 1000000000;

        time_prev = timeCurrent;
        return delta;
    }

    void Fastcraft::handleInput(float deltaTime) {
        float speed = 3.0f; // 3 units / second

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

//            if (event.type == SDL_MOUSEMOTION) {
                // Direction : Spherical coordinates to Cartesian coordinates conversion
                direction = glm::vec3(std::cos(event.motion.yrel) * std::sin(event.motion.xrel),
                                      std::sin(event.motion.yrel),
                                      std::cos(event.motion.yrel) * std::cos(event.motion.xrel));
                right = -glm::vec3(std::sin(event.motion.xrel - 3.14f / 2.0f),
                                   0,
                                   std::cos(event.motion.xrel - 3.14f / 2.0f));
//            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_e:
                        _show_cursor = !_show_cursor;
                        SDL_ShowCursor(_show_cursor);
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        position += right * deltaTime * speed;
                        break;
                    case SDLK_LEFT:
                    case SDLK_a:
                        position -= right * deltaTime * speed;
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        position -= direction * deltaTime * speed;
                        break;
                    case SDLK_UP:
                    case SDLK_w:
                        position += direction * deltaTime * speed;
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
            }

            _player->updatePosition(position, direction, right);
        }
    }

    void setupCubeMap(GLuint& texture) {
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_CUBE_MAP);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void setupCubeMap(GLuint& texture, SDL_Surface *xpos, SDL_Surface *xneg, SDL_Surface *ypos, SDL_Surface *yneg, SDL_Surface *zpos, SDL_Surface *zneg) {
        setupCubeMap(texture);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, xpos->w, xpos->h, 0, xpos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, xpos->pixels);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, xneg->w, xneg->h, 0, xneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, xneg->pixels);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, ypos->w, ypos->h, 0, ypos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, ypos->pixels);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, yneg->w, yneg->h, 0, yneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, yneg->pixels);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, zpos->w, zpos->h, 0, zpos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, zpos->pixels);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, zneg->w, zneg->h, 0, zneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, zneg->pixels);
    }

    void deleteCubeMap(GLuint& texture) {
        glDeleteTextures(1, &texture);
    }

    bool Fastcraft::start() {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(_show_cursor);
        SDL_CaptureMouse(SDL_TRUE);
        time_prev = high_resolution_clock::now();

        _player = new Player(settings);
        _player->setPosition(0, 0, 0);

        _block = new Block();
        _block->setTexture("../resources/texture.jpg");
        _block->setSize(500);
        _block->setPosition(0, 0, -200);

        while (isRunning) {
            float deltaTime = getDelta();
            if (settings.max_fps > 0 && getDelta() < (1000 / settings.max_fps)) {
                SDL_Delay((1000 / settings.max_fps) - deltaTime);
            }
            update(deltaTime);
            render();
        }

        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_SUCCESS;
    }

    void Fastcraft::render() {
        // Clear the window and make it all red
        SDL_RenderClear(renderer);

        _player->render();
        _block->render();

        // Render the changes above
        SDL_RenderPresent(renderer);
    }

}