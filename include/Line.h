#pragma once

#include "Vector.h"
#include "Point.h"

namespace cga {
    class Line2D {
        Vector2D direction;
        Point2D point;
        Vector2D normal_vec;

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
        Line2D(Vector2D& dir, Point2D& pt) {
            direction = dir;
            direction.normalize();
            point = pt;
        }

        // Getters
        Vector2D getDirection() const;
        Vector2D getNormalVector() const;
        Point2D getPoint() const;

        // Setters
        void setDirection(Vector2D&);
        void setNormalVector(Vector2D&);
        void setPoint(Point2D&);
    };
    
    class Line3D {
        // Line can be identified by a point and a direction
        Vector3D direction;
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

        // // Direction and point
        // Line3D(Vector3D dir, Point3D pt) {
        //     direction = dir;
        //     point = pt;
        // }

        // Getters
        Vector3D getDirection() const;
        Point3D getPoint() const;

        // Setters
        void setDirection(Vector3D&);
        void setPoint(Point3D&);
    };
}