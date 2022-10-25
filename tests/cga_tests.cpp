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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}