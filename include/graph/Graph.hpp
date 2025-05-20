#pragma once

#include <vector>
#include <unordered_map>
#include <random>
#include "../vertex/vertex.hpp"
#include "../edge/edge.hpp"

namespace graph_coloring {

enum class ColoringAlgorithm {
    Greedy,
    SF,
    Exact
};

class Graph {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::unordered_map<int, int> vertexColors; // Maps vertex ID to color
    
    // Coloring algorithm implementations
    void greedyColoring();
    void sfColoring();
    
    // Exact coloring algorithm methods
    void exactColoring();
    bool exactColoringUtil(std::vector<int>& coloring, int vertexIndex, int numColors);
    bool isSafeColor(int vertexId, int color, const std::vector<int>& coloring);
    void applyColoring(const std::vector<int>& coloring);
    
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
    void colorGraph(ColoringAlgorithm algorithm = ColoringAlgorithm::Greedy);
    bool isValidColoring();
    int getVertexColor(int vertexId);
    void setVertexColor(int vertexId, int color);
    int getNumberOfColors();

    // Utility methods
    void clear();
    bool isEmpty();
    int getVertexCount();
    int getEdgeCount();
};

} // namespace graph_coloring
