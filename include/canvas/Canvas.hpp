#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include "../graph/graph.hpp"


namespace graph_coloring {

class Canvas {
private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;
    Graph* graph;
    
    // Colors for graph rendering
    static const int MAX_COLORS = 10;
    float colors[MAX_COLORS][3];
    
    // Internal rendering methods
    void renderVertex(const Vertex& vertex);
    void renderEdge(const Edge& edge);
    void renderText(const std::string& text, float x, float y, float scale);

public:
    Canvas(int width, int height, const std::string& title);
    ~Canvas();
    
    bool initialize();
    void setGraph(Graph* graph);
    
    void render();
    bool shouldClose();
    void close();
    
    // Event handling
    void processInput();
    
    // Utility methods
    GLFWwindow* getWindow();
    
};

} // namespace graph_coloring

