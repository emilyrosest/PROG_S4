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
//#include "BoidCalculs.hpp"


void updateBorders(WindowLimits& borders, const p6::Context& ctx) {
    borders = { 
        .top = 1,
        .bottom = -1,
        .left = -ctx.aspect_ratio(),
        .right = ctx.aspect_ratio()
    };
}


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

    WindowLimits borders { // TODO à calculer à chaque frame car aspect_ratio peut changer ///////////
        .top = 1,
        .bottom = -1,
        .left = -ctx.aspect_ratio(),
        .right = ctx.aspect_ratio()
    };

    SimulationParams simulationParams {};

    std::vector<Boid> boids = createBoids(simulationParams, borders); // TODO rename as create_boids?//////

    

    // Declare your infinite update loop.
    ctx.update = [&]() {
        updateBorders(borders, ctx);

        ctx.background({0.6f, 0.1f, 0.2f});
        ctx.stroke_weight = false;

        

        for (Boid& boid : boids) {
            boid.draw(ctx); 
            boid.move(boids, simulationParams, borders);

            // ctx.circle(
            // p6::Center{boid._pos},
            // p6::Radius{0.03f}
            // );

            // boid.applySeparation(boids, simulationParams); // TODO rename as apply_separation? //////////
            // boid.applyAlignment(boids, simulationParams);// TODO same//////////
            // boid.applyCohesion(boids, simulationParams); // TODO same////////////////:
            
            // boid.stayInside(borders, simulationParams); // TODO swap params order to make it read nicer///////////
            // boid.updateSpeed(simulationParams);
            // boid.updatePosition();         
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}