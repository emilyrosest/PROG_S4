#pragma once

#include <corecrt_math.h>
#include <cmath>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "Boid.hpp"


struct WindowLimits {
    float top;
    float bottom;
    float left;
    float right;
};

struct VariablesScene {
    size_t boidsNumber = 50;
    float visualArea = 0.5f;
    float protectedArea = 0.4f;
    float avoidFactor = 0.005f;

    float matchingFactor = 0.0005f;
    float centeringFactor = 0.000005f;
};



class Scene {

private:
    

public:

    WindowLimits _borders;
    VariablesScene _variablesScene;

    Scene(WindowLimits borders) : _borders(borders), _variablesScene(VariablesScene{}) {};


    std::vector<Boid> initialize(const int& boidsNumber) {
        std::vector<Boid> boids;
        for (size_t i = 0; i < boidsNumber; i++) {
            boids.push_back(Boid(glm::vec2(p6::random::number(_borders.left, _borders.right), p6::random::number(_borders.bottom, _borders.top)), glm::vec2(p6::random::number(-1, 1) * 0.005f, p6::random::number(_borders.bottom, _borders.top) * 0.005f)));
        }
        return boids;
    }



};