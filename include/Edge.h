/* Edge structure definition */
#pragma once

#include "Polygon.h"
#include "Vertex.h"


namespace cga {
    // Basic component of a polygon. Connects two vertices.
    // Edges are often shared between 2 faces in a polygon:
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

    // For DCEL, each edge is made up of 2 half-edges. This is to stay in touch
    // with this project's convention of going through vertices in a
    // counter-clockwise direction
    static int id_ = 0;  // Updates everytime EdgeDCEL is called
    template<typename T, size_t dim>
    struct EdgeDCEL {
        VertexDCEL<T, dim>* origin;  // From where half-edge starts
        EdgeDCEL<T, dim>* twin;      // twin half-edge
        EdgeDCEL<T, dim>* next;      // previous half-edge in CCW direction
        EdgeDCEL<T, dim>* prev;      // next half-edge in CCW direction
        int id;

        // Constructors:
        EdgeDCEL() {
            id = -1;
        }
        EdgeDCEL(VertexDCEL<T, dim>* origin_): origin(origin_) {
            id = id_++;
        }

        // Methods:
        void print_info() {
            std::cout << "Edge pointer" << this << std::endl;
            std::cout << "Edge origin coordinates" << this->origin->print_point() << std::endl;
            std::cout << "Edge twin pointer" << this->twin << std::endl;
            std::cout << "Next edge pointer" << this->next << std::endl;
            std::cout << "Previous edge pointer" << this->prev << std::endl;
            
        }

        // twin is the counter-part of half-edge in opposite direction.
        // So, origin of twin would be destination of half-edge.
        // Provides pointer to this edge's destination.
        VertexDCEL<T, dim> get_destination() {
            return twin->origin;
        }
        
    }
}
