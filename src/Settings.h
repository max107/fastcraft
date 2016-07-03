//
// Created by Максим Фалалеев on 24/06/16.
//

#ifndef FASTCRAFT_SETTINGS_H
#define FASTCRAFT_SETTINGS_H

namespace fastcraft {

    struct Settings {
        bool fullscreen = false;
        unsigned int width = 1024;
        unsigned int height = 768;

        bool vsync = false;
        unsigned int limit_fps = 60;
        unsigned int mouse_sensitivity = 6;

        bool wireframe = false;
        // fov is a zoom
        // fov - 5 * glfwGetMouseWheel();
        // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
        float fov = 45.f;
        float draw_distance = 1500.f;
    };

}

#endif //FASTCRAFT_SETTINGS_H
