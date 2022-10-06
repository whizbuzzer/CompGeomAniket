/* For the most basic operations that we would need in our library: */
#pragma once

#include <math.h>

namespace cga {

    #define TOLERANCE 0.0000001  // For performing an operation till the 7th decimal

    enum RELATIVE_POSITION {
        LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
    };

    // For comparing 2 double values. Static ensures that the result does not get reset:
    static bool isEqualD(double x, double y) {
        return fabs(x - y) < TOLERANCE;  // fabs() returns absolute value of an argument
    }

    static bool _xor(bool x, bool y) {
        return x ^ y;
    }

    static float radians2Degrees(float radians) {
        return radians * (180 / M_PI);
    }

    static float degrees2Radians(float degrees) {
        return degrees * (M_PI / 180);
    }
}