#include <gtest/gtest.h>
#include <iostream>

#include "Angle.h"
#include "Core.h"
#include "Distance.h"
#include "GeoUtils.h"
#include "Intersection.h"
#include "Line.h"
#include "Plane.h"
#include "Point.h"
#include "Vector.h"


/*
 * Reference: https://google.github.io/googletest/quickstart-cmake.html
 */

// TestCase = TestSuite. TestCase is a legacy term and being deprecated.
// TestSuite is the group. TestName is a test in that group.

// TEST(TestSuiteName. TestName)

/* Angle calculation tests */
// Two 2D lines
TEST(AngleTest, AngleLines2DTest1) {
    // Defining point and directions for lines:
    cga::Point2D l1P(0, 3);
    cga::Point2D l2P(0, 5);
    cga::Vector2D l1Dir(2, 1);
    cga::Vector2D l2Dir(-2, 1);

    // Defining lines using above points and directions
    cga::Line2D l1(l1Dir, l1P);
    cga::Line2D l2(l2Dir, l2P);

    auto angle = cga::angleLines2D(l1, l2);
    // std::cout << angle << std::endl; 

    EXPECT_TRUE(cga::isEqualD(53.1301, angle));
}

// Two 3D lines
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
    // std::cout << angle << std::endl; 

    EXPECT_TRUE(cga::isEqualD(43.0791, angle));
}

// 3D line and plane
TEST(AngleTest, AngleLinePlaneTest1) {
    // Defining points and normal for line and plane respectively:
    cga::Point3D l1P1(-3, -4, -5);
    cga::Point3D l1P2(4, 3, 5);
    cga::Vector3D pNormal(-14.26, 9.32, 18.89);

    // Defining line and plane using points and normal respectively
    cga::Line3D l1(l1P1, l1P2);
    cga::Planef p(pNormal);

    auto angle = cga::angleLinePlane(l1, p);
    // std::cout << angle << std::endl;

    EXPECT_TRUE(cga::isEqualD(25.5402, angle));
}

// Two planes
TEST(AngleTest, AnglePlanesTest1) {
    // Defining normals for planes
    cga::Vector3D p1Normal(1.68, 0.42, 2.35);
    cga::Vector3D p2Normal(10.47, -4.44, -4.96);

    // Defining planes using above normals
    cga::Planef p1(p1Normal);
    cga::Planef p2(p2Normal);

    auto angle = cga::anglePlanes(p1, p2);
    // std::cout << "angle between 2 planes" << angle << std::endl;

    EXPECT_TRUE(cga::isEqualD(83.5496, angle));
}


/* Area calculation tests */
// 2D triangle area
TEST(AreaTest, AreaTriangle2DTest1) {
    cga::Point2D A(3.98, 4.14);
    cga::Point2D B(1.2, 1.2);
    cga::Point2D C(6.46, 1.12);

    auto area = cga::areaTriangle2D(A, B, C);
    // std::cout << "triangle area 2D: " << area << std::endl;

    EXPECT_TRUE(cga::isEqualD(7.8434, area));
}

// 3D triangle area
TEST(AreaTest, AreaTriangle3DTest1) {
    cga::Point3D A(-2.8017,7.7327,0);
    cga::Point3D B(-1.0824,6.8348,2.6179);
    cga::Point3D C(-4.7480,5.6637,-1.6388);

    auto area = cga::areaTriangle3D(A, B, C);
    // std::cout << "triangle area 3D: " << area << std::endl;

    EXPECT_TRUE(cga::isEqualD(4.4936, area));
}


/* Collinearity tests */
// If three 2D points are collinear as vectors
TEST(CollinearTest, isCollinear2DTest1) {
    cga::Point2D a(0, 0);
    cga::Point2D b(1, 1);
    cga::Point2D c(2, 2);
    
    cga::Vector2D v1 = b - a;
    cga::Vector2D v2 = c - a;

    EXPECT_TRUE(cga::isEqualF(true, cga::isCollinear2D(v1, v2)));
}

