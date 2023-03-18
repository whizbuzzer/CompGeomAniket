/* Vertex structure definition */
#pragma once

#include "Edge.h"
#include "Polygon.h"


namespace cga {
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

    // For DCEL ear-clipping triangulation implementation:
    template<typename T=float, size_t dim>
    struct VertexDCEL {
        Vector<float, dim> point;             // Vertex coordinates
        EdgeDCEL<float, dim> *incident_edge = nullptr;  // Edge starting from this vertex

        // Constructor:
        VertexDCEL(Vector<T, dim>& point_): point(point_) {}

        void print_point() {
            std::cout << "(" << point[X] << point[Y];
            if (dim == DIM3)
                std::cout << point[Z];
            std::cout << ")" << std::endl;
        }
    }
}