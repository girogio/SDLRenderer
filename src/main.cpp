#include <iostream>

#include "engine/engine.h"

#define FPS_INTERVAL 1.0

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path to assets directory>" << std::endl;
        exit(-1);
    }

    auto assetsDir = argv[1];

    Engine engine = Engine(assetsDir);

    engine.run();

    return 0;
}
