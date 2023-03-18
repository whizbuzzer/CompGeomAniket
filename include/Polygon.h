/* Contains both simple and Double Connected Edge-List (DCEL) representation
 * of a polygon
 */

#pragma once

#include <vector>

#include "Core.h"
#include "Point.h"
#include "Vector.h"
#include "Vertex.h"

namespace cga {
    // Polygon class:
    template<typename T, size_t dim>
    class Polygon {
        // Normally would need to store ALL component vertices, but each vertex
        // already has a pointer to both its neighbors, so vertex storage
        // is not necessary. But we will still keep the vertex list so that we
        // could reset the polygon in case the vertex pointers (prev/next) change.
        // Also using heap memory (pointers) as it is larger than stack memory
        // and so stack overflow can be avoided:
        std::vector<Vertex<T, dim>*> vertex_list;
    public:
        // Constructor:
        Polygon(std::vector<Vector<T, dim>>& points) {
            if (points.size() < 3) {
                std::cout << "Number of points should be greater than 3" << std::endl;
                return;
            }

            const int size = points.size();

            // Populating the polygon:
            for (auto _point:points) {
                // Each point is a vector, and we need it as a vertex:
                vertex_list.push_back(new Vertex(_point));
            }
            for (size_t i = 0; i < size; i++) {
                // if (i == 0) {
                //     vertex_list[i].prev = &vertex_list[size - 1];
                //     vertex_list[i].next = &vertex_list[1];
                // } else if (i == size - 1) {
                //     vertex_list[i].prev = &vertex_list[i - 1];
                //     vertex_list[i].next = &vertex_list[0];
                // } else {
                //     vertex_list[i].prev = &vertex_list[i - 1];
                //     vertex_list[i].next = &vertex_list[i + 1];
                // }

                vertex_list[i].next = &vertex_list[(i + 1) % size];

                if (i == 0) {
                    vertex_list[i].prev = vertex_list[size - 1];
                } else {
                    vertex_list[i].prev = vertex_list[i - 1];
                }
            }
        };
        
        std::vector<Vertex<T, dim>*> get_vertices();
    };

    typedef Polygon<float, DIM2>    Polygon2D;
    typedef Polygon<float, DIM3>    Polygon3D;
}