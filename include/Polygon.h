/* Contains both simple and Double Connected Edge-List (DCEL) representation
 * of a polygon
 */

#pragma once

#include <vector>

#include "Core.h"
#include "Point.h"
#include "Vector.h"

namespace cga {
    // Forward declaration for friend declaration:
    template<typename T, size_t dim> class Polygon;

    // Basic component of a polygon. We are going to construct the polygon
    // by going through vertices in a counter-clockwise order. It will function
    // like a "Node" in a Doubly Linked-List/Bi-directional Graph:
    template<typename T, size_t dim>
    struct Vertex {
        Vector<T, dim> point;
        Vertex* prev = nullptr;
        Vertex* next = nullptr;

        // if (dim == DIM2) {
        //     int id = 0;
        // } else if (dim == DIM3) {
        //     bool isEar = false;
        //     bool isProcessed = false;
        // }
    public:
        // Constructor:
        Vertex(Vertex<T, dim>& _point,
            Vertex<T, dim>* _prev,
            Vertex<T, dim>* _next): point(_point), prev(_prev), next(_next) {}
        friend class Polygon<T, dim>;
    };

    typedef Vertex<float, DIM2>     Vertex2D;
    typedef Vertex<float, DIM3>     Vertex3D;


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
        
        std::vector<Vertex<T, dim>*> getVertices();
    };

    typedef Polygon<float, DIM2>    Polygon2D;
    typedef Polygon<float, DIM3>    Polygon3D;
}