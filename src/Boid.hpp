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
    float protectedArea = 0.2f;
    float visualArea = 0.5f;
    float avoidFactor = 0.002f;
    float turnFactor = 0.0005f;
    float matchingFactor = 0.0005f;
    float centeringFactor = 0.000005f;
    float maxSpeed = 0.5f;
    float minSpeed = 0.0005f;
};


class Boid {
private:
    glm::vec2     _pos; 
    glm::vec2     _vel; 


public:
    Boid(glm::vec2 pos, glm::vec2 vel)
        : _pos(pos), _vel(vel) {};


    void updatePosition();

    void stayInside(const WindowLimits& borders, const SimulationParams _simulationParams);

    void updateSpeed(const SimulationParams _simulationParams);

    void applySeparation(const std::vector<Boid>& boids, const SimulationParams& _simulationParams);

    void computeAverage(const std::vector<Boid>& boids, const SimulationParams& _simulationParams, const float& factor, std::function<glm::vec2(const Boid&)> computeFunction);

    void applyAlignment(const std::vector<Boid>& boids, const SimulationParams _simulationParams);

    void applyCohesion(const std::vector<Boid>& boids, const SimulationParams _simulationParams);

    void draw(p6::Context& ctx);

    void move(std::vector<Boid>& boids, SimulationParams& simulationParams, WindowLimits& borders);

};


std::vector<Boid> createBoids(SimulationParams simulationParams, WindowLimits _borders);


