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

    WindowLimits borders {
        .top = 1,
        .bottom = -1,
        .left = -ctx.aspect_ratio(),
        .right = ctx.aspect_ratio()
    };

    Scene scene(borders);


    std::vector<Boid> boids = scene.initialize(scene._variablesScene.boidsNumber);



    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background({0.6f, 0.1f, 0.2f});
        ctx.stroke_weight = false;

        for (size_t i = 0; i < scene._variablesScene.boidsNumber; i++) {
            ctx.circle(
            p6::Center{boids[i]._pos.x, boids[i]._pos.y},
            p6::Radius{0.03f}
            );

            boids[i]._variablesBoid.update();



            for (size_t j = 0; j < scene._variablesScene.boidsNumber; j++) {
                if (j != i && boids[i].distance(boids[j]).x < scene._variablesScene.visualArea && boids[i].distance(boids[j]).y < scene._variablesScene.visualArea) {
                    if (boids[i].squaredDistance(boids[j]) < scene._variablesScene.protectedArea * scene._variablesScene.protectedArea) {
                        boids[i].updateClose(boids[j]);
                    }
                    else if (boids[i].squaredDistance(boids[j]) < scene._variablesScene.visualArea * scene._variablesScene.visualArea) {
                        boids[i].averageAdd(boids[j]);
                        boids[i]._variablesBoid._neighboors ++;
                    }
                }
            }
            if (boids[i]._variablesBoid._neighboors > 0) {
                boids[i].averageDivide();
                boids[i].addMatchingToVelocity(scene._variablesScene.matchingFactor);
                boids[i].addCenteringToVelocity(scene._variablesScene.centeringFactor);
            }
            boids[i].addAvoidToVelocity(scene._variablesScene.avoidFactor);
            boids[i].stayInside();
            boids[i].updateSpeed();
            boids[i].updatePosition();
        }


    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}