/* Angle calculation methods defined to be called 
 * so that header file isn't heavy
 */

#include "Angle.h"
#include "Core.h"

// #define PI 3.14159

float cga::AngleLines2D(const Line2D& l1, const Line2D& l2) {
    auto l1_mag = l1.getDirection().magnitude();
    auto l2_mag = l2.getDirection().magnitude();

    auto l1_dot_l2 = dotProduct(l1.getDirection(), l2.getDirection());

    float angle = acos(fabs(l1_dot_l2) / (l1_mag * l2_mag)) * (180/PI);
    return radians2Degrees(angle);
}