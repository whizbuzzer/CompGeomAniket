/* Monotone polygon partitioning implementation 
 * https://www.cs.jhu.edu/~misha/Spring16/05.pdf
 */

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "GeoUtils.h"
#include "Point.h"
#include "PolygonDCEL.h"
#include "VertexDCEL.h"

namespace cga {
    /* Vertices would be classified into 5 types:
     * -This lies above that == Y-coordinate of this is greater than that
     * -This lies below that == Y-coordinate of this is lesser than that

     * 1. Start vertices: If two neighboring vertices lie below this vertex and the
     * interior angle at this vertex is < 180 degrees

     * 2. End vertices: If two neighboring vertices lie above this vertex and the
     * interior angle at this vertex is < 180 degrees

     * 3. Regular vertices: If one neighboring vertex is above it and the other one is
     * below it

     * 4. Split Vertices: If two neighboring vertices lie below this vertex and the
     * interior angle at this vertex is > 180 degrees

     * 5. Merge Vertices: If two neighboring vertices lie above this vertex and the
     * interior angle at this vertex is > 180 degrees
     */
    enum class VERTEX_CATEGORY {
        START,
        END,
        REGULAR,
        SPLIT,
        MERGE,
        INVALID
    };


    struct VertexDCEL2DWrapper {
        VertexDCEL2D* vertex;
        VERTEX_CATEGORY category;
    };


    // To store the "helper vertices" that EdgeDCEL does not store:
    struct EdgeDCEL2DWrapper {
        EdgeDCEL2D* edge;
        VertexDCEL2DWrapper helper;

        EdgeDCEL2DWrapper(EdgeDCEL2D* edge_, VertexDCEL2DWrapper& helper_) {
            edge = edge_;
            helper = helper_;
            origin = edge->origin->point;
            destination = edge->twin->origin->point;
        }

        const float computeX(const Point2D& point) const {
            // Checking if the line between origin and destination is horizontal:
            float denominator = destination[Y] - origin[Y];
            float x_ = point[X];

            if (denominator != 0) {
                x_ = (((point[Y] - origin[Y]) * (destination[X] - origin[X])) /
                        denominator) + origin[X];
            }

            return x_;
        }

    private:
        Point2D origin, destination;
    };


    // Monotone Partitioning will use a sweep line which travels from up to down
    // in order to scan the vertices and partition the polygon accordingly:
    struct SweepLineComparator {
        Point2D* point;

        SweepLineComparator(std::shared_ptr<cga::Point2D>& sweep_point) {
            point = sweep_point.get();
        }

        bool operator()(const EdgeDCEL2DWrapper* ref1,
                        const EdgeDCEL2DWrapper* ref2) const {
            return ref1->computeX(*point) < ref2->computeX(*point);
        }
    };


    // Event queue should arrange events so that it would give high priority to
    // events with greater Y coordinates. We will make this event queue with a
    // std::vector<> and then sort this vector according to Y coordinates
    struct VertexDCEL2DWrapperSort {
        bool operator()(VertexDCEL2DWrapper& curr_vert,
                        VertexDCEL2DWrapper& ref_vert) {
            auto p_curr = curr_vert.vertex->point;
            auto p_ref = ref_vert.vertex->point;

            // In case 2 points have the same Y-coordinates, then they will be
            // scanned along the X-axis (left to right)
            if ((p_curr[Y] > p_ref[Y])
                || (p_curr[Y] == p_ref[Y] && p_curr[X] < p_ref[X])) {
                return true;
            }
            return false;
            
        }
    };

    /* Methods */
    VERTEX_CATEGORY categorize_vertex(VertexDCEL2D* vertex) {
        // Finding neighbors:
        VertexDCEL2D* v_prev = vertex->incident_edge->prev->origin;
        VertexDCEL2D* v_next = vertex->incident_edge->next->origin;

        // If a vertex does not have two neighbors, then it is INVALID:
        if (!v_next || !v_prev) {
            return cga::VERTEX_CATEGORY::INVALID;
        }

        // Storing points:
        Point2D p = vertex->point;
        Point2D p_prev = v_prev->point;
        Point2D p_next = v_next->point;
        
        // If p is to the left of the line connecting p_prev and p_next, then
        // angle at p is convex. This will help us determing the vertex type of
        // the input vertex
        bool is_left = cga::left(p, p_prev, p_next);  // Argument order might be incorrect...
        // bool is_convex = isConvex()

        if (p[Y] > p_prev[Y] && p[Y] > p_next[Y]) {
            if (is_left)
                return VERTEX_CATEGORY::START;
            else
                return VERTEX_CATEGORY::SPLIT;
        } else if (p[Y] < p_prev[Y] && p[Y] < p_next[Y]) {
            if (is_left)
                return VERTEX_CATEGORY::END;
            else
                return VERTEX_CATEGORY::MERGE;
        } else {
            return VERTEX_CATEGORY::REGULAR;
        }
    }
    

