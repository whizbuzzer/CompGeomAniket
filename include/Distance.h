/* Distance methods */
    // Normally, distance between two points can be calculated as:
    // sqrt((x1 - x2)^2 + (y1 - y2)^2)                    (2D) or
    // sqrt((x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2)      (3D)
    // 
    // But a more convenient way would be using vectors:
    // 1. If v is a normalized equation, then mod(v)^2 = 1
    // 2. t1 = v . (Y - a)
    // 3. Find (Y - X(t)) and get its magnitude

#pragma once

#include "Line.h"
#include "Plane.h"
#include "Point.h"


namespace cga {
    // Distance calculation between 2 2D lines
    float distance(Line2D& line, Point2D& point);

    float distance(Point2D& point, Point2D& seg_start, Point2D& seg_end);

    // Distance calculation between 2 3D lines
    float distance(Line3D& line, Point3D& point);

    float distance(Point3D& point, Point3D& seg_start, Point3D& seg_end);

    // Distance calculation between a plane and a point
    float distance(Planef& plane, Point3D& point);
}