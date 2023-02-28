#pragma once


#include <corecrt_math.h>

#include <cmath>

class RectangleShape {
public:
    RectangleShape(float x_pos, float y_pos, float x_dest, float y_dest)
        : _x_pos(x_pos), _y_pos(y_pos), _x_dest(x_dest), _y_dest(y_dest), _angle(setAngle()){};

    float _x_pos;
    float _y_pos;
    double _angle;
    float _x_dest;
    float _y_dest;

    void inside(float left, float right) {
        if (_x_pos < left || _x_pos > right || _y_pos < -1 || _y_pos > 1) {
            _angle += 90; //*speed
        }
    };

    double setAngle() const{
        return std::atan2(_y_dest, _x_dest);
    }
    
};