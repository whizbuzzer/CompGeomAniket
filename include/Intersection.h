#pragma once

#include "Line.h"
#include "Plane.h"
#include "Point.h"

namespace cga {
    
    // For 4 points, 2 points/line
    bool intersection(const Point2D&,
                      const Point2D&,
                      const Point2D&,
                      const Point2D&);

    // For 5 points, 2 points/line + intersection point
    bool intersection(const Point2D&,
                      const Point2D&,
                      const Point2D&,
                      const Point2D&,
                      Point2D&);

    // For 2 lines and a point + intersection point
    bool intersection(const Line2D&,
                      const Line2D&,
                      Point2D&);

    // For 1 line and 1 plane + intersection point
    bool intersection(const Planef&,
                      const Line3D&,
                      Point3D&);
}