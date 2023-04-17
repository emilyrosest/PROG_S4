#include <corecrt_math.h>
#include <stdlib.h>
#include <vcruntime.h>
#include <cmath>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include <chrono>
#include <random>
#include "Boid.hpp"
#include "doctest/doctest.h"
#include "Scene.hpp"


int main(int argc, char* argv[])
{
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    auto ctx = p6::Context{{.title = "Boids"}};
    ctx.maximize_window();

    Scene scene(ctx);   

    ctx.update = [&]() {
        ctx.background({0.6f, 0.1f, 0.2f});
        ctx.stroke_weight = false;

        scene.update(ctx);
    };

    ctx.start();
}