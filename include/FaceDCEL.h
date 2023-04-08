/* Face structure definition */
#pragma once

#include <vector>

#include "EdgeDCEL.h"
#include "Vertex.h"

namespace cga {
    template<typename T, size_t dim>
    class EdgeDCEL;
    // Each face is a sub-polygon of the main polygon.
    // It is the area bounded by a set of half-edges in CCW direction.
    // Face can also have holes and need not be completely filled.
    template<typename T, size_t dim>
    struct FaceDCEL {
        // Pointer to one of CCW outer half-edges of polygon
        cga::EdgeDCEL<T, dim>* outer = nullptr;
        // Pointer to CW inner half-edges which represent holes
        std::vector<EdgeDCEL<T, dim>*> inner;

        //Constructor:
        FaceDCEL() {}

        // Methods:
        std::vector<cga::EdgeDCEL<T, dim>*> get_edges() {
            std::vector<EdgeDCEL<T, dim>*> edge_list;
            if (outer) {
                auto outer_edge_ptr = outer;
                auto outer_next_ptr = outer->next;

                edge_list.push_back(outer_edge_ptr);
                outer_edge_ptr->origin->print_point();
                while (outer_next_ptr != outer_edge_ptr) {
                    outer_next_ptr->origin->print_point();
                    edge_list.push_back(outer_next_ptr);
                    outer_next_ptr = outer_next_ptr->next;
                }            
            }

            return edge_list;
        }

        std::vector<Vector<T, dim>*> get_points() {
            std::vector<EdgeDCEL<T, dim>*> point_list;
            if (outer) {
                auto outer_edge_ptr = outer;
                auto outer_next_ptr = outer->next;

                point_list.push_back(outer_edge_ptr->origin->point);
                outer_edge_ptr->origin->print_point();
                while (outer_next_ptr != outer_edge_ptr) {
                    outer_next_ptr->origin->print_point();
                    point_list.push_back(outer_next_ptr->origin->point);
                    outer_next_ptr = outer_next_ptr->next;
                }            
            }

            return point_list;
        }

        void print_points() {
            if (outer) {
                auto outer_edge_ptr = outer;
                auto outer_next_ptr = outer->next;

                outer_edge_ptr->origin->print_point();
                while (outer_next_ptr != outer_edge_ptr) {
                    outer_next_ptr->origin->print_point();
                    outer_next_ptr = outer_next_ptr->next;
                }
            }
        }
    };
}