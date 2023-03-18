/* GeoUtils.h methods definitions */

#include <vector>

#include "Angle.h"
#include "GeoUtils.h"
#include "Intersection.h"

namespace cga {
    #define ZERO 0.0
    
    /* Area Methods */
    /* Gotta templatize these methods */
    // template<typename T, size_t dim>
    // double areaTriangle(const Vector<T, dim>& a,
    //                     const Vector<T, dim>& b,
    //                     const Vector<T, dim>& c) {
    //     // Using overloaded operators
    //     auto AB = b - a;
    //     auto AC = c - a;

    //     if (dim == DIM2) {
    //         auto result = crossProduct2D(AB, AC);
    //     } else if (dim == DIM3) {
    //         auto result = crossProduct3D(AB, AC).magnitude();
    //     }
    //     return result / 2;  // Can return positive as well as negative values
    // }

    double areaTriangle2D(const Point2D& a,
                          const Point2D& b,
                          const Point2D& c) {
        // Using overloaded operators
        auto AB = b - a;
        auto AC = c - a;

        // When two vectors are known, cross product can be used to find area of
        // the triangle of which those two vectors are constituents
        auto result = crossProduct2D(AB, AC);
        return result / 2;  // Can return positive as well as negative values
    }

    double areaTriangle3D(const Point3D& a,
                          const Point3D& b,
                          const Point3D& c) {
        auto AB = b - a;
        auto AC = c - a;

        auto result = crossProduct3D(AB, AC).magnitude();
        return result / 2;
    }

    // typedef double (areaTriangle<float, DIM2>) areaTriangle2D;
    // typedef double (areaTriangle<float, DIM3>) areaTriangle3D;


    /* Orientation methods */
    // Finds orientation of a certain point with respect to a line segment
    int orientation2D(const Point2D& target,
                      const Point2D& line_end1,
                      const Point2D& line_end2) {
        auto area = areaTriangle2D(target, line_end1, line_end2);

        // if ((area > 0 && area < TOLERANCE) || (area < 0 && area > TOLERANCE)) {
        //     area = 0;
        // }

        if (area != 0 && fabs(area) < TOLERANCE) {
            area = 0;
        }

        // For when the line and point are colinear
        Vector2D v1 = line_end1 - target;
        Vector2D v2 = line_end2 - target;

        if (area > 0) {
            return LEFT;
        }

        if (area < 0) {
            return RIGHT;
        }

        if ((v1[X] * v2[X] < 0) || (v1[Y] * v2[Y] > 0)) {
            return BEHIND;
        }

        if (v1.magnitude() < v2.magnitude()) {
            return BEYOND;
        }

        if (line_end1 == target) {
            return ORIGIN;
        }
        
        if (line_end2 == target) {
            return DESTINATION;
        }

        return BETWEEN;
    }

    int orientation3D(const Point3D& target,
                      const Point3D& line_end1,
                      const Point3D& line_end2) {
        auto area = areaTriangle3D(target, line_end1, line_end2);
        if (area != 0 && fabs(area) < TOLERANCE) {
            area = 0;
        }

        // For when the line and point are colinear
        Vector3D v1 = line_end1 - target;
        Vector3D v2 = line_end2 - target;

        if (area > 0) {
            return LEFT;
        }

        if (area < 0) {
            return RIGHT;
        }

        if ((v1[X] * v2[X] < 0) || (v1[Y] * v2[Y] > 0)) {
            return BEHIND;
        }

        if (v1.magnitude() < v2.magnitude()) {
            return BEYOND;
        }

        if (line_end1 == target) {
            return ORIGIN;
        }
        
        if (line_end2 == target) {
            return DESTINATION;
        }

        return BETWEEN;        
    }

    bool left(const Point2D& target,
                const Point2D& line_end1,
                const Point2D& line_end2) {
        return orientation2D(target, line_end1, line_end2) == LEFT;
    }

    bool left(const Line2D& line, const Point2D& target) {
        auto line_normal = line.get_normal_vector();
        auto value1 = dotProduct(line_normal, target);
        auto value2 = dotProduct(line_normal, line.get_point());
        return (value1 - value2) < 0 ? false : true;
    }

    bool right(const Point3D& target,
                const Point3D& line_end1,
                const Point3D& line_end2) {
        return orientation3D(target, line_end1, line_end2) == RIGHT;
    }

    bool leftOrBeyond(const Point2D& target,
                        const Point2D& line_end1,
                        const Point2D& line_end2) {
        auto orientation = orientation2D(target, line_end1, line_end2);
        return (orientation == LEFT || orientation == BEYOND);
    }

    bool leftOrBeyond(const Point3D& target,
                        const Point3D& line_end1,
                        const Point3D& line_end2) {
        auto orientation = orientation3D(target, line_end1, line_end2);
        return (orientation == LEFT || orientation == BEYOND);
    }

