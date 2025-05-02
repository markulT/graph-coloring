#pragma once

#include <vector>
#include <unordered_map>
#include "../vertex/vertex.hpp"
#include "../edge/edge.hpp"

namespace graph_coloring {

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::unordered_map<int, int> vertexColors; // Maps vertex ID to color

public:
    Graph();
    ~Graph();

    // Vertex operations
    void addVertex(const Vertex& vertex);
    void addVertex(float x, float y);
    Vertex* getVertex(int id);
    std::vector<Vertex>& getVertices();

    // Edge operations
    void addEdge(const Edge& edge);
    void addEdge(int sourceId, int targetId);
    Edge* getEdge(int sourceId, int targetId);
    std::vector<Edge>& getEdges();
    std::vector<int> getAdjacentVertexIds(int vertexId);

    // Coloring operations
    void colorGraph();                  // Main coloring algorithm
    bool isValidColoring();             // Check if current coloring is valid
    int getVertexColor(int vertexId);   // Get the color of a specific vertex
    void setVertexColor(int vertexId, int color);
    int getNumberOfColors();            // Get total number of colors used

    // Utility methods
    void clear();
    bool isEmpty();
    int getVertexCount();
    int getEdgeCount();
};

} // namespace graph_coloring
