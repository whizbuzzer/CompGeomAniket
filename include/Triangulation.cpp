/* Polygon triangulation methods definitions:
 * https://en.wikipedia.org/wiki/Polygon_triangulation
 */

#include "Edge.h"
#include "GeoUtils.h"
#include "Polygon.h"
#include "Triangulation.h"


namespace cga {
    // Methods changing class members are named with small letters & underscores
    // Changes "is_ear" property of vertices:
    static void initialize_ear_status(Polygon2D* polygon) {
        Vertex2D *prev, *curr, *next;
        auto vertices = polygon->get_vertices();
        curr = vertices[0];

        do {
            prev = curr->prev;
            next = curr->next;
            if (isConvex(prev, curr, next))
                curr->is_ear = isDiagonal(prev, curr);
            curr = curr->next;
        } (while v1 != vertices[0]);
    }

    // Stores the diagonals which form the triangulation:
    void earClippingTriangulate2D(Polygon2D* polygon, std::vector<Edge2D>& edge_list) {
        initialize_ear_status(polygon);

        auto vertex_list = polygon->get_vertices();
        int vertices_left = vertex_list.size();

        // Vertex dynamics will change due to clipping. To record them properly,
        // we will consider 5 vertices: middle one, which is to be clipped/removed,
        // and its 2 neighbors on both sides:
        Vertex *neighbor_l2, *neighbor_l1, *clipped, *neighbor_r1, *neighbor_r2;

        while (vertices_left > 3) {
            for (auto vertex:vertex_list) {
                clipped = vertex;
                if (clipped->is_ear && !clipped->is_processed) {
                    // Establishing node relationships:
                    neighbor_l1 = clipped->prev;
                    neighbor_l2 = neighbor_l1->prev;
                    neighbor_r1 = clipped->next;
                    neighbor_r2 = neighbor_r1->next;

                    // Recording diagonals:
                    edge_list.push_back(Edge2D(*neighbor_l1, *neighbor_r1));

                    // Clipping the node:
                    neighbor_l1->next = neighbor_r1;
                    neighbor_r1->prev = neighbor_l1;

                    // Checking if neighbor_l1 and neighbor_r1 are ears or not:
                    if (isConvex(neighbor_l1->prev, neighbor_l1, neighbor_l1->next))
                        // Using nullptr because polygon vertices are getting altered:
                        neighbor_l1->is_ear = isDiagonal(neighbor_l1->prev, neighbor_l1->next, nullptr);
                    if (isConvex(neighbor_r1->prev, neighbor_r1, neighbor_r1->next))
                        neighbor_r1->is_ear = isDiagonal(neighbor_r1->prev, neighbor_r1->next, nullptr);

                    vertices_left--;
                    if (vertices_left <= 3)
                        break;
                }
            }
        }
    }  // Time complexity: ~O(n^2)
}