    bool leftOrBetween(const Point3D& target,
                        const Point3D& line_end1,
                        const Point3D& line_end2) {
        auto orientation = orientation3D(target, line_end1, line_end2);
        return (orientation == LEFT || orientation == BETWEEN);
    }


    /* Collinearity methods */
    // Checks if two 2D vectors are collinear:
    bool isCollinear2D(const Vector2D& v1,
                       const Vector2D& v2) {
        auto k = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
        return isEqualD(ZERO, k);
    }

    // Checks if three 2D points are collinear:
    bool isCollinear2D(const Point2D& a,
                       const Point2D& b,
                       const Point2D& c) {
        auto ab = b - a;
        auto ac = c - a;

        return isCollinear2D(ab, ac);
    }

    // Checks if two 3D vectors are collinear:
    bool isCollinear3D(const Vector3D& v1,
                       const Vector3D& v2) {
        auto k1 = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
        auto k2 = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
        auto k3 = (v1[Z] * v2[X]) - (v1[X] * v2[Z]);

        return isEqualD(ZERO, k1) && isEqualD(ZERO, k2) && isEqualD(ZERO, k3);
    }

    // Checks if three 3D points are collinear:
    bool isCollinear3D(const Point3D& a,
                       const Point3D& b,
                       const Point3D& c) {
        auto ab = b - a;
        auto ac = c - a;

        return isCollinear3D(ab, ac);
    }


    /* Coplanarity methods */
    // Checks if 3 vectors/4 points are collinear
    bool isCoplanar(const Vector3D& v1,
                    const Vector3D& v2,
                    const Vector3D& v3) {
        float value = scalarTripleProduct(v1, v2, v3);
        return isEqualD(ZERO, value);
    }

    // 3 coplanar vectors have a zero scalar-triple product
    bool isCoplanar(const Point3D& a,
                    const Point3D& b,
                    const Point3D& c,
                    const Point3D& d) {
        auto v1 = b - a;
        auto v2 = c - a;
        auto v3 = d - a;
        return isCoplanar(v1, v2, v3);
    }


    /* Interior checks to check if a line is inside the polygon or not */
    // Vertices would be scanned in a counter-clockwise direction in this project
    static bool insidePolygon(const Vertex2D* v1, const Vertex2D* v2) {
        if (leftOrBeyond(v1->point, v1->next->point, v1->prev->point)) {
            // Convex vertex (inner angle < 180 degrees)
            return (left(v1->point, v2->point, v1->prev->point)
                && left(v2->point, v1->point, v1->next->point));
        }

        // Concave vertex (inner angle > 180 degrees)
        return !(left(v1->point, v2->point, v1->next->point)
            && left(v2->point, v1->point, v1->prev->point));
    }


    /* Diagonal checking methods */
    // Vertices would be scanned in a counter-clockwise direction in this project
    // Checks if a line is a diagonal based on 3 conditions:
    // 1. First line should not intersect with any other edges
    // 2. Start vertex is a convex vertex (inner angle < 180 degrees) and
    // neighboring vertices are on opposite sides of the line.
    // 3. Start vertex is a concave vertex (inner angle > 180 degrees) and
    // line extending from it lies inside the polygon only.
    bool isDiagonal(const Vertex2D* v1, const Vertex2D* v2, Polygon2D* poly=nullptr) {
        bool possibleDiagonal = true;
        std::vector<Vertex2D*> vertices;

        // Based on whether polygon pointer is defined or not, we will record ALL vertices:
        if(poly) {
            vertices = poly->get_vertices();
        } else {
            vertices.push_back((Vertex2D*)v1);  // Ensuring correct datatype is inserted
            auto vertex_ptr = v1->next;  // For populating vertices vector
            while (vertex_ptr != v1) {
                vertices.push_back(vertex_ptr);
                vertex_ptr = vertex_ptr->next;
            }
        }

        // Checking for lines formed by non-adjacent points that could be diagonals:
        Vertex2D *current = vertices[0], *next;

        // Execute statement first, then check the condition:
        do {
            next = current->next;
            // Ensuring that current and next are not neighbors and that an intersction doesn't occur:
            if (current != v1 && next != v1 && current != v2 && next != v2
                && intersection(v1->point, v2->point, current->point, next->point)) {
                    possibleDiagonal = false;
                    break;
            }
            current = next;
        } while (current != vertices[0]);  // Till all points have been covered

        return (possibleDiagonal && insidePolygon(v1, v2) && insidePolygon(v2, v1));
    }


    /* Convex angle check (checking whether interior angle < 180 degrees) */
    bool isConvex(const Vertex2D* v0, const Vertex2D* v1, const Vertex2D* v2) {
        return (getAngle(*v0, *v1, *v2) < 180);
    }
}