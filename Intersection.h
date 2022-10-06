#pragma once

#include "Point.h"
#include "Line.h"
#include "Plane.h"

namespace cga {
    
    // For 4 points, 2 points/line
    bool intersection(const cga::Point2D&,
                      const cga::Point2D&,
                      const cga::Point2D&,
                      const cga::Point2D&);

    // For 5 points, 2 points/line + intersection point
    bool intersection(const cga::Point2D&,
                      const cga::Point2D&,
                      const cga::Point2D&,
                      const cga::Point2D&,
                      cga::Point2D&);

    // For 2 lines and a point
    bool intersection(const cga::Line2D&,
                      const cga::Line2D&,
                      cga::Point2D&);
}