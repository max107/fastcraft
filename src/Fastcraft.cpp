//
// Created by Максим Фалалеев on 23/06/16.
//

#include "Fastcraft.h"

namespace fastcraft {

    Fastcraft::Fastcraft() {

    }

    Fastcraft::~Fastcraft() {
        SDL_GL_DeleteContext(_gl_context);
    }

    bool Fastcraft::init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
            std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
            return false;
        }

        unsigned int mods = SDL_WINDOW_OPENGL;
        if (settings.fullscreen) {
            mods |= SDL_WINDOW_FULLSCREEN;
        }
        window = SDL_CreateWindow("Fastcraft",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  settings.width,
                                  settings.height,
                                  mods);
        if (window == nullptr) {
            std::cout << "Failed to create window : " << SDL_GetError();
            return false;
        }

        _gl_context = SDL_GL_CreateContext(window);

        // http://headerphile.com/sdl2/opengl-part-1-sdl-opengl-awesome/

        // Set our OpenGL version.
        // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Turn on double buffering with a 24bit Z buffer.
        // You may need to change this to 16 or 32 for your system
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // Init GLEW
        // Apparently, this is needed for Apple. Thanks to Ross Vander for letting me know
#ifdef __APPLE__
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            return false;
        } else if (!GLEW_VERSION_2_1) {
            std::cout << "Failed to support API 2.1" << std::endl;
            return false;
        }
#endif

        unsigned int renderMods = 0;
        if (settings.vsync) {
            renderMods = SDL_RENDERER_PRESENTVSYNC;
        }
        renderer = SDL_CreateRenderer(window, -1, renderMods);
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
        float mouseSpeed = 4.0f; // 3 units / second

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            if (event.type == SDL_MOUSEMOTION) {
                float x = event.motion.x / (mouseSpeed * 10);
                float y = event.motion.y / (mouseSpeed * 10);
                // Direction : Spherical coordinates to Cartesian coordinates conversion
                direction = glm::vec3(std::cos(y) * std::sin(x), std::sin(y), std::cos(y) * std::cos(x));
                right = -glm::vec3(std::sin(x - 3.14f / 2.0f), 0, std::cos(x - 3.14f / 2.0f));

                _player->setDirection(direction);
                _player->setRight(right);
            }

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

                _player->setPosition(position);
            }
        }
    }

    bool Fastcraft::start() {
        SDL_GL_SwapWindow(window);

        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(_show_cursor);
        SDL_CaptureMouse(SDL_TRUE);
        time_prev = high_resolution_clock::now();

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(settings.width) / settings.height;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 1500.f); // 1500.f

        Shader mainShader("../resources/shader/main.vert", "../resources/shader/main.frag");
        mainShader.use();

        _skybox = new Skybox();

        _player = new Player(settings);
        _player->setPosition(0, 0, 0);

        _block = new Block();
        _block->setTexture("../resources/texture.jpg");
        _block->setSize(20);
        _block->setPosition(0, 0, -100);

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

        _skybox->render();
        _player->render();
        _block->render();

        // Render the changes above
        SDL_RenderPresent(renderer);
    }

}