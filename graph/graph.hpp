#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <set>
#include <string>

struct Vertex {
    std::string label;

    explicit Vertex(std::string label) : label(std::move(label)) {}
    bool operator==(const Vertex& vertex) const { return label == vertex.label; }
    bool operator<(const Vertex& vertex) const { return label < vertex.label; }
};

struct Arc {
    const Vertex* tail;
    const Vertex* head;

    Arc(const Vertex* tail, const Vertex* head) : tail(tail), head(head) {}
    bool operator<(const Arc& arc) const {
        return *tail == *arc.tail ? *head < *arc.head : *tail < *arc.tail;
    }
};

struct DirectedGraph {
    std::set<Vertex> vertexSet;
    std::set<Arc> arcSet;

    void addVertex(const Vertex& vertex) { vertexSet.insert(vertex); }
    void addArc(const Arc& arc) { arcSet.insert(arc); }
    [[nodiscard]] std::set<Arc> getArcsStartFrom(const Vertex& from) const {
        std::set<Arc> resultArcSet;
        for (const auto& arc : arcSet) {
            if (*arc.tail == from) {
                resultArcSet.insert(arc);
            }
        }

        return resultArcSet;
    }
};

struct DirectedPath {
    std::vector<Arc> arcVector;
};

#endif
