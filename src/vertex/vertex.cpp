#include "../../include/vertex/vertex.hpp"

namespace graph_coloring {

Vertex::Vertex(int id, float x, float y, const std::string& label)
    : id(id), x(x), y(y), label(label) {
}

Vertex::~Vertex() {
}

int Vertex::getId() const {
    return id;
}

float Vertex::getX() const {
    return x;
}

float Vertex::getY() const {
    return y;
}

std::string Vertex::getLabel() const {
    return label;
}

void Vertex::setX(float x) {
    this->x = x;
}

void Vertex::setY(float y) {
    this->y = y;
}

void Vertex::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vertex::setLabel(const std::string& label) {
    this->label = label;
}

bool Vertex::operator==(const Vertex& other) const {
    return id == other.id;
}

bool Vertex::operator!=(const Vertex& other) const {
    return !(*this == other);
}

} // namespace graph_coloring 