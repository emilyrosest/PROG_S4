#pragma once

#include "Boid.hpp"
#include <p6/p6.h>


class Scene {
private: 
    WindowLimits _borders;
    SimulationParams _simulationParams;
    Behaviors _behaviors;
    std::vector<Boid> _boids;

public:
    explicit Scene(const p6::Context& ctx);

    void updateBorders(const p6::Context& ctx);

    void createWindow();

    void runBoids(p6::Context& ctx);

    void update(p6::Context& ctx);
};