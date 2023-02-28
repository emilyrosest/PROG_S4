#include <stdlib.h>
#include <vcruntime.h>
#include <cmath>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include <chrono>
#include <random>
#include "RectangleShape.hpp"
#include "doctest/doctest.h"


int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    float left  = -ctx.aspect_ratio();
    float right = ctx.aspect_ratio();
    float top = 1;
    float bottom = -1;

    // Declare your infinite update loop.

    unsigned                              seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937                          generator(seed);

    std::uniform_real_distribution<float> uniformRealDistributionX(left, right);
    std::uniform_real_distribution<float> uniformRealDistributionY(bottom, top);


    RectangleShape myRect = RectangleShape(uniformRealDistributionX(generator), uniformRealDistributionY(generator), uniformRealDistributionX(generator), uniformRealDistributionY(generator));


    ctx.update = [&]() {
        ctx.background({0.6f, 0.1f, 0.2f});
        ctx.stroke_weight = false;

        ctx.circle(
            p6::Center{myRect._x_pos, myRect._y_pos},
            p6::Radius{0.1f}
        );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}