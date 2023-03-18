#include "Angle.h"
#include "Core.h"
#include "Vector.h"

int main() {
    // cga::Point2D l1P(0, 3);
    // cga::Point2D l2P(0, 5);
    // cga::Vector2D l1Dir(2, 1);
    // std::cout << "l1 direction magnitude: " << l1Dir.magnitude() << std::endl;
    // cga::Vector2D l2Dir(-2, 1);
    // std::cout << "l2 direction magnitude: " << l2Dir.magnitude() << std::endl;

    // // Defining lines using above points and directions
    // cga::Line2D l1(l1Dir, l1P);
    // cga::Line2D l2(l2Dir, l2P);

    // // auto dp = cga::dotProduct(l1Dir, l2Dir);

    // // std::cout << "Lines dot product: " << dp << std::endl;

    // auto angle = cga::angleLines2D(l1, l2);

    // Defining point and directions for lines:
    cga::Point3D l1P1(1, 5, 5);
    cga::Point3D l2P1(-3, -3, 0);
    cga::Point3D l1P2(1.5, -5, -2);
    cga::Point3D l2P2(3, 5, 2);

    // Defining lines using above points and directions
    cga::Line3D l1(l1P1, l1P2);
    for (int i=0; i < 3; i++) {std::cout << l1.get_direction()[i] << std::endl;}
    // std::cout << l1.get_direction().magnitude() << std::endl;
    cga::Line3D l2(l2P1, l2P2);
    // std::cout << l2.get_direction().magnitude() << std::endl;

    auto angle = cga::angleLines3D(l1, l2);
    std::cout << "the angle is: " << angle << std::endl;
    return 0;
}