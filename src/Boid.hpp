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

struct SimulationParams { // TODO rename ?//////////////
    int boidsNumber = 50;
    float protectedArea = 0.4f;
    float visualArea = 0.5f;
    float avoidFactor = 0.005f;
    float turnFactor = 0.001f;
    float matchingFactor = 0.0005f;
    float centeringFactor = 0.000005f;
    float maxSpeed = 0.5f;
    float minSpeed = 0.0005f;
};


// struct VariablesLoop {
//     //glm::vec2 close      = glm::vec2(0, 0);
//     glm::vec2 _averagePos = glm::vec2(0, 0);
//     glm::vec2 _averageVel = glm::vec2(0, 0);
//     int       _neighboors = 0;

//     void update() // TODO remove bc not needed bc wi will recreate an insteance in each function that needs it//////////
//     {
//         //close      = glm::vec2(0, 0);
//         _averagePos = glm::vec2(0, 0);
//         _averageVel = glm::vec2(0, 0);
//         _neighboors = 0;
//     }
// };

class Boid {
private:
    glm::vec2     _pos; // TODO private///////////
    glm::vec2     _vel; // TODO private///////////


public:

    Boid(glm::vec2 pos, glm::vec2 vel)
        : _pos(pos), _vel(vel) {};

    

    //VariablesLoop _variablesLoop; // TODO remove///////////

    void updatePosition();

    void stayInside(const WindowLimits& borders, const SimulationParams _simulationParams);

    void updateSpeed(const SimulationParams _simulationParams);

    void applySeparation(const std::vector<Boid>& boids, const SimulationParams& _simulationParams);

    void applyAlignment(const std::vector<Boid>& boids, const SimulationParams _simulationParams);

    void applyCohesion(const std::vector<Boid>& boids, const SimulationParams _simulationParams);

    void draw(p6::Context& ctx);

    void move(std::vector<Boid>& boids, SimulationParams& simulationParams, WindowLimits& borders);

};


std::vector<Boid> createBoids(SimulationParams simulationParams, WindowLimits _borders);


