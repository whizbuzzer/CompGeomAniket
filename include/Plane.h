#pragma once

#include "Vector.h"
#include "Point.h"

namespace cga {
    
    template<typename coordinate_type>  // dimensions not needed since planes are always 3D
    class Plane {
        // Normal-point form ( n . X = d )
        Vector3D normal;
        float d = 0;  // Ax + By + Cz = D

    public:
        Plane() {}

        Plane(Vector3D& _normal):normal(_normal) {
            normal.normalize();
        }

        // Make sure to calculate _d using normalized normal
        Plane(Vector3D& _normal, float& _d):normal(_normal), d(_d) {
            normal.normalize();
        }

        Plane(Vector3D& _normal, Vector3D& p):normal(_normal) {
            normal.normalize();  // For faster calculations
            d = dotProduct(normal, p);
        }

        Plane(Point3D& p1, Point3D& p2, Point3D& p3) {
            /* The three points would help us find the normal (A, B, C),
             * but, we could also use the property of cross-products that
             * cross-product of two vectors is perpendicular to both of them
             */
            auto v12 = p2 - p1;
            auto v13 = p3 - p1;
            normal = crossProduct3D(v12, v13);
            normal.normalize();  // For faster calcula
            
            // d would be dot-product of normal and any point
            d = dotProduct(normal, p1);
            /* dotProduct is part of the Vector template class
             * unlike crossProduct3D. Hence, "dotProduct()" cannot be used 
             * without its prefix"
             */
        }

        /* Operators */
        // Equality check
        bool operator == (const Plane<coordinate_type>& _other) {
            if (normal == _other.normal && isEqualD(d, _other.d)) {
                return true;
            } else {
                return false;
            }
        }

        bool operator != (const Plane<coordinate_type>& _other) {
            return !(*this != _other);
        }

        Vector3D getNormal() const {
            return normal;
        }

        float getD() const {
            return d;
        }
    };

    typedef Plane<float>    Planef;
}