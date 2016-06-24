#include "src/Fastcraft.h"

using namespace fastcraft;

int main(int argc, char *args[]) {
    Fastcraft *fastcraft = new Fastcraft();
    if (!fastcraft->init()) {
        return EXIT_FAILURE;
    }

    return fastcraft->start();
}


