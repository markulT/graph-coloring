#pragma once

namespace graph_coloring {

class Edge {
private:
    int sourceId;     // ID of the source vertex
    int targetId;     // ID of the target vertex
    float weight;     // Optional weight for the edge

public:
    Edge(int sourceId, int targetId, float weight = 1.0f);
    ~Edge();

    // Getters
    int getSourceId() const;
    int getTargetId() const;
    float getWeight() const;

    // Setters
    void setWeight(float weight);

    // Utility methods
    bool operator==(const Edge& other) const;
    bool operator!=(const Edge& other) const;
    bool connects(int vertexId) const;
    bool connects(int vertexId1, int vertexId2) const;
};

} // namespace graph_coloring 