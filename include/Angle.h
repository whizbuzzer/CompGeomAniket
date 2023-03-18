/* Angle calculations fro 2D lines */
#pragma once

#include "Line.h"
#include "Plane.h"

namespace cga {
    // Both 2D and 3D lines share this part of the calculation:
    template<typename coordinate_type, size_t dimensions>
    static float getAngle(Vector<coordinate_type, dimensions> v1, Vector<coordinate_type, dimensions> v2) {
        // auto l1_mag = l1.get_direction().magnitude();
        // auto l2_mag = l2.get_direction().magnitude();

        auto v1_dot_v2 = dotProduct(v1, v2);

        // float angle = acos(fabs(l1_dot_l2) / (l1_mag * l2_mag));

        /* (l1_mag * l2_mag) need not be considered because both of their
         * magnitudes are 1 due to being normalized
         */
        float angle = acos(fabs(v1_dot_v2));  // * (180 / M_PI);
        return radians2Degrees(angle);
    }

    // Angle calculation when 3 2D/3D points are given:
    template<typename coordinate_type, size_t dimensions>
    static float getAngle(Vector<coordinate_type, dimensions> v0,
                            Vector<coordinate_type, dimensions> v1,
                            Vector<coordinate_type, dimensions> v2) {
        auto left_arm = v0 - v1;
        auto right_arm = v2 - v1;
        return getAngle(left_arm, right_arm);
    }
    
    // Lines could be parellel or intersecting
    float angleLines2D(const Line2D& l1, const Line2D& l2);

    // Lines could be parellel, intersecting or skewed
    float angleLines3D(const Line3D& l1, const Line3D& l2);

    // Angle between a line and a plane normal
    float angleLinePlane(const Line3D& l, const Planef& p);

    // Angle between 2 plane normals
    float anglePlanes(const Planef& p1, const Planef& p2);
}