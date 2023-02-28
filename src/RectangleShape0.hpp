// #pragma once


// #include <corecrt_math.h>
// class RectangleShape {
// public:
//     RectangleShape(float x_pos, float y_pos, float deplX, float deplY, float destX, float destY)
//         : _x_pos(x_pos), _y_pos(y_pos), _deplX(deplX), _deplY(deplY), _destX(destX), _destY(destY){};

//     float _x_pos;
//     float _y_pos;
//     float _angle;
//     float _deplX;
//     float _deplY;
//     float _destX;
//     float _destY;

//     void inside(float left, float right) {
//         if (_x_pos < left || _x_pos > right || _y_pos < -1 || _y_pos > 1) {
//             _angle += 90; //*speed
//         }
//     };

//     bool dehors(float left, float right) {
//         if (_destX < left || _destX > right || _destY < -1 || _destY > 1) {
//             return false;
//         }
//     };

//     void newDest(float abs, float ord) {
//         if (_x_pos == _destX && _y_pos == _destY) {
//             _destX = abs;
//             _destY = ord;
//             std::cout << "atteint" << std::endl;
//         }
//     };

//     float angleFromDest() {
//         return atan((_destY - _y_pos) / (_destX - _x_pos));
//     }
// };