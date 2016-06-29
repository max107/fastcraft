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
        unsigned int mouse_sensitivity = 0;
    };

}

#endif //FASTCRAFT_SETTINGS_H
