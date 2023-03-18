/* Edge structure definition */
#pragma once

#include "Polygon.h"
#include "Vertex.h"


namespace cga {
    // Basic component of a polygon. Connects two vertices:
    template<typename T, size_t dim>
    struct Edge {
        Vertex<T, dim> v1;
        Vertex<T, dim> v2;
        
        // Constructor:
        Edge(Vertex<T, dim> v1_, Vertex<T, dim> v2_): v1(v1_), v2(v2_) {}

        friend class Polygon<T, dim>;
    }

    typedef Edge<float, DIM2>   Edge2D;
    typedef Edge<float, DIM3>   Edge3D;
}
