
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "src/Block.h"
#include "src/Player.h"
#include "src/Camera.h"

using namespace fastcraft;

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);

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
    window.setActive();

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    glDisable(GL_LIGHTING);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    Camera *camera = new Camera();
    Player* player = new Player(camera);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    Block *block = new Block();

    // Start game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
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

        player->handleUpdate(clock.getElapsedTime());

        // Draw the background
        window.pushGLStates();
        window.draw(background);
        window.popGLStates();

        // Clear the depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        block->setPosition(0, 0, -100);
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