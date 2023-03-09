#include "Core.h"
#include "GeoUtils.h"
#include "Intersection.h"


namespace cga {

    // For 4 points, 2 points/line
    bool intersection(const cga::Point2D& line1_p1,
                      const cga::Point2D& line1_p2,
                      const cga::Point2D& line2_p1,
                      const cga::Point2D& line2_p2) {
        auto l1_l2p1 = cga::orientation2D(line1_p1, line1_p2, line2_p1);
        auto l1_l2p2 = cga::orientation2D(line1_p1, line1_p2, line2_p2);
        auto l2_l1p1 = cga::orientation2D(line2_p1, line2_p2, line1_p1);
        auto l2_l1p2 = cga::orientation2D(line2_p1, line2_p2, line1_p2);

        // Checking if any points from one line lie on the other:
        if (l1_l2p1 == BETWEEN || l1_l2p1 == ORIGIN || l1_l2p1 == DESTINATION ||
            l1_l2p2 == BETWEEN || l1_l2p2 == ORIGIN || l1_l2p2 == DESTINATION ||
            l2_l1p1 == BETWEEN || l2_l1p1 == ORIGIN || l2_l1p1 == DESTINATION ||
            l2_l1p2 == BETWEEN || l2_l1p2 == ORIGIN || l2_l1p2 == DESTINATION) {
            return true;
        }

        return cga::_xor(l1_l2p1 == LEFT, l1_l2p2 == LEFT) && cga::_xor(l2_l1p1 == LEFT, l2_l1p2 == LEFT);
    }

    // For 5 points, 2 points/line + intersection point
    bool intersection(const cga::Point2D& line1_p1,
                      const cga::Point2D& line1_p2,
                      const cga::Point2D& line2_p1,
                      const cga::Point2D& line2_p2,
                      cga::Point2D& _intersection) {
        Vector2D line1 = line1_p2 - line1_p1;
        Vector2D line2 = line2_p2 - line2_p1;
        
        // Normal vector to line 2
        Vector2D n(line2[Y], -line2[X]);

        /* Intersection point:
        * t = dotProduct(n, line2) / dotProduct(n, line1)
        */
        auto denominator = dotProduct(n, line1);

        if (!isEqualD(denominator, 0)) {
            auto num_vector = line2_p1 - line1_p1;
            auto numerator = dotProduct(n, num_vector);
            auto t = numerator / denominator;

            auto _x = line1_p1[X] + t * line1[X];
            auto _y = line1_p1[Y] + t * line1[Y];
            _intersection.assign(X, _x);
            _intersection.assign(Y, _y);
            return true;  
        } else {
            return false;  // Lines are parallel or collinear
        }
    }

    // For 2 lines and a point + intersection point
    bool intersection(const cga::Line2D& l1,
                      const cga::Line2D& l2,
                      cga::Point2D& _intersection) {
        auto l1_start = l1.getPoint();
        auto l1_end = l1_start + l1.getDirection();

        auto l2_start = l2.getPoint();
        auto l2_end = l2_start + l2.getDirection();

        return intersection(l1_start, l1_end, l2_start, l2_end, _intersection);
    }

    // For 1 line and 1 plane + intersection point
    bool intersection(const Planef& plane,
                      const Line3D& line,
                      Point3D& _intersection) {
        auto n = plane.getNormal();
        auto d = line.getDirection();

        // Check if line is parallel to plane:
        auto denom = dotProduct(n, d);

        if (!isEqualD(denom, ZERO)) {
            auto D = plane.getD();        
            auto p = line.getPoint();
            auto t1 = (-1 * dotProduct(n, p) + D) / denom;

            // assign t1 to line to get intersection point:
            _intersection.assign(X, p[X] + t1 * d[X]);
            _intersection.assign(X, p[Y] + t1 * d[Y]);
            _intersection.assign(X, p[Z] + t1 * d[Z]);
            return true;
        } else {
            return false;
        }
    }

    bool intersection(const Planef& p1,
                      Planef& p2,
                      Line3D& _intersection) {
        auto n1 = p1.getNormal();
        auto n2 = p2.getNormal();

        // Check if p1 and p2 are parellel to each other:
        auto direction = crossProduct3D(n1, n2);  // Direction vector of intersecting line

        if (!isEqualD(direction.magnitude(), ZERO)) {
            auto d1 = p1.getD();
            auto d2 = p2.getD();

            // We are storing the normal vectors normalized
            // Hence, their magnitude would be 1
            // So, equations of a and b would be simplified:
            auto n1n2 = dotProduct(n1, n2);
            auto n1n2_2 = n1n2 * n1n2;

            auto a = ((d2 * n1n2) - d1) / (n1n2_2 - 1);
            auto b = ((d1 * n1n2) - d2) / (n1n2_2 -1);

            auto point = (n1 * a) - (n2 * b);
            _intersection.setPoint(point);
            direction.normalize();
            _intersection.setDirection(direction);
            return true;
        } else {
            return false;
        }
    }
}