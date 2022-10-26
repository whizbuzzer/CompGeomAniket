#pragma once

#include "Vector.h"
#include "Point.h"

namespace cga {
    
    template<typename coordinate_type>  // dimensions not needed since planes are always 3D
    class Plane {
        // Normal-point form ( n . X = d )
        Vector3f normal;
        float d = 0;  // Ax + By + Cz = D

    public:
        Plane() {}

        Plane(Vector3f& _normal):normal(_normal) {
            normal.normalize();
        }

        // Make sure to calculate _d using normalized normal
        Plane(Vector3f& _normal, float& _d):normal(_normal), d(_d) {
            normal.normalize();
        }

        Plane(Vector3f& _normal, Vector3f& p):normal(_normal) {
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

        Vector3f getNormal() const {
            return normal;
        }
    };

    typedef Plane<float>    Planef;
}