// If three 2D points are collinear
TEST(CollinearTest, isCollinear2DTest2) {
    cga::Point2D a(0, 0);
    cga::Point2D b(1, 1);
    cga::Point2D c(2, 2);
    
    EXPECT_TRUE(cga::isEqualF(true, cga::isCollinear2D(a, b, c)));
}

// If three 3D points are collinear as vectors
TEST(CollinearTest, isCollinear3DTest1) {
    cga::Point3D a(0, 0, 0);
    cga::Point3D b(1, 1, 1);
    cga::Point3D c(2, 2, 2);
    
    cga::Vector3D v1 = b - a;
    cga::Vector3D v2 = c - a;

    EXPECT_TRUE(cga::isEqualF(true, cga::isCollinear3D(v1, v2)));
}

// If three 3D points are collinear
TEST(CollinearTest, isCollinear3DTest2) {
    cga::Point3D a(0, 0, 0);
    cga::Point3D b(1, 1, 1);
    cga::Point3D c(2, 2, 2);
    
    EXPECT_TRUE(cga::isEqualF(true, cga::isCollinear3D(a, b, c)));
}


/* Coplanarity test */
TEST(CoplanarTest, isCoplanarTest1) {
    cga::Point3D a(1, -1, 2);
    cga::Point3D b(3, -2, 5);
    cga::Point3D c(1, 1, 4);
    cga::Point3D d(4, -2, 7);

    EXPECT_TRUE(cga::isEqualD(true, cga::isCoplanar(a, b, c, d)));
}


/* Distance tests */
// 3D point and 3D line
TEST(DistanceTest, DistancePointLine3DTest1) {
    cga::Point3D point_0(-1, -9, 1);

    cga::Point3D line_end_1(-10, 8, 2);
    cga::Point3D line_end_2(8, 5, -3);
    cga::Line3D line_0(line_end_1, line_end_2);

    float distance_1 = cga::distance(line_0, point_0);
    float distance_2 = cga::distance(line_end_1, line_end_2, point_0);

    EXPECT_TRUE(cga::isEqualF(distance_1, distance_2));
}

/* Intersection tests */
// two 2D lines
TEST(LineIntersection, intersection)
{
	cga::Point2D p1, p2 , p_intersect;
	p1.assign(X,5);
	p1.assign(Y, 10);
	p2.assign(X,11);
	p2.assign(Y, 8.4);

	cga::Vector2D v1, v2;
	v1.assign(X, 3);
	v1.assign(Y,-3);
	v2.assign(X,-5);
	v2.assign(Y, -3);

	cga::Line2D l1(p1, v1);
	cga::Line2D l2(p2, v2);

	bool result = cga::intersection(l1, l2, p_intersect);

	EXPECT_TRUE(result);
}

// two planes
// TEST(IntersectionTest, TwoPlanesIntersectionTest1) {
//     cga::Vector3D normal_1(1, 2, 3);
//     cga::Vector3D normal_2(2, 5, -2);

//     float d1 = 6 / normal_1.magnitude();
// 	float d2 = -4 / normal_2.magnitude();

// 	cga::Plane plane_1(normal_1, d1);
// 	cga::Plane plane_2(normal_2, d2);

// 	Line l1;

// 	auto result = intersect(plane_1, plane_2, l1);

// 	EXPECT_TRUE(cga::isEqual2(83.549, result));
// }


/* Orientation test*/
// TEST(OrientationTest, Orientation3DTest1) {
//     Point3D point_ref(-0.8, 0.26, -0.57);
// 	//Point3d point_ref(-0.34, 0, 0);
// 	cga::Point3D p1(-1,-1,-1);
// 	cga::Point3D p2(-1,1,-1);
// 	cga::Point3D p3(-1,1,1);

// 	cga::Vertex3D v1(&p1);
// 	cga::Vertex3D v2(&p2);
// 	cga::Vertex3D v3(&p3);

// 	cga::Face f( &v1,&v2,&v3);
// 	float order = orientation(f, point_ref);
// 	EXPECT_TRUE(order == 2);
// }


// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }