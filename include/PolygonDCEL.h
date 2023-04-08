/* DCEL Polygon class definition */
#pragma once

#include <memory>
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

        // Smart pointers have automatic memory management.
        // No need to worry about having a delete
        std::shared_ptr<EdgeDCEL<T, dim>> empty_edge = std::make_shared<cga::EdgeDCEL<T, dim>>();

    public:
        // Reference ensures that this object is NEVER null.
        explicit PolygonDCEL(std::vector<VectorND>&);

        // Gets all edges starting from a certain vertex
        void getEdgesFromVertex(VertexDCEL<T, dim>* v,
                                std::vector<EdgeDCEL<T, dim>*> edges_from_v);

        // This method initializes the edges pointers that are needed for
        // splitting the polygon along an edge given the half-edge origins and
        // the half-edges. All of them are part of the same face
        void getEdgesForSplittingPolygon(VertexDCEL<T, dim>* v1,
                                         VertexDCEL<T, dim>* v2,
                                         EdgeDCEL<T, dim>** edge_from_v1,
                                         EdgeDCEL<T, dim>** edge_from_v2);

        // Splits the polygon along edge between vertices v1 and v2 given that
        // this edge lies completely inside the polygon
        bool split(VertexDCEL<T, dim>* v1, VertexDCEL<T, dim>* v2);

        // Joins two face split by the edge between vertices v1 and v2
        bool join(VertexDCEL<T, dim>* v1, VertexDCEL<T, dim>* v2);

        std::vector<VertexDCEL<T, dim>*> get_vertex_list();
        
        std::vector<EdgeDCEL<T, dim>*> get_edge_list();

        std::vector<FaceDCEL<T, dim>*> get_face_list();

        // Returns pointer to a vertex given its point coordinates:
        VertexDCEL<T, dim>* get_vertex(VectorND& point_);
    };

    template<typename T, size_t dim>
    inline PolygonDCEL<T, dim>::PolygonDCEL(std::vector<VectorND>& points_) {
        if (points_.size() < 3)
            return;

        int size = points_.size();

        for (auto point_:points_) {
            vertex_list.push_back(std::make_shared<cga::VertexDCEL<T, dim>>(point_));
        }

        // Defining polygon half-edges:
        for (size_t i = 0; i <= vertex_list.size() - 2; i++) {
            auto half_edge = std::make_shared<EdgeDCEL<T, dim>>(vertex_list[i]);
            auto edge_twin = std::make_shared<EdgeDCEL<T, dim>>(vertex_list[i + 1]);
            vertex_list[i]->incident_edge = half_edge.get;

            half_edge->twin = edge_twin;
            edge_twin->twin = half_edge;

            // std::pair<EdgeDCEL<T, dim>*, EdgeDCEL<T, dim>*> edge_pair(half_edge, edge_twin);
            // edge_list.push_back(edge_pair);

            // edge_list.push_back(std::make_pair(half_edge, edge_twin));

            edge_list.push_back(half_edge);
            edge_list.push_back(edge_twin);
        }

        // Definiting start/end half-edges:
        auto half_edge = std::make_shared<EdgeDCEL<T, dim>>(vertex_list.back());
        auto edge_twin = std::make_shared<EdgeDCEL<T, dim>>(vertex_list.front());

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
        auto f1 = std::make_shared<FaceDCEL<T, dim>>();  // Hole in f2
        auto f2 = std::make_shared<FaceDCEL<T, dim>>();  // Unbounded face

        // Outer edge of hole would be CCW, but inner edges of unbound face would be CW
        f1->outer = edge_list[0];
        f2->inner.push_back(edge_list[1]);

        face_list.push_back(f1.get());
        face_list.push_back(f2.get());

        // Setting incident faces for each outer edge of face f1:
        f1->outer->incident_face = f1;
        std::shared_ptr<EdgeDCEL<T, dim>> edge = f1->outer->next;
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

    template<typename T, size_t dim>
    inline void PolygonDCEL<T, dim>::getEdgesFromVertex(VertexDCEL<T, dim>* v,
                                std::vector<EdgeDCEL<T, dim>*> edges_from_v) {
        auto v_incident_edge = v->incident_edge;
        edges_from_v.push_back(v_incident_edge);

        auto next_edge = v_incident_edge->twin->next;
        while (next_edge != v_incident_edge) {
            edges_from_v.push_back(next_edge);
            next_edge = next_edge->twin->next;
        }
    }

    template<typename T, size_t dim>
    inline void PolygonDCEL<T, dim>::getEdgesForSplittingPolygon(VertexDCEL<T, dim>* v1,
                                        VertexDCEL<T, dim>* v2,
                                        EdgeDCEL<T, dim>** edge_from_v1,
                                        EdgeDCEL<T, dim>** edge_from_v2) {
        // For recording all edges from vertices v1 and v2:
        std::vector<EdgeDCEL<T, dim>*> edges_from_v1, edges_from_v2;

        getEdgesFromVertex(v1, edges_from_v1);
        getEdgesFromVertex(v2, edges_from_v2);

        // Getting the required half-edges:
        for (auto edge1:edges_from_v1) {
            for (auto edge2:edges_from_v2) {
                if (edge1->incident_face->outer != nullptr) {
                    if (edge1->incident_face == edge2->incident_face) {
                        *edge_from_v1 = edge1;
                        *edge_from_v2 = edge2;
                        return;
                    }
                }
            }
        }
    }

    template<typename T, size_t dim>
    inline bool PolygonDCEL<T, dim>::split(VertexDCEL<T, dim>* v1,
                                           VertexDCEL<T, dim>* v2) {
        // Creating the half-edges from v1 and v2:
        EdgeDCEL<T, dim>* edge_from_v1;
        EdgeDCEL<T, dim>* edge_from_v2;

        getEdgesForSplittingPolygon(v1, v2, &edge_from_v1, &edge_from_v2);

        // No such half-edges exist:
        if (edge_from_v1-> id == -1 || edge_from_v2->id == -1)
            return false;
        
        // No half-edges for adjacent vertices:
        if (edge_from_v1->next->origin == v2 || edge_from_v1->prev->origin == v2)
            return false;

        FaceDCEL<T, dim>* previous_face = edge_from_v1->incident_face;

        // Establishing half-edges for the split:
        std::shared_ptr<EdgeDCEL<T, dim>> half_edge1 = std::make_shared<cga::EdgeDCEL<T, dim>>(v1);
        std::shared_ptr<EdgeDCEL<T, dim>> half_edge2 = std::make_shared<cga::EdgeDCEL<T, dim>>(v2);

        half_edge1->twin = half_edge2.get();
        half_edge2->twin = half_edge1.get();

        half_edge1->next = edge_from_v2;
        half_edge2->next = edge_from_v1;

        half_edge1->prev = edge_from_v1->prev;
        half_edge2->prev = edge_from_v2->prev;

        half_edge1->next->prev = half_edge1.get();
        half_edge2->next->prev = half_edge2.get();

        half_edge1->prev->next = half_edge1.get();
        half_edge2->prev->next = half_edge2.get();

        // Establishing new faces:
        std::shared_ptr<FaceDCEL<T, dim>> new_face1 = std::make_shared<FaceDCEL<T, dim>>();
        new_face1->outer = half_edge1.get();
        half_edge1->incident_face = new_face1.get();
        auto temp_edge = half_edge1->next;
        while (temp_edge != half_edge1.get()) {
            temp_edge->incident_face = new_face1.get();
            temp_edge = temp_edge->next;
        }

        std::shared_ptr<FaceDCEL<T, dim>> new_face2 = std::make_shared<FaceDCEL<T, dim>>();
        new_face2->outer = half_edge2.get();
        half_edge2->incident_face = new_face2.get();
        temp_edge = half_edge2->next;
        while (temp_edge != half_edge2.get()) {
            temp_edge->incident_face = new_face2.get();
            temp_edge = temp_edge->next;
        }

        face_list.push_back(new_face1.get());
        face_list.push_back(new_face2.get());

        // Updating faces:
        auto itr = std::find(face_list.begin(), face_list.end(), previous_face);

        if (itr != face_list.end()) {
            face_list.erase(itr);
            delete previous_face;
        }

        return true;
    }

    // Implementation pending...
    template<typename T, size_t dim>
    inline bool PolygonDCEL<T, dim>::join(VertexDCEL<T, dim>* v1,
                                          VertexDCEL<T, dim>* v2) {
        std::cout << "join() implementation is pending..." << std::endl;
        return false;
    }

    template<typename T, size_t dim>
    inline std::vector<VertexDCEL<T, dim>*> PolygonDCEL<T, dim>::get_vertex_list() {
        return vertex_list;
    }

    template<typename T, size_t dim>
    inline std::vector<EdgeDCEL<T, dim>*> PolygonDCEL<T, dim>::get_edge_list() {
        return edge_list;
    }

    template<typename T, size_t dim>
    inline std::vector<FaceDCEL<T, dim>*> PolygonDCEL<T, dim>::get_face_list() {
        return face_list;
    }

    template<typename T, size_t dim>
    inline VertexDCEL<T, dim>* PolygonDCEL<T, dim>::get_vertex(VectorND& point_) {
        for (auto vertex:vertex_list) {
            if (point_ == vertex->point) {
                return vertex;
            }
        }

        std::cout << "Vertex with given point does not exist" << std::endl;
        return nullptr;
    }

    typedef PolygonDCEL<float, DIM2>    PolygonDCEL2D;
}