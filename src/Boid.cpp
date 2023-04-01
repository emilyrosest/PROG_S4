#include "Boid.hpp"
#include <corecrt_math.h>
#include <cmath>
#include <cstdlib>
#include "BoidCalculs.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

void Boid::updatePosition()
{
    _pos += _vel;
}

void Boid::stayInside(const WindowLimits& borders, const SimulationParams _simulationParams)
{
    if (_pos.x <= borders.left)
    {
        _vel.x += _simulationParams.turnFactor;
    }
    if (_pos.x >= borders.right)
    {
        _vel.x -= _simulationParams.turnFactor;
    }
    if (_pos.y <= borders.bottom)
    {
        _vel.y += _simulationParams.turnFactor;
    }
    if (_pos.y >= borders.top)
    {
        _vel.y -= _simulationParams.turnFactor;
    }
}

void Boid::updateSpeed(const SimulationParams _simulationParams)
{
    const float speed = computeSpeed(_vel); // TODO rename as compute_speed//////////////
    if (speed > _simulationParams.maxSpeed)
    {
        _vel = (_vel / speed) * _simulationParams.maxSpeed; // TODO use vector operations instead of x and y separately/////////
    }
    if (speed < _simulationParams.minSpeed)
    {
        _vel = (_vel / speed) * _simulationParams.minSpeed;
    }
}

void Boid::applySeparation(const std::vector<Boid>& boids, const SimulationParams& _simulationParams)
{
    glm::vec2 close(0, 0);
    
    for (const Boid& otherBoid : boids)
    {
        //if (&otherBoid != this && distance(_pos, otherBoid._pos).x < _simulationParams.visualArea && distance(_pos, otherBoid._pos).y < _simulationParams.visualArea)
        //if (&otherBoid != this && glm::distance(_pos, otherBoid._pos) < _simulationParams.visualArea)
        //{ // TODO don't use visualArea, only protectedArea///////////
        if (&otherBoid != this && squaredDistance(_pos, otherBoid._pos) < _simulationParams.protectedArea * _simulationParams.protectedArea)
        {
            close += _pos - otherBoid._pos; // TODO don't use the  _variablesLoop struct, just a float "close" /////////
        }
        //}
    }
    _vel += computeAvoidToVelocity(close, _simulationParams.avoidFactor); // TODO rename add as compute/////////
}

void Boid::applyAlignment(const std::vector<Boid>& boids, const SimulationParams _simulationParams)
{
    //variablesLoop.update();
    //VariablesLoop variablesLoop{};

    glm::vec2 averagePos(0, 0);
    glm::vec2 averageVel(0, 0);
    int       neighboors = 0;

    // COmpute average velocithy of neighbours
    // compute_average([](const Boid& boid) {return boid._vel}); // TODO refactor to make this possible (when we have seen the lesson on std::function)
    // compute_average([](const Boid& boid) {return boid._pos}); // TODO refactor to make this possible (when we have seen the lesson on std::function)
    for (const Boid& otherBoid : boids)
    {
        //if (this != &otherBoid && glm::distance(_pos, otherBoid._pos) < _simulationParams.visualArea)
        //{
            if (this != &otherBoid && squaredDistance(_pos, otherBoid._pos) < _simulationParams.visualArea * _simulationParams.visualArea)
            { // TODO don't use squareDIstance, only distance??????????????????????
                // averageAddVel(this, otherBoid);
                averageVel += otherBoid._vel;
                neighboors++;
            }
        //}
    }
    if (neighboors > 0)
    {
        averageVel /= neighboors;
        // averageDivideVel(this);
        _vel += computeMatchingToVelocity(this->_pos, _simulationParams.matchingFactor, averagePos);
    }
}

void Boid::applyCohesion(const std::vector<Boid>& boids, const SimulationParams _simulationParams)
{
    //variablesLoop.update();
    //VariablesLoop variablesLoop{};

    glm::vec2 averagePos(0, 0);
    glm::vec2 averageVel(0, 0);
    int       neighboors = 0;

    for (const Boid& otherBoid : boids)
    {
        //if (this != &otherBoid && glm::distance(_pos, otherBoid._pos) < _simulationParams.visualArea)
        //{
            if (this != &otherBoid && squaredDistance(_pos, otherBoid._pos) < _simulationParams.visualArea * _simulationParams.visualArea)
            {
                // averageAddPos(this, otherBoid);
                averagePos += otherBoid._pos;
                neighboors++;
            }
        //}
    }
    if (neighboors > 0)
    {
        // averageDividePos(this);
        averagePos /= neighboors;
        _vel += computeCenteringToVelocity(this->_pos, _simulationParams.centeringFactor, averagePos);
    }
}

void Boid::draw(p6::Context& ctx)
{
    ctx.circle(
        p6::Center{_pos.x, _pos.y},
        p6::Radius{0.03f}
    );

// TODO plutôt mettre ça dans une fonction move()/////////////
/////////////////
    
    ///////////
}

void Boid::move(std::vector<Boid>& boids, SimulationParams& simulationParams, WindowLimits& borders)
{
    applySeparation(boids, simulationParams);
    applyAlignment(boids, simulationParams);
    applyCohesion(boids, simulationParams);

    stayInside(borders, simulationParams);
    updateSpeed(simulationParams);
    updatePosition();
}

std::vector<Boid> createBoids(SimulationParams simulationParams, WindowLimits _borders)
{
    std::vector<Boid> boids;
    for (size_t i = 0; i < simulationParams.boidsNumber; i++)
    {
        boids.push_back(Boid(glm::vec2(p6::random::number(_borders.left, _borders.right), p6::random::number(_borders.bottom, _borders.top)), glm::vec2(p6::random::number(-1, 1) * 0.005f, p6::random::number(_borders.bottom, _borders.top) * 0.005f)));
    }
    return boids;
}