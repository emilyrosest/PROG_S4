#include "BoidCalculs.hpp"
#include <glm/glm.hpp>

#include <iostream>


// glm::vec2 distance(const glm::vec2 boidPos, const glm::vec2 otherBoidPos) // TODO return the usual distance (glm::distance)///////////
// {
//     return glm::vec2(abs(boidPos.x - otherBoidPos.x), abs(boidPos.y - otherBoidPos.y));
// }

float squaredDistance(const glm::vec2 boidPos, const glm::vec2 otherBoidPos)
{
    return glm::length(glm::distance(boidPos, otherBoidPos)) * glm::length(glm::distance(boidPos, otherBoidPos));
}

glm::vec2 computeCenteringToVelocity(const glm::vec2& boidPos, const float& centeringFactor, const glm::vec2& averagePos)
{
    return (averagePos - boidPos) * centeringFactor;
}

glm::vec2 computeMatchingToVelocity(const glm::vec2& boidPos, const float& matchingFactor, const glm::vec2& averagePos)
{
    return (averagePos - boidPos) * matchingFactor;
}

glm::vec2 computeAvoidToVelocity(const glm::vec2& boidClose, const float& avoidFactor)
{
    return boidClose * avoidFactor;
}

float computeSpeed(const glm::vec2 vel)
{
    return glm::length(vel);
}

