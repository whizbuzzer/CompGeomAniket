/* Geometric utilities. Functions for certain operations */
#pragma once

#include "Line.h"
#include "Point.h"
#include "Polygon.h"
#include "Vector.h"

namespace cga {
    /* Area Methods */
    double areaTriangle2D(const Point2D& a,
                          const Point2D& b,
                          const Point2D& c);

    double areaTriangle3D(const Point3D& a,
                          const Point3D& b,
                          const Point3D& c);


    /* Orientation methods */
    // Finds orientation of a certain point with respect to a line segment
    int orientation2D(const Point2D& target,
                      const Point2D& line_end1,
                      const Point2D& line_end2);

    int orientation3D(const Point3D& target,
                      const Point3D& line_end1,
                      const Point3D& line_end2);

    bool left(const Point2D& target,
                const Point2D& line_end1,
                const Point2D& line_end2);

    bool left(const Line2D& l, const Point2D& p);

    bool right(const Point3D& target,
                const Point3D& line_end1,
                const Point3D& line_end2);

    bool leftOrBeyond(const Point2D& target,
                        const Point2D& line_end1,
                        const Point2D& line_end2);

    bool leftOrBeyond(const Point3D& target,
                        const Point3D& line_end1,
                        const Point3D& line_end2);

    bool leftOrBetween(const Point3D& target,
                        const Point3D& line_end1,
                        const Point3D& line_end2);


    /* Collinearity methods */
    // Checks if two 2D vectors are collinear:
    bool isCollinear2D(const Vector2D& v1,
                       const Vector2D& v2);

    // Checks if three 2D points are collinear:
    bool isCollinear2D(const Point2D& a,
                       const Point2D& b,
                       const Point2D& c);

    // Checks if two 3D vectors are collinear:
    bool isCollinear3D(const Vector3D& v1,
                       const Vector3D& v2);

    // Checks if three 3D points are collinear:
    bool isCollinear3D(const Point3D& a,
                       const Point3D& b,
                       const Point3D& c);


    /* Coplanarity methods */
    // Checks if 3 vectors/4 points are collinear
    bool isCoplanar(const Vector3D& v1,
                    const Vector3D& v2,
                    const Vector3D& v3);

    // 3 coplanar vectors have a zero scalar-triple product
    bool isCoplanar(const Point3D& a,
                    const Point3D& b,
                    const Point3D& c,
                    const Point3D& d);


    /* Interior checks to check if a line is inside the polygon or not */
    static bool insidePolygon(Vertex2D* v1, Vertex2D* v2);

    /* Diagonal checking methods */
    // Vertices would be scanned in a counter-clockwise direction in this project
    // Checks if a line is a diagonal based on 3 conditions:
    // 1. First line should not intersect with any other edges
    // 2. Start vertex is a convex vertex (inner angle < 180 degrees) and
    // neighboring vertices are on opposite sides of the line.
    // 3. Start vertex is a concave vertex (inner angle > 180 degrees) and
    // line extending from it lies inside the polygon only.
    bool isDiagonal(const Vertex2D* v1, const Vertex2D* v2, Polygon2D* poly=nullptr);

}