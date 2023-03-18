#pragma once

#include <corecrt_math.h>
#include <cmath>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"



struct VariablesBoid {
    glm::vec2 _close = glm::vec2(0, 0);
    glm::vec2 _averagePos = glm::vec2(0, 0);
    glm::vec2 _averageVel = glm::vec2(0, 0);
    int _neighboors = 0;

    void update() {
        _close = glm::vec2(0, 0);
        _averagePos = glm::vec2(0, 0);
        _averageVel = glm::vec2(0, 0);
        _neighboors = 0;
    }
};



class Boid {
public:
    Boid(glm::vec2 pos, glm::vec2 vel)
        : _pos(pos), _vel(vel), _variablesBoid(VariablesBoid{}){};


    glm::vec2 _pos;
    glm::vec2 _vel;
    VariablesBoid _variablesBoid;

    void updatePosition() {
        _pos.x += _vel.x;
        _pos.y += _vel.y;
    }

    glm::vec2 distance(const Boid& otherBoid) {
        return glm::vec2(abs(_pos.x - otherBoid._pos.x), abs(_pos.y - otherBoid._pos.y));
    }

    float squaredDistance(const Boid& otherBoid) {
        return distance(otherBoid).x * distance(otherBoid).x + distance(otherBoid).y * distance(otherBoid).y;
    }

    void updateClose(const Boid& otherBoid) {
        _variablesBoid._close += _pos - otherBoid._pos;
    }

    void averageAdd(const Boid& otherBoid) {
        _variablesBoid._averagePos += otherBoid._pos;
        _variablesBoid._averageVel += otherBoid._vel;
    }

    void averageDivide() {
        _variablesBoid._averagePos /= _variablesBoid._neighboors;
        _variablesBoid._averageVel /= _variablesBoid._neighboors;
    }

    void addCenteringToVelocity(const float& centeringFactor) {
        _vel += (_variablesBoid._averagePos - _pos) * centeringFactor;
    }

    void addMatchingToVelocity(const float& matchingFactor) {
        _vel += (_variablesBoid._averagePos - _pos) * matchingFactor;
    }

    void addAvoidToVelocity(const float& avoidFactor) {
        _vel += _variablesBoid._close * avoidFactor;
    }



    void stayInside() {
        float turnFactor = 0.001;
        float left = -0.7;
        float right = 0.7;
        float top = 0.7;
        float bottom = -0.7;
        if (_pos.x < left) {
            _vel.x += turnFactor;
        }
        if (_pos.x > right) {
            _vel.x -= turnFactor;
        }
        if (_pos.y < bottom) {
            _vel.y += turnFactor;
        }
        if (_pos.y > top) {
            _vel.y -= turnFactor;
        }
    }

    

    float getSpeed() {
        return sqrtf(_vel.x * _vel.x + _vel.y * _vel.y);
    }

    void updateSpeed() {
        float maxSpeed = 0.5;
        float minSpeed = 0.0005;
        if (getSpeed() > maxSpeed) {
            _vel.x = ( _vel.x / getSpeed() ) * maxSpeed;
            _vel.y = ( _vel.y / getSpeed() ) * maxSpeed;
        }
        if (getSpeed() < minSpeed) {
            _vel.x = ( _vel.x / getSpeed() ) * minSpeed;
            _vel.y = ( _vel.y / getSpeed() ) * minSpeed;
        }
    }
    


    









    
};

