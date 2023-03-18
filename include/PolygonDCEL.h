/* DCEL Polygon class definition */
#pragma once

#include <vector>

#include "Edge.h"
#include "FaceDCEL.h"
#include "Vertex.h"


namespace cga {
    template<typename T, size_t dim>
    class PolygonDCEL {
        std::vector<VertexDCEL<T, dim>*> vertex_list;
        std::vector<EdgeDCEL<T, dim>*> edge_list;
        std::vector<FaceDCEL<T, dim>*> face_list;

        EdgeDCEL<T, dim>* empty_edge = new EdgeDCEL<T, dim>();
    }
}