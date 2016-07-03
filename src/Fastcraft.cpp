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
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Turn on double buffering with a 24bit Z buffer.
        // You may need to change this to 16 or 32 for your system
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_GL_SetSwapInterval(1);

        // Init GLEW
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            return false;
        } else if (!GLEW_VERSION_2_1) {
            std::cout << "Failed to support API 2.1" << std::endl;
            return false;
        }

        std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

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
        // Make our background black
        glClearColor(0.5, 0.5, 0.5, 1.0);
        // Set color of renderer to red
        SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);

        return true;
    }

    void Fastcraft::update(float deltaTime) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_e:
                        _show_cursor = !_show_cursor;
                        SDL_ShowCursor(_show_cursor);
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
            }
        }

        _player->update(deltaTime);
    }

    bool Fastcraft::start() {
        _fps = new FpsManager(settings.limit_fps);
        _timer = new Timer;

//        SDL_GL_SwapWindow(window);

        // Make sure that the mouse cursor is centered in the window at program start
        SDL_WarpMouseInWindow(window, settings.width / 2, settings.height / 2);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(_show_cursor);
        SDL_CaptureMouse(SDL_TRUE);

        time_prev = high_resolution_clock::now();

        _skybox = new Skybox();
        _skybox->setup();

        _player = new Player();
        _player->setSettings(settings);
        _player->setup();

//        _block = new Block();
//        _block->setTexture("../resources/texture.jpg");
//        _block->setSize(1);
//        _block->setPosition(0, 0, -100);

        // Enable depth buffer
        glEnable(GL_DEPTH_TEST);

        // Enable back face culling
//        glEnable(GL_CULL_FACE);

        while (isRunning) {
            double deltaTime = _timer->getDeltaTime();
            update(deltaTime);
            render();

            GLenum error;
            while ((error = glGetError()) != GL_NO_ERROR) {
                std::cerr << error << std::endl;
            }

            if (_fps->limit()) {
                char display_text[128];
                sprintf(display_text, "FPS: %i/%i fps - %ims %ims %fms",
                        _fps->getFps(), settings.limit_fps, _fps->getFrameMin(), _fps->getFrameMax(),
                        _fps->getFrameAverage());
                SDL_SetWindowTitle(window, display_text);

                /*
                printf("FPS:%i/%i fps - Min: %ims Max: %ims Average: %fms \n",
                        fps->getFps(), settings.max_fps, fps->getFrameMin(), fps->getFrameMax(), fps->getFrameAverage());
                        */
            }

            // SDL_GL_SwapWindow(window);
        }

        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_SUCCESS;
    }

    void Fastcraft::render() {
        // Clear the window
        SDL_RenderClear(renderer);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        _player->render();
//        _block->render();
//        _skybox->setPosition(_player->getPosition());
        _skybox->setPosition(_player->getPosition());
        _skybox->setSkyboxRotation(_player->getFront(), _player->getUp());
        _skybox->render();

        printf("Player: %f %f %f. Skybox: %f %f %f\n",
               _player->getPosition().x, _player->getPosition().y, _player->getPosition().z,
               _skybox->getPosition().x, _skybox->getPosition().y, _skybox->getPosition().z
        );

        // SDL_GL_SwapWindow(window);

        // Render the changes above
        SDL_RenderPresent(renderer);
    }

}