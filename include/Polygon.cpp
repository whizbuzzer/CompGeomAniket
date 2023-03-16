/* Polgon class method definitions */
#include <vector>

#include "Polygon.h"

namespace cga {
    template<typename T, size_t dim>
    std::vector<Vertex<T, dim>*> Polygon<T, dim>::getVertices()  {
        return vertex_list;
    }
}