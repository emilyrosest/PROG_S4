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

void Boid::stayInside(const WindowLimits& borders, const SimulationParams& simulationParams)
{
    if (_pos.x <= borders.left)
    {
        _vel.x += simulationParams.turnFactor;
    }
    if (_pos.x >= borders.right)
    {
        _vel.x -= simulationParams.turnFactor;
    }
    if (_pos.y <= borders.bottom)
    {
        _vel.y += simulationParams.turnFactor;
    }
    if (_pos.y >= borders.top)
    {
        _vel.y -= simulationParams.turnFactor;
    }
}

void Boid::updateSpeed(const SimulationParams& simulationParams)
{
    const float speed = computeSpeed(_vel);
    if (speed > simulationParams.maxSpeed)
    {
        _vel = glm::normalize(_vel) * simulationParams.maxSpeed;
    }
    if (speed < simulationParams.minSpeed)
    {
        _vel = glm::normalize(_vel) * simulationParams.minSpeed;
    }
}

void Boid::applySeparation(const std::vector<Boid>& boids, const SimulationParams& simulationParams)
{
    glm::vec2 close(0, 0);

    for (const Boid& otherBoid : boids)
    {
        if (&otherBoid != this && glm::distance(_pos, otherBoid._pos) < simulationParams.protectedArea)
        {
            close += _pos - otherBoid._pos;
        }
    }
    _vel += computeAvoidToVelocity(close, simulationParams.avoidFactor);
}

void Boid::computeAverage(const std::vector<Boid>& boids, const SimulationParams& simulationParams, const float& factor, std::function<glm::vec2(const Boid&)> computeFunction)
{
    glm::vec2 average(0, 0);
    int       neighboors = 0;

    for (const Boid& otherBoid : boids)
    {
        if (this != &otherBoid && isVisible(_pos, otherBoid._pos, simulationParams.visualArea))
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

void Boid::applyAlignment(const std::vector<Boid>& boids, const SimulationParams& simulationParams)
{
    computeAverage(boids, simulationParams, simulationParams.matchingFactor, [](const Boid& boid) { return boid._vel; });
}

void Boid::applyCohesion(const std::vector<Boid>& boids, const SimulationParams& simulationParams)
{
    computeAverage(boids, simulationParams, simulationParams.centeringFactor, [](const Boid& boid) { return boid._pos; });
}

void Boid::draw(p6::Context& ctx)
{
    ctx.circle(
        p6::Center{_pos},
        p6::Radius{0.03f}
    );
}

void Boid::move(std::vector<Boid>& boids, const SimulationParams& simulationParams, const WindowLimits& borders, Behaviors& behaviors)
{
    if (behaviors.separation) {
        applySeparation(boids, simulationParams);
    }
    
    if (behaviors.allignment) {
        applyAlignment(boids, simulationParams);
    }

    if (behaviors.cohesion) {
        applyCohesion(boids, simulationParams);
    }
    
    stayInside(borders, simulationParams);
    updateSpeed(simulationParams);
    updatePosition();
}

std::vector<Boid> createBoids(const SimulationParams& simulationParams, const WindowLimits& borders)
{
    std::vector<Boid> boids;
    boids.reserve(simulationParams.boidsNumber);
    
    for (int i = 0; i < simulationParams.boidsNumber; i++)
    {
        boids.emplace_back(glm::vec2(p6::random::number(borders.left, borders.right), p6::random::number(borders.bottom, borders.top)), glm::vec2(p6::random::number(borders.left, borders.right) * simulationParams.minSpeed, p6::random::number(borders.bottom, borders.top) * simulationParams.minSpeed));
    }
    return boids;
}