    // Vertex handling functions (mutators/setters):
    static void handle_end_vertices(VertexDCEL2DWrapper& vertex,
                std::set<EdgeDCEL2DWrapper*, SweepLineComparator>& sweep_line,
                std::map<EdgeDCEL2D*, EdgeDCEL2DWrapper*>& edge_mapping,
                PolygonDCEL2D* polygon) {
        auto edge_wrapper = edge_mapping[vertex.vertex->incident_edge->prev];
        auto found = sweep_line.find(edge_wrapper);
        auto helper = (*found)->helper;
        if (helper.category == VERTEX_CATEGORY::MERGE)
            polygon->split(vertex.vertex, helper.vertex);
        sweep_line.erase(found);
    }


    static void handle_merge_vertices(VertexDCEL2DWrapper& vertex,
                std::set<EdgeDCEL2DWrapper*, SweepLineComparator>& sweep_line,
                std::map<EdgeDCEL2D*, EdgeDCEL2DWrapper*>& edge_mapping,
                PolygonDCEL2D* polygon) {
        auto edge_wrapper = edge_mapping[vertex.vertex->incident_edge->prev];
        if (edge_wrapper->helper.category == VERTEX_CATEGORY::MERGE)
            polygon->split(vertex.vertex, edge_wrapper->helper.vertex);
        
        auto found = sweep_line.find(edge_wrapper);
        if (found != sweep_line.end())
            sweep_line.erase(found);
        
        std::shared_ptr<EdgeDCEL2DWrapper> edge = std::make_shared<EdgeDCEL2DWrapper>(vertex.vertex->incident_edge, vertex);
        found = sweep_line.lower_bound(edge.get());
        std::shared_ptr<EdgeDCEL2DWrapper> ej;
        
        // Might cause problem:
        if (sweep_line.size() > 0) {
            if (found == sweep_line.end() || found != sweep_line.begin()) {
                ej.reset(*(--found));
                if (ej->helper.category == VERTEX_CATEGORY::MERGE)
                    polygon->split(vertex.vertex, ej->helper.vertex);
                ej->helper = vertex;
            }
        }
    }


    static void handle_regular_vertices(VertexDCEL2DWrapper& vertex,
                std::set<EdgeDCEL2DWrapper*, SweepLineComparator>& sweep_line,
                std::map<EdgeDCEL2D*, EdgeDCEL2DWrapper*>& edge_mapping,
                PolygonDCEL2D* polygon) {
        // Checking whether the polygon lies to the right of "vertex" or not:
        auto prev_y = vertex.vertex->incident_edge->prev->origin->point[Y];
        auto curr_y = vertex.vertex->point[Y];
        auto next_y = vertex.vertex->incident_edge->prev->origin->point[Y];

        std::shared_ptr<cga::EdgeDCEL2DWrapper> edge = std::make_shared<cga::EdgeDCEL2DWrapper>(vertex.vertex->incident_edge,
                                                                        vertex);

        // Condition for a regular vertex:
        if (prev_y >= curr_y && curr_y >= next_y) {
            auto edge_wrapper = edge_mapping[vertex.vertex->incident_edge->prev];
            if (edge_wrapper->helper.category == VERTEX_CATEGORY::MERGE)
                polygon->split(vertex.vertex, edge_wrapper->helper.vertex);
            
            auto found = sweep_line.find(edge_wrapper);
            if (found != sweep_line.end())
                sweep_line.erase(found);

            sweep_line.insert(edge.get());
            edge_mapping.insert(std::pair<cga::EdgeDCEL2D*, cga::EdgeDCEL2DWrapper*>(vertex.vertex->incident_edge,
                                                                        edge.get()));
        } else {
            auto found = sweep_line.lower_bound(edge.get());
            std::shared_ptr<EdgeDCEL2DWrapper> ej;
            
            // Might cause problem:
            if (sweep_line.size() > 0) {
                if (found == sweep_line.end())
                    ej.reset(*(--found));
                else if (found != sweep_line.begin())
                    ej.reset(*(found--));

                if (ej->helper.category == VERTEX_CATEGORY::MERGE)
                    polygon->split(vertex.vertex, ej->helper.vertex);
                ej->helper = vertex;
            }
        }
    }



