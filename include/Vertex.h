/* Vertex structure definition */
#pragma once

#include "Polygon.h"


namespace cga {
    // Forward declaration for friend declaration:
    template<typename T, size_t dim>
    class Polygon; 

    // Basic component of a polygon. We are going to construct the polygon
    // by going through vertices in a counter-clockwise order. It will function
    // like a "Node" in a Doubly Linked-List/Bi-directional Graph:
    template<typename T, size_t dim>
    struct Vertex {
        Vector<T, dim> point;
        Vertex* prev = nullptr;
        Vertex* next = nullptr;
        bool is_ear = false;  // Ear vertex check
        bool is_processed = false;  // Required for triangulation

        // if (dim == DIM2) {
        //     int id = 0;
        // } else if (dim == DIM3) {
        //     bool isEar = false;
        //     bool isProcessed = false;
        // }
    
        // Constructor:
        Vertex(Vertex<T, dim>& _point,
            Vertex<T, dim>* _prev,
            Vertex<T, dim>* _next): point(_point), prev(_prev), next(_next) {}
        
        friend class Polygon<T, dim>;
    };

    typedef Vertex<float, DIM2>     Vertex2D;
    typedef Vertex<float, DIM3>     Vertex3D;
}