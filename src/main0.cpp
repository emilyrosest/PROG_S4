// #include <stdlib.h>
// #include <vcruntime.h>
// #include <cmath>
// #include "p6/p6.h"
// #define DOCTEST_CONFIG_IMPLEMENT
// #include <chrono>
// #include <random>
// #include "RectangleShape.hpp"
// #include "doctest/doctest.h"


// int main(int argc, char* argv[])
// {
//     { // Run the tests
//         if (doctest::Context{}.run() != 0)
//             return EXIT_FAILURE;
//         // The CI does not have a GPU so it cannot run the rest of the code.
//         const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
//         if (no_gpu_available)
//             return EXIT_SUCCESS;
//     }

//     // Actual app
//     auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
//     ctx.maximize_window();

//     float left  = -ctx.aspect_ratio();
//     float right = ctx.aspect_ratio();

//     // Declare your infinite update loop.

//     unsigned                              seed = std::chrono::system_clock::now().time_since_epoch().count();
//     std::mt19937                          generator(seed);
//     std::uniform_real_distribution<float> uniformRealDistribution(-1, 1);

//     std::vector<float> v_x;
//     for (int i = 0; i < 100; ++i)
//         v_x.push_back(uniformRealDistribution(generator));
//     std::vector<float> v_y;
//     for (int i = 0; i < 100; ++i)
//         v_y.push_back(uniformRealDistribution(generator));

//     // float speed = 0.1f;

//     std::uniform_real_distribution<float> uniformRealDistributionAngle(0, 360);
//     float                                 alpha = uniformRealDistributionAngle(generator);

//     std::uniform_real_distribution<float> uniformRealDistributionDestX(left, right);
//     float                                 destX = uniformRealDistributionDestX(generator);

//     // std::vector<RectangleShape> rectangles;
//     // for(int i=0; i <100; i++){
//     //     rectangles.push_back(RectangleShape(v_x[i], v_y[i], uniformRealDistributionAngle(generator), uniformRealDistribution(generator), uniformRealDistribution(generator)));
//     // }

//     // float deplX = uniformRealDistribution(generator);

//     RectangleShape myRect = RectangleShape(0, 0, uniformRealDistribution(generator), uniformRealDistribution(generator), destX, uniformRealDistribution(generator));
//     myRect._angle         = myRect.angleFromDest();

//     ctx.update = [&]() {
//         ctx.background({0.6f, 0.1f, 0.2f});
//         ctx.stroke_weight = false;

//         ctx.circle(
//             p6::Center{myRect._destX, myRect._destY},
//             p6::Radius{0.01f}
//         );

//         // for(int i=0; i<100; ++i)
//         //     ctx.square(
//         //         p6::Center{uniformRealDistribution(generator), uniformRealDistribution(generator)},
//         //         p6::Radius{0.1f}
//         //     );

//         // for(int i=0; i<100; ++i)
//         //     ctx.square(
//         //         p6::Center{v_x[i] + cos(alpha), v_y[i] + sin(alpha)},
//         //         p6::Radius{0.1f}
//         //     );

//         // for(int i=0; i<100; ++i)
//         //     ctx.square(
//         //         p6::Center{rectangles[i]._x_pos, rectangles[i]._y_pos},
//         //         p6::Radius{0.1f}
//         //     );

//         // for(int i=0; i<100; ++i) {
//         //     rectangles[i]._x_pos += rectangles[i]._deplX* ctx.time() * 0.01f * cos(rectangles[i]._angle); //angle ne sert a rien
//         //     rectangles[i]._y_pos += rectangles[i]._deplY* ctx.time() * 0.01f * sin(rectangles[i]._angle);
//         // }

//         ctx.circle(
//             p6::Center{myRect._x_pos, myRect._y_pos},
//             p6::Radius{0.1f}
//         );
//         myRect._x_pos += myRect._destX * cos(myRect._angle) * 0.005f;
//         myRect._y_pos += myRect._destY * sin(myRect._angle) * 0.005f;

//         myRect.newDest(uniformRealDistribution(generator), uniformRealDistribution(generator));

//         // (myRect._x_pos >= ctx.aspect_ratio() - 0.2|| myRect._x_pos <= -ctx.aspect_ratio() +0.2 || myRect._y_pos >= 1-0.2 || myRect._y_pos <= -1+0.2) ? myRect._x_pos += cos(90) * ctx.time() * 0.001f : myRect._x_pos += cos(myRect._angle) * ctx.time() * 0.001f;
//         // (myRect._x_pos >= ctx.aspect_ratio() - 0.2|| myRect._x_pos <= -ctx.aspect_ratio() +0.2 || myRect._y_pos >= 1-0.2 || myRect._y_pos <= -1+0.2) ? myRect._y_pos += sin(90) * ctx.time() * 0.001f : myRect._y_pos += sin(myRect._angle) * ctx.time() * 0.001f;

//         // myRect.inside(left, right);
//         //  if (myRect._x_pos >= ctx.aspect_ratio() - 0.3|| myRect._x_pos <= -ctx.aspect_ratio() +0.3 || myRect._y_pos >= 1-0.3 || myRect._y_pos <= -1+0.3) {
//         //      // myRect._angle += ctx.time() * 0.001f;
//         //      // std::cout << "ou" << std::endl;
//         //      // for (size_t i = 0; i < 90; i++) {
//         //      //     myRect._x_pos += cos(myRect._angle + i) ;
//         //      //     myRect._y_pos += sin(myRect._angle + i) ;
//         //      // }
//         //      // if (myRect._x_pos >= ctx.aspect_ratio() && myRect._y_pos >= 1 ||
//         //      //     myRect._x_pos >= ctx.aspect_ratio() && myRect._y_pos <= -1 ||
//         //      //     myRect._x_pos <= -ctx.aspect_ratio() && myRect._y_pos >= 1 ||
//         //      //     myRect._x_pos <= -ctx.aspect_ratio() && myRect._y_pos <= -1) {
//         //      //     myRect._x_pos += cos(myRect._angle + 90) * ctx.time() * 0.001f;
//         //      //     myRect._y_pos += sin(myRect._angle + 90) * ctx.time() * 0.001f;
//         //      // }
//         //      myRect._x_pos += cos(myRect._angle + 90) * 0.005f;
//         //      myRect._y_pos += sin(myRect._angle + 90) * 0.005f;
//         //  }
//         //  else {
//         //      myRect._x_pos += cos(myRect._angle) * ctx.time() * 0.001f;
//         //      myRect._y_pos += sin(myRect._angle) * ctx.time() * 0.001f;
//         //  }
//         //  while (myRect._x_pos >= ctx.aspect_ratio() || myRect._x_pos <= -ctx.aspect_ratio() || myRect._y_pos >= 1 || myRect._y_pos <= -1) {
//         //      // myRect._x_pos += cos(myRect._angle + 10) * ctx.time() * 0.001f;
//         //      // myRect._y_pos += sin(myRect._angle + 10) * ctx.time() * 0.001f;
//         //       myRect._angle += 90;
//         //  }
//     };

//     // Should be done last. It starts the infinite loop.
//     ctx.start();
// }