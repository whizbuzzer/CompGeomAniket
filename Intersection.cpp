#include "Core.h"
#include "GeoUtils.h"
#include "Intersection.h"

bool cga::intersection(const cga::Point2D& line1_p1,
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

bool cga::intersection(const cga::Point2D& line1_p1,
                       const cga::Point2D& line1_p2,
                       const cga::Point2D& line2_p1,
                       const cga::Point2D& line2_p2,
                       cga::Point2D& _intersection) {
    Vector2f line1 = line1_p2 - line1_p1;
    Vector2f line2 = line2_p2 - line2_p1;
    
    // Normal vector to line 2
    Vector2f n(line2[Y], -line2[X]);

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

bool cga::intersection(const cga::Line2D& l1,
                       const cga::Line2D& l2,
                       cga::Point2D& _intersection) {
    auto l1_start = l1.getPoint();
    auto l1_end = l1_start + l1.getDirection();

    auto l2_start = l2.getPoint();
    auto l2_end = l2_start + l2.getDirection();

    return intersection(l1_start, l1_end, l2_start, l2_end, _intersection);
}