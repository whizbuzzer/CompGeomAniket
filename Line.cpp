#include "Line.h"

Vector<coordinate_type, dimensions> Line<coordinate_type, dimensions>::getPoint() {
    return point;
}

template <typename coordinate_type, size_t dimensions>
Vector<coordinate_type, dimensions> Line<coordinate_type, dimensions>::getDirection() {
    return direction;
}