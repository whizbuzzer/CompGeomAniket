/* Polygon triangulation methods declarations:
 * https://en.wikipedia.org/wiki/Polygon_triangulation
 */

#include <vector>

#include "Edge.h"
#include "Polygon.h"


namespace cga {
    // Methods changing class members are named with small letters & underscores
    // Changes "is_ear" property of vertices:
    static void initialize_ear_status(Polygon2D* polygon);

    // Stores the diagonals which form the triangulation:
    void earClippingTriangulate2D(Polygon2D* polygon, std::vector<Edge2D>& edge_list);
}