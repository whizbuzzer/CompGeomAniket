#include "Line.h"

namespace cga {
    Vector3f Line3D::getDirection() const {
        return direction;
    }

    Point3D Line3D::getPoint() const {
        return point;
    }

    Vector2f Line2D::getDirection() const {
        return direction;
    }

    Point2D Line2D::getPoint() const {
        return point;
    }

    Vector2f Line2D::getNormalVector() const {
        return normal_vec;
    }

}