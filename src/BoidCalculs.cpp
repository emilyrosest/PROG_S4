#include "BoidCalculs.hpp"
#include <glm/glm.hpp>



float squaredDistance(const glm::vec2& boidPos, const glm::vec2& otherBoidPos)
{
    return glm::length(glm::distance(boidPos, otherBoidPos)) * glm::length(glm::distance(boidPos, otherBoidPos));
}

glm::vec2 computeVelocity(const glm::vec2& boidPosOrVel, const float& factor, const glm::vec2& averagePos)
{
    return (averagePos - boidPosOrVel) * factor;
}

glm::vec2 computeAvoidToVelocity(const glm::vec2& boidClose, const float& avoidFactor)
{
    return boidClose * avoidFactor;
}

float computeSpeed(const glm::vec2& vel)
{
    return glm::length(vel);
}

bool isVisible(const glm::vec2& boidPos, const glm::vec2& otherBoidPos, const float& visualArea)
{
    return squaredDistance(boidPos, otherBoidPos) < visualArea * visualArea;
}

