#pragma once

#include <string>

namespace graph_coloring {

class Vertex {
private:
    int id;
    float x, y;  // Coordinates for visualization
    std::string label;

public:
    Vertex(int id, float x = 0.0f, float y = 0.0f, const std::string& label = "");
    ~Vertex();

    // Getters
    int getId() const;
    float getX() const;
    float getY() const;
    std::string getLabel() const;

    // Setters
    void setX(float x);
    void setY(float y);
    void setPosition(float x, float y);
    void setLabel(const std::string& label);

    // Utility methods
    bool operator==(const Vertex& other) const;
    bool operator!=(const Vertex& other) const;
};

} // namespace graph_coloring

