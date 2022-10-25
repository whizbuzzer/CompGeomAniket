/* Angle calculations fro 2D lines */
#pragma once

#include "Line.h"
#include "Plane.h"

namespace cga {
    float angleLines2D(const Line2D& l1, const Line2D& l2);
}