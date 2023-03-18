#include "Line.h"

namespace cga {
    Vector3D Line3D::get_direction() const {
        return direction;
    }

    Point3D Line3D::get_point() const {
        return point;
    }

    void Line3D::set_direction(Vector3D& d) {
        direction.assign(X, d[X]);
        direction.assign(Y, d[Y]);
        direction.assign(Z, d[Z]);
    }

    void Line3D::set_point(Point3D& p) {
        point.assign(X, p[X]);
        point.assign(Y, p[Y]);
        point.assign(Z, p[Z]);
    }

    Vector2D Line2D::get_direction() const {
        return direction;
    }

    Vector2D Line2D::get_normal_vector() const {
        return normal_vec;
    }

    Point2D Line2D::get_point() const {
        return point;
    }

    void Line2D::set_direction(Vector2D& d) {
        direction.assign(X, d[X]);
        direction.assign(Y, d[Y]);
    }

    void Line2D::set_normal_vector(Vector2D& n) {
        normal_vec.assign(X, n[X]);
        normal_vec.assign(Y, n[Y]);
    }

    void Line2D::set_point(Point2D& p) {
        point.assign(X, p[X]);
        point.assign(Y, p[Y]);
    }
}