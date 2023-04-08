/* EdgeDCEL structure definition */
#pragma once

#include <iostream>

#include "FaceDCEL.h"
#include "VertexDCEL.h"


namespace cga {
    static int id_ = 0;  // Updates everytime EdgeDCEL is called
    // For DCEL, each edge is made up of 2 half-edges. This is to stay in touch
    // with this project's convention of going through vertices in a
    // counter-clockwise direction    
    template<typename T, size_t dim>
    struct EdgeDCEL {
        // If edge starts from vertex "V1", then the edge would be named "e1"
        VertexDCEL<T, dim>* origin = nullptr;  // From where half-edge starts
        EdgeDCEL<T, dim>* twin = nullptr;      // twin half-edge
        EdgeDCEL<T, dim>* next = nullptr;      // previous half-edge in CCW direction
        EdgeDCEL<T, dim>* prev = nullptr;      // next half-edge in CCW direction
        FaceDCEL<T, dim>* incident_face = nullptr;
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
        
    };

    typedef EdgeDCEL<float, DIM2>     EdgeDCEL2D;
}