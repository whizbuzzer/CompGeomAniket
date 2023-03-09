#include "Line.h"

namespace cga {
    Vector3D Line3D::getDirection() const {
        return direction;
    }

    Point3D Line3D::getPoint() const {
        return point;
    }

    void Line3D::setDirection(Vector3D& d) {
        direction.assign(X, d[X]);
        direction.assign(Y, d[Y]);
        direction.assign(Z, d[Z]);
    }

    void Line3D::setPoint(Point3D& p) {
        point.assign(X, p[X]);
        point.assign(Y, p[Y]);
        point.assign(Z, p[Z]);
    }

    Vector2D Line2D::getDirection() const {
        return direction;
    }

    Vector2D Line2D::getNormalVector() const {
        return normal_vec;
    }

    Point2D Line2D::getPoint() const {
        return point;
    }

    void Line2D::setDirection(Vector2D& d) {
        direction.assign(X, d[X]);
        direction.assign(Y, d[Y]);
    }

    void Line2D::setNormalVector(Vector2D& n) {
        normal_vec.assign(X, n[X]);
        normal_vec.assign(Y, n[Y]);
    }

    void Line2D::setPoint(Point2D& p) {
        point.assign(X, p[X]);
        point.assign(Y, p[Y]);
    }
}