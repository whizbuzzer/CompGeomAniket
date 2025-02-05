/* For the most basic operations and aliases that we would need in our library: */
#pragma once

#include <math.h>

namespace cga {
    #define ZERO 0.0

    #define DIM2 2
    #define DIM3 3

    #define X 0
    #define Y 1
    #define Z 2

    #define TOLERANCED 0.0000001  // For doubles
    #define TOLERANCEF 0.0001     // For floats
    #define TOLERANCE2 0.001      // Only 3 decimal places 

    // Use enum when a variable can have a value only from a certain set of
    // values, e.g. DIRECTION (4-8 fixed values) or COLOR (set no. of values)
    enum RELATIVE_POSITION {
        LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
    };

    // For comparing 2 double values. Static ensures that the result does not get reset:
    static bool isEqualD(double x, double y) {
        return fabs(x - y) < TOLERANCED;  // fabs() returns absolute value of an argument
    }

    // For comparing 2 float values. Static ensures that the result does not get reset:
    static bool isEqualF(float x, float y) {
        return fabs(x - y) < TOLERANCEF;  // fabs() returns absolute value of an argument
    }

    // For comparing 2 float values upto 3 decimal places. Static ensures that the result does not get reset:
    static bool isEqual2(float x, float y) {
        return fabs(x - y) < TOLERANCE2;  // fabs() returns absolute value of an argument
    }

    static bool exOr(bool x, bool y) {
        return x ^ y;
    }

    static float radians2Degrees(float radians) {
        return radians * 360 / (2 * M_PI);
    }

    static float degrees2Radians(float degrees) {
        return degrees * (M_PI * 2) / 360;
    }
}