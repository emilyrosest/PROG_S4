#pragma once 

#include "glm/fwd.hpp"
#include <glm/vec2.hpp>



float squaredDistance(const glm::vec2& boidPos, const glm::vec2& otherBoidPos);

glm::vec2 computeVelocity(const glm::vec2& boidPosOrVel, const float& factor, const glm::vec2& averagePos);

glm::vec2 computeAvoidToVelocity(const glm::vec2& boidClose, const float& avoidFactor);

float computeSpeed(const glm::vec2& vel);

bool isVisible(const glm::vec2& boidPos, const glm::vec2& otherBoidPos, const float& visualArea);

