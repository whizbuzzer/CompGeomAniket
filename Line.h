#pragma once

#include "Vector.h"
#include "Point.h"

namespace cga {
    class Line3D {
        // Line can be identified by a point and a direction
        Vector3f direction;
        Point3D point;

    public:
        // Default
        Line3D() {}

        // Two points
        Line3D(Point3D& p1, Point3D& p2) {
            point = p1;
            direction = p2 - p1;  // Thanks to overloaded vector operator
            direction.normalize();  // For faster calculations
        }

        // Direction and point
        Line3D(Vector3f dir, Point3D pt) {
            direction = dir;
            point = pt;
        }

        Point3D getPoint() const;
        Vector3f getDirection() const;
    };

    class Line2D {
        Vector2f direction;
        Point2D point;
        Vector2f normal_vec;

    public:
        // Default
        Line2D() {}

        // // Two points
        // Line2D(Point2D& p1, Point2D& p2) {
        //     point = p1;
        //     direction = p2 - p1;  // Thanks to overloaded vector operator
        //     direction.normalize();  // For faster calculations
        // }

        // Direction and point
        Line2D(Vector2f dir, Point2D pt) {
            direction = dir;
            direction.normalize();
            point = pt;
        }

        Vector2f getDirection() const;
        Point2D getPoint() const;
        Vector2f getNormalVector() const;
    };
}