#pragma once

#include "./Vector.h"

namespace cga {
    
    template <typename coordinate_type, size_t dimensions = DIM3>
    class Line {
        // Line can be identified by a point and a direction
        Vector<coordinate_type, dimensions> point;
        Vector<coordinate_type, dimensions> direction;

    public:
        Line() {}

        Line(Vector<coordinate_type, dimensions>& p1, Vector<coordinate_type, dimensions>& p2) {
            direction = p2 - p1;  // Thanks to overloaded vector operator
            direction.normalize();  // For faster calculations
            point = p1;
        }

        Vector<coordinate_type, dimensions> getPoint() const;
        Vector<coordinate_type, dimensions> getDirection() const;
    };

    template <typename coordinate_type, size_t dimensions>
    Vector<coordinate_type, dimensions> Line<coordinate_type, dimensions>::getPoint() const {
        return point;
    }

    template <typename coordinate_type, size_t dimensions>
    Vector<coordinate_type, dimensions> Line<coordinate_type, dimensions>::getDirection() const {
        return direction;
    }

    // 2D and 3D lines
    typedef Line<float, DIM2> Line2D;
    typedef Line<float, DIM3> Line3D;
}