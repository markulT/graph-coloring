#include "../../include/graph/graph.hpp"
#include <algorithm>
#include <stdexcept>

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

void Graph::colorGraph() {
    // Clear existing coloring
    vertexColors.clear();
    
    // If no vertices, return
    if (vertices.empty()) {
        return;
    }
    
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

} // namespace graph_coloring 