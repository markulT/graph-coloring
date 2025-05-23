#include "../../include/graph/graph.hpp"
#include <algorithm>
#include <stdexcept>
#include <random>
#include <ctime>
#include <iostream>

namespace graph_coloring {

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::addVertex(const Vertex& vertex) {
    // Check if a vertex with the same ID already exists
    for (const auto& v : vertices) {
        if (v.getId() == vertex.getId()) {
            return; // Vertex with this ID already exists
        }
    }
    vertices.push_back(vertex);
}

void Graph::addVertex(float x, float y) {
    int id = vertices.size();
    Vertex vertex(id, x, y);
    vertices.push_back(vertex);
}

Vertex* Graph::getVertex(int id) {
    for (auto& vertex : vertices) {
        if (vertex.getId() == id) {
            return &vertex;
        }
    }
    return nullptr;
}

std::vector<Vertex>& Graph::getVertices() {
    return vertices;
}

void Graph::addEdge(const Edge& edge) {
    // Check if vertices exist
    bool sourceExists = false;
    bool targetExists = false;
    
    for (const auto& v : vertices) {
        if (v.getId() == edge.getSourceId()) sourceExists = true;
        if (v.getId() == edge.getTargetId()) targetExists = true;
        
        if (sourceExists && targetExists) break;
    }
    
    if (!sourceExists || !targetExists) {
        throw std::runtime_error("Cannot add edge: one or both vertices don't exist");
    }
    
    // Check if the edge already exists
    for (const auto& e : edges) {
        if (e == edge) {
            return; // Edge already exists
        }
    }
    
    edges.push_back(edge);
}

void Graph::addEdge(int sourceId, int targetId) {
    Edge edge(sourceId, targetId);
    addEdge(edge);
}

Edge* Graph::getEdge(int sourceId, int targetId) {
    for (auto& edge : edges) {
        if (edge.connects(sourceId, targetId)) {
            return &edge;
        }
    }
    return nullptr;
}

std::vector<Edge>& Graph::getEdges() {
    return edges;
}

std::vector<int> Graph::getAdjacentVertexIds(int vertexId) {
    std::vector<int> adjacentIds;
    
    for (const auto& edge : edges) {
        if (edge.getSourceId() == vertexId) {
            adjacentIds.push_back(edge.getTargetId());
        } else if (edge.getTargetId() == vertexId) {
            adjacentIds.push_back(edge.getSourceId());
        }
    }
    
    return adjacentIds;
}

void Graph::colorGraph(ColoringAlgorithm algorithm) {
    // Clear existing coloring
    vertexColors.clear();
    
    // If no vertices, return
    if (vertices.empty()) {
        return;
    }
    
    // Choose the algorithm based on the parameter
    switch (algorithm) {
        case ColoringAlgorithm::SF:
            std::cout << "Using smallest-first algorithm for graph coloring" << std::endl;
            sfColoring();
            break;
        case ColoringAlgorithm::Exact:
            std::cout << "Using exact algorithm for graph coloring" << std::endl;
            exactColoring();
            break;
        case ColoringAlgorithm::Greedy:
        default:
            std::cout << "Using greedy algorithm for graph coloring" << std::endl;
            greedyColoring();
            break;
    }
}

void Graph::greedyColoring() {
    // Greedy coloring algorithm
    for (const auto& vertex : vertices) {
        int vertexId = vertex.getId();
        
        // Get colors of adjacent vertices
        std::vector<int> adjacentIds = getAdjacentVertexIds(vertexId);
        std::vector<bool> usedColors(vertices.size(), false);
        
        for (int adjId : adjacentIds) {
            auto it = vertexColors.find(adjId);
            if (it != vertexColors.end()) {
                int adjColor = it->second;
                if (adjColor < usedColors.size()) {
                    usedColors[adjColor] = true;
                }
            }
        }
        
        // Find the first unused color
        int color = 0;
        for (; color < usedColors.size(); color++) {
            if (!usedColors[color]) {
                break;
            }
        }
        
        // Assign this color to the current vertex
        vertexColors[vertexId] = color;
    }
}

void Graph::sfColoring() {
    // Smallest-First (SF) coloring algorithm
    // First, compute the degree of each vertex
    std::vector<std::pair<int, int>> vertexDegrees; // (vertex id, degree)
    
    for (const auto& vertex : vertices) {
        int vertexId = vertex.getId();
        std::vector<int> adjacentIds = getAdjacentVertexIds(vertexId);
        vertexDegrees.push_back(std::make_pair(vertexId, adjacentIds.size()));
    }
    
    // Sort vertices by degree in non-increasing order (largest degree first)
    std::sort(vertexDegrees.begin(), vertexDegrees.end(), 
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });
    
