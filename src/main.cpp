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

    float left   = -ctx.aspect_ratio();
    float right  = ctx.aspect_ratio();
    float top    = 1;
    float bottom = -1;

    size_t boidsNumber = 50;
    float visualArea = 0.5;
    float protectedArea = 0.4;
    float avoidFactor = 0.005;

    float matchingFactor = 0.0005;
    float centeringFactor = 0.000005;

    

    std::vector<Boid> boids;
    for (size_t i = 0; i < boidsNumber; i++) {
        boids.push_back(Boid(glm::vec2(p6::random::number(left, right), p6::random::number(bottom, top)), glm::vec2(p6::random::number(-1, 1) * 0.005f, p6::random::number(bottom, top) * 0.005f)));
    }


    // Boid myRect = Boid(glm::vec2(p6::random::number(left, right), p6::random::number(bottom, top)), glm::vec2(p6::random::number(left, right), p6::random::number(bottom, top)));
    //Boid myRect = Boid(glm::vec2(p6::random::number(left, right), p6::random::number(bottom, top)), glm::vec2(p6::random::number(-1, 1) * 0.005f, p6::random::number(bottom, top) * 0.005f));


    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background({0.6f, 0.1f, 0.2f});
        ctx.stroke_weight = false;

        for (size_t i = 0; i < boidsNumber; i++) {
            ctx.circle(
            p6::Center{boids[i]._pos.x, boids[i]._pos.y},
            p6::Radius{0.05f}
            );

            glm::vec2 close(0, 0);
            glm::vec2 averagePos(0, 0);
            glm::vec2 averageVel(0, 0);
            int neighboors = 0;


            for (size_t j = 0; j < boidsNumber; j++) {
                if (j != i && boids[i].distanceVec(boids[j]).x < visualArea && boids[i].distanceVec(boids[j]).y < visualArea) {
                    if (boids[i].distanceNumber(boids[j]) < protectedArea * protectedArea) {
                        close += boids[i]._pos - boids[j]._pos;
                    }
                    else if (boids[i].distanceNumber(boids[j]) < visualArea * visualArea) {
                        averagePos += boids[j]._pos;
                        averageVel += boids[j]._vel;

                        neighboors ++;
                    }
                }
                // if (j != i && boids[i].distanceVec(boids[j]).x < protectedArea && boids[i].distanceVec(boids[j]).y < protectedArea) {
                //     close += boids[i]._pos - boids[j]._pos;
                // }
            }

            if (neighboors > 0) {
                averagePos /= neighboors;
                averageVel /= neighboors;

                boids[i]._vel = boids[i]._vel + ((averagePos - boids[i]._pos) * centeringFactor) +  ((averageVel - boids[i]._vel) * matchingFactor);
            }

            boids[i]._vel += close * avoidFactor;

            boids[i].stayInside();
            //std::cout << boids[i].getSpeed() << std::endl;
            boids[i].updateSpeed();
            boids[i].updatePosition();
        }


    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}