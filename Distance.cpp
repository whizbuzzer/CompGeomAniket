#include "Distance.h"

// Distance calculation between 2 2D lines
float cga::distance(Line2D& line, Point2D& point) {
    /* t1 = v . (Y - a) */
    // Difference vector
    auto AC = point - line.getPoint();
    auto t1 = dotProduct(line.getDirection(), AC);

    auto xt = line.getPoint() - (line.getDirection() * t1);
    auto dist_vec = xt - point;

    return dist_vec.magnitude();
}

float cga::distance(Point2D& point, Point2D& seg_start, Point2D& seg_end) {
    Line2D line(seg_start, seg_end);
    
    return distance(line, point);
    
    // float temp1 = (seg_end[X] - seg_start[X]) * (seg_start[Y] - point[Y]);
    // float temp2 = (seg_start[X] - point[X]) * (seg_end[Y] - seg_start[Y]);
    // float numerator = fabs(temp1 - temp2);
    // float denominator = sqrt(pow((seg_end[X] - seg_start[X]), 2.0) + \
    // pow((seg_end[Y] - seg_start[Y]), 2.0));
    // return numerator / denominator;
}

// Distance calculation between 2 3D lines
float cga::distance(Line3D& line, Point3D& point) {
    /* t1 = v . (Y - a) */
    // Difference vector
    auto AC = point - line.getPoint();
    auto t1 = dotProduct(line.getDirection(), AC);

    auto xt = line.getPoint() - (line.getDirection() * t1);
    auto dist_vec = xt - point;

    return dist_vec.magnitude();
}

// For rays. For rays, t can be negative.
// In this case, distance between point and ray is the distance between point
// and starting point of the ray
float cga::distance(Point3D& point, Point3D& seg_start, Point3D& seg_end) {
    Line3D line(seg_start, seg_end);
    
    return distance(line, point);

    // auto AB = seg_start - point;  // direction vector of the line
    // auto CA = point - seg_end;
    // Vector3f cross = crossProduct3D(CA, AB);
    
    // float cross_mag = cross.magnitude();
    // float dir_mag = AB.magnitude();

    // return cross_mag / dir_mag;
}

// Distance calculation between a plane and a point
// Could be negative OR positive depending on which side of the plane
// the point lies on.
float cga::distance(Planef& plane, Point3D& point) {
    auto _distance = dotProduct(plane.getNormal(), point) - plane.getd();

    return _distance;
}