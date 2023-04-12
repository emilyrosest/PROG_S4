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

    WindowLimits borders { 
        .top = 1.f-0.2f,
        .bottom = -1.f+0.2f,
        .left = -ctx.aspect_ratio()+0.2f,
        .right = ctx.aspect_ratio()-0.2f
    };

    SimulationParams simulationParams {};

    std::vector<Boid> boids = createBoids(simulationParams, borders); 



    

    // Declare your infinite update loop.
    ctx.update = [&]() {
        updateBorders(borders, ctx);

        ctx.background({0.6f, 0.1f, 0.2f});
        ctx.stroke_weight = false;

        ImGui::Begin("Simulation Parameters");
        ImGui::SliderFloat("Protected Area", &simulationParams.protectedArea, 0.1f, 0.5f);
        ImGui::SliderFloat("Visual Area", &simulationParams.visualArea, 0.1f, 0.8f);
        ImGui::SliderFloat("Turn Factor", &simulationParams.turnFactor, 0.1f, 0.5f);
        ImGui::SliderFloat("Avoid Factor", &simulationParams.avoidFactor, 0.001f, 0.01f);
        ImGui::SliderFloat("Matching Factor", &simulationParams.matchingFactor, 0.0001f, 0.001f);
        ImGui::SliderFloat("Centering Factor", &simulationParams.centeringFactor, 0.000001f, 0.0001f);
        ImGui::SliderFloat("Max Speed", &simulationParams.maxSpeed, 0.1f, 0.9f);
        ImGui::SliderFloat("Min Speed", &simulationParams.minSpeed, 0.00001f, 0.5f);
        ImGui::End();
        //ImGui::ShowDemoWindow();


        for (Boid& boid : boids) {
            boid.draw(ctx); 
            boid.move(boids, simulationParams, borders);        
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}