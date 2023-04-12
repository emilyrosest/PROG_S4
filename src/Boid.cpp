#include "Boid.hpp"
#include <corecrt_math.h>
#include <cmath>
#include <cstdlib>
#include "BoidCalculs.hpp"
#include "glm/ext/quaternion_geometric.hpp"
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
    const float speed = computeSpeed(_vel); 
    if (speed > _simulationParams.maxSpeed)
    {
        // _vel = (_vel / speed) * _simulationParams.maxSpeed; 
        _vel = glm::normalize(_vel) * _simulationParams.maxSpeed; 
    }
    if (speed < _simulationParams.minSpeed)
    {
        //_vel = (_vel / speed) * _simulationParams.minSpeed;
        _vel = glm::normalize(_vel) * _simulationParams.minSpeed;
    }
}

void Boid::applySeparation(const std::vector<Boid>& boids, const SimulationParams& _simulationParams)
{
    glm::vec2 close(0, 0);
    
    for (const Boid& otherBoid : boids)
    {
        if (&otherBoid != this && glm::distance(_pos, otherBoid._pos) < _simulationParams.protectedArea)
        {
            close += _pos - otherBoid._pos;
        }
    }
    _vel += computeAvoidToVelocity(close, _simulationParams.avoidFactor);
}

void Boid::computeAverage(const std::vector<Boid>& boids, const SimulationParams& _simulationParams, const float& factor, std::function<glm::vec2(const Boid&)> computeFunction) {
    glm::vec2 average(0, 0);
    int       neighboors = 0;

    for (const Boid& otherBoid : boids)
    {
        if (this != &otherBoid && isVisible(_pos, otherBoid._pos, _simulationParams.visualArea))
        {
            average += computeFunction(otherBoid); 
            neighboors++;
        }
    }
    if (neighboors > 0)
    {
        average /= neighboors;
        _vel += computeVelocity(computeFunction(*this), factor, average); 
    }
}

void Boid::applyAlignment(const std::vector<Boid>& boids, const SimulationParams _simulationParams)
{
    computeAverage(boids, _simulationParams, _simulationParams.matchingFactor, [](const Boid& boid) {return boid._vel;});
}

void Boid::applyCohesion(const std::vector<Boid>& boids, const SimulationParams _simulationParams)
{
    computeAverage(boids, _simulationParams, _simulationParams.centeringFactor, [](const Boid& boid) {return boid._pos;});
}

void Boid::draw(p6::Context& ctx)
{
    ctx.circle(
        p6::Center{_pos},
        p6::Radius{0.03f}
    );
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
        boids.push_back(Boid(glm::vec2(p6::random::number(_borders.left, _borders.right), p6::random::number(_borders.bottom, _borders.top)), glm::vec2(p6::random::number(_borders.left, _borders.right) * simulationParams.minSpeed, p6::random::number(_borders.bottom, _borders.top) * simulationParams.minSpeed)));
    }
    return boids;
}