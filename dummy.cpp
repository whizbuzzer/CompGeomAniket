#include "Angle.h"
#include "Core.h"
#include "Vector.h"

int main() {
    cga::Point2D l1P(0, 3);
    cga::Point2D l2P(0, 5);
    cga::Vector2f l1Dir(2, 1);
    std::cout << "l1 direction magnitude: " << l1Dir.magnitude() << std::endl;
    cga::Vector2f l2Dir(-2, 1);
    std::cout << "l2 direction magnitude: " << l2Dir.magnitude() << std::endl;

    // Defining lines using above points and directions
    cga::Line2D l1(l1Dir, l1P);
    cga::Line2D l2(l2Dir, l2P);

    // auto dp = cga::dotProduct(l1Dir, l2Dir);

    // std::cout << "Lines dot product: " << dp << std::endl;

    auto angle = cga::angleLines2D(l1, l2);
    std::cout << "the angle is: " << angle << std::endl;
    return 0;
}