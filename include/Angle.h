/* Angle calculations fro 2D lines */
#pragma once

#include "Line.h"
#include "Plane.h"

namespace cga {
    // Lines could be parellel or intersecting
    float angleLines2D(const Line2D& l1, const Line2D& l2);

    // Lines could be parellel, intersecting or skewed
    float angleLines3D(const Line3D& l1, const Line3D& l2);

    // Angle between a line and a plane normal
    float angleLinePlane(const Line3D& l, const Planef& p);

    // Angle between 2 plane normals
    float anglePlanes(const Planef& p1, const Planef& p2);
}