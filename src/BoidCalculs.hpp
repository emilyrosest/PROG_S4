#pragma once 

#include "glm/fwd.hpp"
#include <glm/vec2.hpp>



glm::vec2 distance(const glm::vec2 boidPos, const glm::vec2 otherBoidPos);

float squaredDistance(const glm::vec2 boidPos, const glm::vec2 otherBoidPos);

glm::vec2 computeCenteringToVelocity(const glm::vec2& boidPos, const float& centeringFactor, const glm::vec2& averagePos);

glm::vec2 computeMatchingToVelocity(const glm::vec2& boidPos, const float& matchingFactor, const glm::vec2& averagePos);

glm::vec2 computeAvoidToVelocity(const glm::vec2& boidClose, const float& avoidFactor);

float computeSpeed(const glm::vec2 vel);

bool isVisible(const glm::vec2 boidPos, const glm::vec2 otherBoidPos, const float& visualArea);