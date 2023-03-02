/* Having certain methods defined separately will help us reduce compile times
 * and the amount of recompilation needed when you change the implementation
 */

#include "Vector.h"


float cga::crossProduct2D(Vector2f v1, Vector2f v2) {
    return (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
}

cga::Vector3f cga::crossProduct3D(Vector3f v1, Vector3f v2) {
    float _x = 0, _y = 0, _z = 0;
    _x = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
    _y = -((v1[X] * v2[Z]) - (v1[Z] * v2[X]));
    _z = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);

    return Vector3f(_x, _y, _z);
}

float cga::scalarTripleProduct(Vector3f v1, Vector3f v2, Vector3f v3) {
    auto v2_cross_v3 = crossProduct3D(v2, v3);
    
    return dotProduct(v1, v2_cross_v3);
}