    // Color the vertices in this order
    for (const auto& vertexPair : vertexDegrees) {
        int vertexId = vertexPair.first;
        
        // Get colors of adjacent vertices
        std::vector<int> adjacentIds = getAdjacentVertexIds(vertexId);
        std::vector<bool> usedColors(vertices.size(), false);
        
        for (int adjId : adjacentIds) {
            auto it = vertexColors.find(adjId);
            if (it != vertexColors.end()) {
                int adjColor = it->second;
                if (adjColor < usedColors.size()) {
                    usedColors[adjColor] = true;
                }
            }
        }
        
        // Find the first unused color
        int color = 0;
        for (; color < usedColors.size(); color++) {
            if (!usedColors[color]) {
                break;
            }
        }
        
        // Assign this color to the current vertex
        vertexColors[vertexId] = color;
    }
}

void Graph::applyColoring(const std::vector<int>& coloring) {
    // Apply the coloring to the graph
    vertexColors.clear();
    
    for (size_t i = 0; i < vertices.size(); i++) {
        vertexColors[vertices[i].getId()] = coloring[i];
    }
}

bool Graph::isValidColoring() {
    // Check if every adjacent pair has different colors
    for (const auto& edge : edges) {
        int sourceId = edge.getSourceId();
        int targetId = edge.getTargetId();
        
        // Both vertices should have colors assigned
        if (vertexColors.find(sourceId) == vertexColors.end() ||
            vertexColors.find(targetId) == vertexColors.end()) {
            return false;
        }
        
        // Colors should be different
        if (vertexColors[sourceId] == vertexColors[targetId]) {
            return false;
        }
    }
    
    return true;
}

int Graph::getVertexColor(int vertexId) {
    auto it = vertexColors.find(vertexId);
    if (it != vertexColors.end()) {
        return it->second;
    }
    return -1; // No color assigned
}

void Graph::setVertexColor(int vertexId, int color) {
    // Check if vertex exists
    if (getVertex(vertexId) == nullptr) {
        throw std::runtime_error("Cannot set color: vertex doesn't exist");
    }
    
    vertexColors[vertexId] = color;
}

int Graph::getNumberOfColors() {
    if (vertexColors.empty()) {
        return 0;
    }
    
    int maxColor = -1;
    for (const auto& pair : vertexColors) {
        maxColor = std::max(maxColor, pair.second);
    }
    
    return maxColor + 1; // Colors are zero-indexed
}

void Graph::clear() {
    vertices.clear();
    edges.clear();
    vertexColors.clear();
}

bool Graph::isEmpty() {
    return vertices.empty();
}

int Graph::getVertexCount() {
    return vertices.size();
}

int Graph::getEdgeCount() {
    return edges.size();
}

void Graph::exactColoring() {
    // Start with minimum possible number of colors (1)
    int minColors = 1;
    int maxColors = vertices.size(); // Maximum possible colors needed
    
    // Binary search for the minimum number of colors
    while (minColors < maxColors) {
        int mid = (minColors + maxColors) / 2;
        std::vector<int> coloring(vertices.size(), -1);
        
        if (exactColoringUtil(coloring, 0, mid)) {
            maxColors = mid;
        } else {
            minColors = mid + 1;
        }
    }
    
    // Try one final time with the minimum number of colors
    std::vector<int> finalColoring(vertices.size(), -1);
    if (exactColoringUtil(finalColoring, 0, minColors)) {
        applyColoring(finalColoring);
        std::cout << "Found exact coloring with " << minColors << " colors" << std::endl;
    } else {
        std::cout << "Failed to find exact coloring" << std::endl;
    }
}

bool Graph::exactColoringUtil(std::vector<int>& coloring, int vertexIndex, int numColors) {
    // Base case: all vertices are colored
    if (vertexIndex == vertices.size()) {
        return true;
    }
    
    // Try all possible colors for the current vertex
    for (int color = 0; color < numColors; color++) {
        // Check if it's safe to color the current vertex with this color
        if (isSafeColor(vertices[vertexIndex].getId(), color, coloring)) {
            // Assign the color
            coloring[vertexIndex] = color;
            
            // Recursively color the rest of the vertices
            if (exactColoringUtil(coloring, vertexIndex + 1, numColors)) {
                return true;
            }
            
            // If coloring doesn't lead to a solution, backtrack
            coloring[vertexIndex] = -1;
        }
    }
    
    // If no color can be assigned to this vertex
    return false;
}

bool Graph::isSafeColor(int vertexId, int color, const std::vector<int>& coloring) {
    // Get adjacent vertices
    std::vector<int> adjacentIds = getAdjacentVertexIds(vertexId);
    
    // Check if any adjacent vertex has the same color
    for (int adjId : adjacentIds) {
        // Find the index of the adjacent vertex
        auto it = std::find_if(vertices.begin(), vertices.end(),
            [adjId](const Vertex& v) { return v.getId() == adjId; });
        
        if (it != vertices.end()) {
            int adjIndex = std::distance(vertices.begin(), it);
            if (coloring[adjIndex] == color) {
                return false;
            }
        }
    }
    
    return true;
}

} // namespace graph_coloring