/* VertexDCEL structure definition*/
#pragma once

#include <iostream>

#include "EdgeDCEL.h"
#include "Vector.h"


namespace cga {
    // For DCEL ear-clipping triangulation implementation:
    template<typename T=float, size_t dim>
    struct VertexDCEL {
        Vector<float, dim> point;             // Vertex coordinates
        // Edge starting from this vertex.
        // Set to nullptr in case it has not been constructed yet:
        EdgeDCEL<float, dim> *incident_edge = nullptr;  

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