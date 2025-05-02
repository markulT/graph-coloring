#include "../../include/edge/edge.hpp"

namespace graph_coloring {

Edge::Edge(int sourceId, int targetId, float weight)
    : sourceId(sourceId), targetId(targetId), weight(weight) {
}

Edge::~Edge() {
}

int Edge::getSourceId() const {
    return sourceId;
}

int Edge::getTargetId() const {
    return targetId;
}

float Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(float weight) {
    this->weight = weight;
}

bool Edge::operator==(const Edge& other) const {
    return (sourceId == other.sourceId && targetId == other.targetId) ||
           (sourceId == other.targetId && targetId == other.sourceId);
}

bool Edge::operator!=(const Edge& other) const {
    return !(*this == other);
}

bool Edge::connects(int vertexId) const {
    return sourceId == vertexId || targetId == vertexId;
}

bool Edge::connects(int vertexId1, int vertexId2) const {
    return (sourceId == vertexId1 && targetId == vertexId2) ||
           (sourceId == vertexId2 && targetId == vertexId1);
}

} // namespace graph_coloring 