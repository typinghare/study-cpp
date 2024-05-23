#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include "graph.hpp"

/**
 * @brief Finds the shortest path in a directed graph from vertex `a` to vertex `b` using
 * Breadth-First Search (BFS).
 *
 * This function performs a BFS on the directed graph starting from vertex `a` and attempts to find
 * the shortest path to vertex `b`. If a path is found, it returns the path as a DirectedPath
 * object. If no path is found, it returns an empty DirectedPath object.
 *
 * @param graph The directed graph to search.
 * @param a The starting vertex.
 * @param b The destination vertex.
 * @return A DirectedPath object representing the shortest path from `a` to `b`, or an empty path if
 * no such path exists.
 */
DirectedPath getPathWithBFS(const DirectedGraph& graph, const Vertex& a, const Vertex& b) {
    // Queue to hold vertices to be processed
    std::queue<const Vertex*> vertex_queue;
    // Map to store the path information (current vertex -> previous vertex)
    std::unordered_map<const Vertex*, const Vertex*> path_map;
    // Set to keep track of visited vertices
    std::unordered_set<const Vertex*> visited;

    // Setup: Push vertex A to the queue and mark it as visited
    vertex_queue.push(&a);
    visited.insert(&a);

    // Breadth-first search to traverse all reachable vertices from vertex A
    while (!vertex_queue.empty()) {
        // Get the next vertex to process from the queue
        const Vertex* current = vertex_queue.front();
        vertex_queue.pop();

        // If the current vertex is the destination vertex B, break out of the loop
        if (*current == b) {
            break;
        }

        // Get all arcs starting from the current vertex
        for (const auto& arc : graph.getArcsStartFrom(*current)) {
            // Get the head (destination) vertex of the arc
            // If the head vertex has not been visited yet
            if (const auto* const next = arc.head; !visited.contains(next)) {
                // Push the head vertex to the queue for further processing
                vertex_queue.push(next);
                // Mark the head vertex as visited
                visited.insert(next);
                // Record the path: head vertex -> current vertex
                path_map[next] = current;
            }
        }
    }

    // Find the directed path based on the path map
    // If there is a path to vertex B or if A is the same as B
    if (path_map.contains(&b) || a == b) {
        DirectedPath directed_path;
        std::stack<const Vertex*> reversed_path;

        // Trace the path back from vertex B to vertex A using the path map
        const Vertex* current = &b;
        while (current != &a) {
            const Vertex* previous = path_map[current];
            // Push the current vertex onto the stack to reverse the path
            reversed_path.push(current);
            // Move to the previous vertex in the path
            current = previous;
        }
        // Finally, push vertex A onto the stack
        reversed_path.push(&a);

        // Create arcs from the reversed path
        const Vertex* tail = reversed_path.top();
        reversed_path.pop();
        while (!reversed_path.empty()) {
            const Vertex* head = reversed_path.top();
            reversed_path.pop();
            // Add the arc to the directed path
            directed_path.arcVector.emplace_back(tail, head);
            // Move to the next arc in the path
            tail = head;
        }

        // Return the constructed path
        return directed_path;
    }

    // If no path was found, return an empty path
    return {};
}

int main() {
    // Create vertices
    const Vertex v1("A");
    const Vertex v2("B");
    const Vertex v3("C");
    const Vertex v4("D");
    const Vertex v5("E");
    const Vertex v6("F");
    const Vertex v7("G");

    // Create a graph and add vertices
    DirectedGraph graph;
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addVertex(v3);
    graph.addVertex(v4);
    graph.addVertex(v5);
    graph.addVertex(v6);
    graph.addVertex(v7);

    // Add arcs (edges) between vertices
    graph.addArc(Arc(&v1, &v2));  // A -> B
    graph.addArc(Arc(&v2, &v3));  // B -> C
    graph.addArc(Arc(&v3, &v4));  // C -> D
    graph.addArc(Arc(&v1, &v3));  // A -> C
    graph.addArc(Arc(&v1, &v5));  // A -> E
    graph.addArc(Arc(&v5, &v6));  // E -> F
    graph.addArc(Arc(&v6, &v4));  // F -> D
    graph.addArc(Arc(&v4, &v7));  // D -> G
    graph.addArc(Arc(&v2, &v6));  // B -> F
    graph.addArc(Arc(&v6, &v7));  // F -> G

    // Find the path from A to G using BFS and output the path
    const auto& from = v1;
    const auto& to = v7;
    if (const auto [arcVector] = getPathWithBFS(graph, from, to); arcVector.empty()) {
        std::cout << "No path found from " << from.label << " to " << to.label << std::endl;
    } else {
        std::cout << "Path from " << from.label << " to " << to.label << ": ";
        std::cout << arcVector[0].tail->label;
        for (const auto& arc : arcVector) {
            std::cout << " -> " << arc.head->label;
        }
        std::cout << std::endl;
    }

    return 0;
}
