/* Geometric utilities. Functions for certain operations */
#pragma once

#include "Line.h"
#include "Plane.h"
#include "Point.h"

namespace cga {

    #define ZERO 0.0
    
    /* Area Methods */
    double areaTriangle2D(const Point2D& a,
                          const Point2D& b,
                          const Point2D& c) {
        // Using overloaded operators
        auto AB = b - a;
        auto AC = c - a;

        // When two vectors are known, cross product can be used to find area of
        // the triangle of which those two vectors are constituents
        auto result = crossProduct2D(AB, AC);
        return result / 2;  // Can return positive as well as negative values
    }

    double areaTriangle3D(const Point3D& a,
                          const Point3D& b,
                          const Point3D& c) {
        auto AB = b - a;
        auto AC = c - a;

        auto result = crossProduct3D(AB, AC).magnitude();
        return result / 2;
    }


    /* Orientation methods */
    // Finds orientation of a certain point with respect to a line segment
    int orientation2D(const Point2D& target,
                      const Point2D& line_end1,
                      const Point2D& line_end2) {
        auto area = areaTriangle2D(target, line_end1, line_end2);

        if ((area > 0 && area < TOLERANCE) || (area < 0 && area > TOLERANCE)) {
            area = 0;
        }

        if (area > 0) {
            return LEFT;
        }

        if (area < 0) {
            return RIGHT;
        }

        // For when the line and point are colinear
        Vector2f v1 = line_end2 - line_end1;
        Vector2f v2 = target - line_end1;

        if ((v1[X] * v2[X] < 0) || (v1[Y] * v2[Y] > 0)) {
            return BEHIND;
        }

        if (v1.magnitude() < v2.magnitude()) {
            return BEYOND;
        }

        if (line_end1 == target) {
            return ORIGIN;
        }
        
        if (line_end2 == target) {
            return DESTINATION;
        }

        return BETWEEN;
    }


    /* Collinearity methods */
    // Checks if two vectors/3 points are collinear
    bool isCollinear2D(const Vector2f& v1,
                       const Vector2f& v2) {
        auto k = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
        return isEqualD(ZERO, k);
    }

    bool isCollinear2D(const Point2D& a,
                       const Point2D& b,
                       const Point2D& c) {
        auto ab = b - a;
        auto ac = c - a;

        return isCollinear2D(ab, ac);
    }

    bool isCollinear3D(const Vector3f& v1,
                       const Vector3f& v2) {
        auto k1 = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
        auto k2 = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
        auto k3 = (v1[Z] * v2[X]) - (v1[X] * v2[Z]);

        return isEqualD(ZERO, k1) && isEqualD(ZERO, k2) && isEqualD(ZERO, k3);
    }

    bool isCollinear3D(const Point3D& a,
                       const Point3D& b,
                       const Point3D& c) {
        auto ab = b - a;
        auto ac = c - a;

        return isCollinear3D(ab, ac);
    }


    /* Coplanarity methods */
    // Checks if 3 vectors/4 points are collinear
    bool isCoplanar(const Vector3f& v1,
                    const Vector3f& v2,
                    const Vector3f& v3) {
        float value = scalarTripleProduct(v1, v2, v3);
        return isEqualD(ZERO, value);
    }

    // 3 coplanar vectors have a zero scalar-triple product
    bool isCoplanar(const Point3D& a,
                    const Point3D& b,
                    const Point3D& c,
                    const Point3D& d) {
        auto v1 = b - a;
        auto v2 = c - a;
        auto v3 = d - a;
        return isCoplanar(v1, v2, v3);
    }
}