/* Angle calculation methods defined to be called 
 * so that header file isn't heavy
 */

#include "Angle.h"
// #include "Core.h"
// #include "Line.h"

// #define PI 3.14159


// using namespace cga;

namespace cga {
    // Both 2D and 3D lines share this part of the calculation:
    template<typename coordinate_type, size_t dimensions>
    static float getAngle(cga::Vector<coordinate_type, dimensions> v1, cga::Vector<coordinate_type, dimensions> v2) {
        // auto l1_mag = l1.getDirection().magnitude();
        // auto l2_mag = l2.getDirection().magnitude();

        auto v1_dot_v2 = dotProduct(v1, v2);

        // float angle = acos(fabs(l1_dot_l2) / (l1_mag * l2_mag));

        /* (l1_mag * l2_mag) need not be considered because both of their
         * magnitudes are 1 due to being normalized
         */
        float angle = acos(fabs(v1_dot_v2));  // * (180 / M_PI);
        return radians2Degrees(angle);
    }

    // Finding angle between 2 2D lines
    float angleLines2D(const Line2D& l1, const Line2D& l2) {
        return getAngle(l1.getDirection(), l2.getDirection());
    }

    // Finding angle between 2 3D lines
    float angleLines3D(const Line3D& l1, const Line3D& l2) {
        // For skewed lines, the angle between them is calculated by drawing a line
        // parellel to l2, which intersects l1, and then calculating the angle 
        // between the new line and l1
        // Implementation will be the same as 2D lines however.
        return getAngle(l1.getDirection(), l2.getDirection());
    }

    float angleLinePlane(const Line3D& l, const Planef& p) {
        auto theta = getAngle(l.getDirection(), p.getNormal());
        return 90 - theta;
    }

    float anglePlanes(const Planef& p1, const Planef& p2) {
        return getAngle(p1.getNormal(), p2.getNormal());
    }
}