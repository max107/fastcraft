//
// Created by Максим Фалалеев on 24/06/16.
//

#ifndef FASTCRAFT_SETTINGS_H
#define FASTCRAFT_SETTINGS_H

namespace fastcraft {

    struct Settings {
        // todo
        bool fullscreen = false;
        int width = 1024;
        int height = 768;
        bool vsync = true;
        // todo
        int max_fps = 60;
    };

}

#endif //FASTCRAFT_SETTINGS_H