    static void handle_split_vertices(cga::VertexDCEL2DWrapper& vertex,
                std::set<cga::EdgeDCEL2DWrapper*, cga::SweepLineComparator>& sweep_line,
                std::map<cga::EdgeDCEL2D*, cga::EdgeDCEL2DWrapper*>& edge_mapping,
                cga::PolygonDCEL2D* polygon) {
        std::shared_ptr<cga::EdgeDCEL2DWrapper> edge = std::make_shared<cga::EdgeDCEL2DWrapper>(vertex.vertex->incident_edge,
                                                                        vertex);
        auto found = sweep_line.lower_bound(edge.get());
        std::shared_ptr<cga::EdgeDCEL2DWrapper> ej;

        // Might cause problem:
        if (sweep_line.size() > 0) {
            if (found == sweep_line.end() || found != sweep_line.begin()) {
                ej.reset(*(--found));
                if (ej->helper.category == cga::VERTEX_CATEGORY::MERGE)
                    polygon->split(vertex.vertex, ej->helper.vertex);
                ej->helper = vertex;
            }
        }

        sweep_line.insert(edge.get());
        edge_mapping.insert(std::pair<cga::EdgeDCEL2D*, cga::EdgeDCEL2DWrapper*>(vertex.vertex->incident_edge,
                                                                    edge.get()));
    }


    static void handle_start_vertices(cga::VertexDCEL2DWrapper& vertex,
                std::set<cga::EdgeDCEL2DWrapper*, cga::SweepLineComparator>& sweep_line,
                std::map<cga::EdgeDCEL2D*, cga::EdgeDCEL2DWrapper*>& edge_mapping,
                cga::PolygonDCEL2D* polygon) {
        std::shared_ptr<cga::EdgeDCEL2DWrapper> edge = std::make_shared<cga::EdgeDCEL2DWrapper>(vertex.vertex->incident_edge,
                                                                        vertex);
        sweep_line.insert(edge.get());
        edge_mapping.insert(std::pair<cga::EdgeDCEL2D*, cga::EdgeDCEL2DWrapper*>(vertex.vertex->incident_edge,
                                                                    edge.get()));
    }


    // https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
    void get_monotone_polygons(cga::PolygonDCEL2D* polygon,
                               std::vector<cga::PolygonDCEL2D>& sub_polygons) {
        // Event queue:
        std::vector<cga::VertexDCEL2DWrapper> vertices;

        for (auto v:polygon->get_vertex_list()) {
            vertices.push_back(cga::VertexDCEL2DWrapper{v, cga::categorize_vertex(v)});
        }

        // Sorting the queue based on vertex type:
        std::sort(vertices.begin(), vertices.end(), cga::VertexDCEL2DWrapperSort());

        // Passing the sweep point to the sweep line comparator:
        std::shared_ptr<cga::Point2D> sweep_point = std::make_shared<cga::Point2D>();
        
        // Assigning sweep point to be the first element of the event queue:
        sweep_point->assign(X, vertices[0].vertex->point[X]);
        sweep_point->assign(Y, vertices[0].vertex->point[Y]);

        // Initializing comparator which would be used in the sweep line status:
        cga::SweepLineComparator comparator(sweep_point);
        std::set<cga::EdgeDCEL2DWrapper*, cga::SweepLineComparator> sweep_line(comparator);
        // Creating edge-mapping to iterate through edges in O(logN) time:
        std::map<cga::EdgeDCEL2D*, cga::EdgeDCEL2DWrapper*> edge_mapping;

        for (auto v:vertices) {
            sweep_point->assign(X, vertices[0].vertex->point[X]);
            sweep_point->assign(Y, vertices[0].vertex->point[Y]);

            switch(v.category) {
                case cga::VERTEX_CATEGORY::START:
                    cga::handle_start_vertices(v, sweep_line, edge_mapping, polygon);
            }
        }
    }
}


int main() {
    return 0;
}