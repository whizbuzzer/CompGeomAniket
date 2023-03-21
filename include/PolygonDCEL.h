/* DCEL Polygon class definition */
#pragma once

// #include <utility>
#include <vector>

#include "Core.h"
#include "EdgeDCEL.h"
#include "FaceDCEL.h"
#include "VertexDCEL.h"
#include "Vector.h"


namespace cga {
    template<typename T, size_t dim>
    class PolygonDCEL {
        typedef Vector<T, dim>      VectorND;

        std::vector<VertexDCEL<T, dim>*> vertex_list;
        // Edge-list could be turned into a map or vector of half-edge pairs
        // std::vector<std::pair<EdgeDCEL<T, dim>*, EdgeDCEL<T, dim>*>> edge_list;
        std::vector<EdgeDCEL<T, dim>*> edge_list;
        std::vector<FaceDCEL<T, dim>*> face_list;

        EdgeDCEL<T, dim>* empty_edge = new EdgeDCEL<T, dim>();

    public:
        // Reference ensures that this object is NEVER null.
        explicit PolygonDCEL(std::vector<VectorND>&);
    };

    template<typename T, size_t dim>
    inline PolygonDCEL<T, dim>::PolygonDCEL(std::vector<VectorND>& points_) {
        if (points_.size() < 3)
            return;

        int size = points_.size();

        for (auto point_:points_) {
            vertex_list.push_back(new VertexDCEL<T, dim>(point_));
        }

        // Defining polygon half-edges:
        for (size_t i = 0; i <= vertex_list.size() - 2; i++) {
            auto half_edge = new EdgeDCEL<T, dim>(vertex_list[i]);
            auto edge_twin = new EdgeDCEL<T, dim>(vertex_list[i + 1]);
            vertex_list[i]->incident_edge = half_edge;

            half_edge->twin = edge_twin;
            edge_twin->twin = half_edge;

            // std::pair<EdgeDCEL<T, dim>*, EdgeDCEL<T, dim>*> edge_pair(half_edge, edge_twin);
            // edge_list.push_back(edge_pair);

            // edge_list.push_back(std::make_pair(half_edge, edge_twin));

            edge_list.push_back(half_edge);
            edge_list.push_back(edge_twin);
        }

        // Definiting start/end half-edges:
        auto half_edge = new EdgeDCEL<T, dim>(vertex_list.back());
        auto edge_twin = new EdgeDCEL<T, dim>(vertex_list.front());

        vertex_list[vertex_list.size() - 1]->incident_edge = half_edge;

        half_edge->twin = edge_twin;
        edge_twin->twin = half_edge;

        edge_list.push_back(half_edge);
        edge_list.push_back(edge_twin);

        // Establishing edge connections:
        for (size_t i = 2; i <= edge_list.size() - 3; i++)  {
            if (i % 2 != 0) {  // Odd case:
                edge_list[i]->next = edge_list[i - 2];
                edge_list[i]->prev = edge_list[i + 2];
            } else {           // Even case:
                edge_list[i]->next = edge_list[i + 2];
                edge_list[i]->prev = edge_list[i - 2];
            }
        }

        // Connecting the ends:

        // First two half-edges:
        // CCW
        edge_list[0]->next = edge_list[2];
        edge_list[0]->prev = edge_list[edge_list.size() - 2];
        // CW
        edge_list[1]->next = edge_list[edge_list.size() - 1];  
        edge_list[1]->prev = edge_list[3];

        // Last two half-edges:
        // CCW
        edge_list[edge_list.size() - 2]->next = edge_list[0];
        edge_list[edge_list.size() - 2]->prev = edge_list[edge_list.size() - 4];
        // CW
        edge_list[edge_list.size() - 1]->next = edge_list[edge_list.size() - 3];
        edge_list[edge_list.size() - 1]->prev = edge_list[1];
        
        // Just like edges, face_list will have face pairs:
        FaceDCEL<T, dim>* f1 = new FaceDCEL<T, dim>();  // Hole in f2
        FaceDCEL<T, dim>* f2 = new FaceDCEL<T, dim>();  // Unbounded face

        // Outer edge of hole would be CCW, but inner edges of unbound face would be CW
        f1->outer = edge_list[0];
        f2->inner.push_back(edge_list[1]);

        face_list.push_back(f1);
        face_list.push_back(f2);

        // Setting incident faces for each outer edge of face f1:
        f1->outer->incident_face = f1;
        EdgeDCEL<T, dim>* edge = f1->outer->next;
        while (edge != f1-> outer) {
            edge->incident_face = f1;
            edge = edge->next;
        }

        // Setting incident faces for each inner edge of face f2:
        f2->inner[0]->incident_face = f2;
        edge = f2->inner[0]->next;
        while (edge != f2->inner[0]) {
            edge->incident_face = f2;
            edge = edge->next;
        }
    }
}