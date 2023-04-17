#pragma once

#include <corecrt_math.h>
#include <cmath>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "BoidCalculs.hpp"


struct WindowLimits {
    float top{};
    float bottom{};
    float left{};
    float right{};
};

struct SimulationParams { 
    int boidsNumber = 50;
    float protectedArea = 0.3f;
    float visualArea = 0.7f;
    float avoidFactor = 0.0005f;
    float turnFactor = 0.0005f;
    float matchingFactor = 0.0005f;
    float centeringFactor = 0.0005f;
    float maxSpeed = 0.5f;
    float minSpeed = 0.0005f;
};

struct Behaviors {
    bool separation = true;
    bool allignment = true;
    bool cohesion = true;
};


class Boid {
private:
    glm::vec2     _pos; 
    glm::vec2     _vel; 


public:
    Boid(glm::vec2 pos, glm::vec2 vel)
        : _pos(pos), _vel(vel) {};


    void updatePosition();

    void stayInside(const WindowLimits& borders, const SimulationParams& simulationParams);

    void updateSpeed(const SimulationParams& simulationParams);

    void applySeparation(const std::vector<Boid>& boids, const SimulationParams& simulationParams);

    void computeAverage(const std::vector<Boid>& boids, const SimulationParams& simulationParams, const float& factor, std::function<glm::vec2(const Boid&)> computeFunction);

    void applyAlignment(const std::vector<Boid>& boids, const SimulationParams& simulationParams);

    void applyCohesion(const std::vector<Boid>& boids, const SimulationParams& simulationParams);

    void draw(p6::Context& ctx);

    void move(std::vector<Boid>& boids, const SimulationParams& simulationParams, const WindowLimits& borders, Behaviors& behaviors);

};


std::vector<Boid> createBoids(const SimulationParams& simulationParams, const WindowLimits& borders);


