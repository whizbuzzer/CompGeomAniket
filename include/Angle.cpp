/* Angle calculation methods defined to be called 
 * so that header file isn't heavy
 */

#include "Angle.h"
#include "Line.h"
#include "Plane.h"
#include "Vector.h"

// #define PI 3.14159


// using namespace cga;

namespace cga {
    // Finding angle between 2 2D lines
    float angleLines2D(const Line2D& l1, const Line2D& l2) {
        return getAngle(l1.get_direction(), l2.get_direction());
    }

    // Finding angle between 2 3D lines
    float angleLines3D(const Line3D& l1, const Line3D& l2) {
        // For skewed lines, the angle between them is calculated by drawing a line
        // parellel to l2, which intersects l1, and then calculating the angle 
        // between the new line and l1
        // Implementation will be the same as 2D lines however.
        return getAngle(l1.get_direction(), l2.get_direction());
    }

    float angleLinePlane(const Line3D& l, const Planef& p) {
        auto theta = getAngle(l.get_direction(), p.get_normal());
        return 90 - theta;
    }

    float anglePlanes(const Planef& p1, const Planef& p2) {
        return getAngle(p1.get_normal(), p2.get_normal());
    }
}