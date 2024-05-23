#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <set>
#include <string>

struct Vertex {
    std::string label_;

    explicit Vertex(std::string label) : label_(std::move(label)) {}
    bool operator==(const Vertex& vertex) const { return label_ == vertex.label_; }
    bool operator<(const Vertex& vertex) const { return label_ < vertex.label_; }
};

struct Arc {
    const Vertex* tail_;
    const Vertex* head_;

    Arc(const Vertex* tail, const Vertex* head) : tail_(tail), head_(head) {}
    bool operator<(const Arc& arc) const {
        return *tail_ == *arc.tail_ ? *head_ < *arc.head_ : *tail_ < *arc.tail_;
    }
};

struct DirectedGraph {
    std::set<Vertex> vertex_set_;
    std::set<Arc> arc_set_;

    void addVertex(const Vertex& vertex) { vertex_set_.insert(vertex); }
    void addArc(const Arc& arc) { arc_set_.insert(arc); }
    [[nodiscard]] std::set<Arc> getArcsStartFrom(const Vertex& from) const {
        std::set<Arc> result_arc_result;
        for (const auto& arc : arc_set_) {
            if (*arc.tail_ == from) {
                result_arc_result.insert(arc);
            }
        }

        return result_arc_result;
    }
};

struct DirectedPath {
    std::vector<Arc> arc_vector_;
};

#endif
