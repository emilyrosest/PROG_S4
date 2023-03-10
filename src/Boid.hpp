#pragma once

#include <corecrt_math.h>
#include <cmath>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
public:
    Boid(glm::vec2 pos, glm::vec2 vel)
        : _pos(pos), _vel(vel){};


    glm::vec2 _pos;
    glm::vec2 _vel;

    void updatePosition() {
        _pos.x += _vel.x;
        _pos.y += _vel.y;
    }

    glm::vec2 distanceVec(Boid otherBoid) {
        return glm::vec2(abs(_pos.x - otherBoid._pos.x), abs(_pos.y - otherBoid._pos.y));
    }

    float distanceNumber(Boid otherBoid) {
        return distanceVec(otherBoid).x * distanceVec(otherBoid).x + distanceVec(otherBoid).y * distanceVec(otherBoid).y;
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
    


    // void inside(float left, float right) {
    //     if (_x_pos < left || _x_pos > right || _y_pos < -1 || _y_pos > 1) {
    //         _angle += 90; //*speed
    //     }
    // };

    // float setAngle() const{
    //     return std::atan2(_dest.y, _dest.x);
    // }

    // void setDest(float left, float right, float bottom, float top) {
    //     _dest.x = p6::random::number(left, right);
    //     _dest.y = p6::random::number(bottom, top);
    // }

    // void stayInside(float left, float right, float bottom, float top) {
    //     float avoidFactor = 10;
    //     if (_pos.x < left) {
    //         _dest.x += avoidFactor;
    //     }
    //     if (_pos.x > right) {
    //         _dest.x -= avoidFactor;
    //     }
    //     if (_pos.y < bottom) {
    //         _dest.y += avoidFactor;
    //     }
    //     if (_pos.y > top) {
    //         _dest.y -= avoidFactor;
    //     }
    // }

    // void changeDest(float left, float right, float bottom, float top) {
    //     float closeFactor = 0.2;
    //     if (abs(_pos.x - _dest.x) < closeFactor && abs(_pos.y - _dest.y) < closeFactor) {
    //         //setAngle();
    //         setDest(left, right, bottom, top);
    //     }
    // }
    
};