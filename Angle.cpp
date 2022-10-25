/* Angle calculation methods defined to be called 
 * so that header file isn't heavy
 */

#include "Angle.h"
#include "Core.h"
// #include "Line.h"

// #define PI 3.14159

float cga::angleLines2D(const Line2D& l1, const Line2D& l2) {
    // auto l1_mag = l1.getDirection().magnitude();
    // auto l2_mag = l2.getDirection().magnitude();

    auto l1_dot_l2 = dotProduct(l1.getDirection(), l2.getDirection());

    float angle = acos(fabs(l1_dot_l2));  // * (180 / M_PI);
    std::cout << "angle in radians: " << angle << std::endl;
    float angle_deg = radians2Degrees(angle);
    std::cout << "angle in degrees: " << angle_deg << std::endl;
    return radians2Degrees(angle);
}