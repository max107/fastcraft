#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <SFML/Graphics.hpp>

#include "src/Block.h"
#include "src/Player.h"
#include "src/Camera.h"
#include "src/Shader.h"

#include <glm/glm.hpp>

using namespace fastcraft;

int main() {
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

//    contextSettings.majorVersion = 3;
//    contextSettings.minorVersion = 3;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        //Problem: glewInit failed, something is seriously wrong.
        cout << "glewInit failed, aborting." << endl;
    }
    cout << glGetString(GL_VERSION) << endl;

    // Create a sprite for the background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../resources/background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite background(backgroundTexture);

    // Create some text to draw on top of our OpenGL object
    sf::Font font;
    if (!font.loadFromFile("../resources/sansation.ttf"))
        return EXIT_FAILURE;
    sf::Text text("SFML / OpenGL demo", font);
    text.setColor(sf::Color(0, 0, 0, 170));
    text.setPosition(10.f, 10.f);
    text.setCharacterSize(14);

    // Make the window the active target for OpenGL calls
    // Note: If using sf::Texture or sf::Shader with OpenGL,
    // be sure to call sf::Texture::getMaximumSize() and/or
    // sf::Shader::isAvailable() at least once before calling
    // setActive(), as those functions will cause a context switch
    window.setMouseCursorVisible(false);
    window.setActive();

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    glDisable(GL_LIGHTING);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    ///////////////////////////////////////////////////

    // Create and compile our GLSL program from the shaders
//    GLuint programID = LoadShaders("../resources/shader/vertex.vertexshader",
//                                   "../resources/shader/fragment.fragmentshader");
    // Get a handle for our "MVP" uniform
//    GLuint MatrixID = glGetUniformLocation(programID, "mvp");

    ///////////////////////////////////////////////////

    Player *player = new Player(window);

    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);

    // enable wireframe GL_FRONT, GL_BACK
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // disable wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    Block *block = new Block();

    // Start game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key: exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // Adjust the viewport when the window is resized
            if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // Compute the MVP matrix from keyboard and mouse input
        player->handleUpdate(clock.getElapsedTime().asSeconds());

        // check OpenGL error
        GLenum errGl;
        while ((errGl = glGetError()) != GL_NO_ERROR) {
            cerr << "OpenGL error: " << errGl << endl;
        }

        // Draw the background
//        window.pushGLStates();
//        window.draw(background);
//        window.popGLStates();

        // Clear the depth buffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        block->setPosition(0, 0, -200);
        block->render();

        // Draw some text on top of our OpenGL object
        window.pushGLStates();
        window.draw(text);
        window.popGLStates();

        // Finally, display the rendered frame on screen
        window.display();
    }

    delete block;

    return EXIT_SUCCESS;
}