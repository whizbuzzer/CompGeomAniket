#include <gtest/gtest.h>

#include "../Angle.h"
#include "../Core.h"
#include "../Vector.h"

/*
 * Reference: https://google.github.io/googletest/quickstart-cmake.html
 */

// TestCase = TestSuite. TestCase is a legacy term and being deprecated.

// TEST(TestSuiteName. TestName)
TEST(AngleTest, AngleLines2DTest1) {
    // Defining point and directions for lines:
    cga::Point2D l1P(0, 3);
    cga::Point2D l2P(0, 5);
    cga::Vector2f l1Dir(2, 1);
    cga::Vector2f l2Dir(-2, 1);

    // Defining lines using above points and directions
    cga::Line2D l1(l1Dir, l1P);
    cga::Line2D l2(l2Dir, l2P);

    auto angle = cga::angleLines2D(l1, l2);
    std::cout << angle << std::endl; 

    EXPECT_TRUE(cga::isEqualD(53.1301, angle));
}

TEST(AngleTest, AngleLines3DTest1) {
    // Defining point and directions for lines:
    cga::Point3D l1P1(1, 5, 5);
    cga::Point3D l2P1(-3, -3, 0);
    cga::Point3D l1P2(1.5, -5, -2);
    cga::Point3D l2P2(3, 5, 2);

    // Defining lines using above points and directions
    cga::Line3D l1(l1P1, l1P2);
    cga::Line3D l2(l2P1, l2P2);

    auto angle = cga::angleLines3D(l1, l2);
    std::cout << angle << std::endl; 

    EXPECT_TRUE(cga::isEqualD(43.0791, angle));
}

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }