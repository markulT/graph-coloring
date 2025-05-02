#include "../../include/canvas/canvas.hpp"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace graph_coloring {

// GLFW error callback
static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

// Define predefined colors for graph coloring
Canvas::Canvas(int width, int height, const std::string& title)
    : width(width), height(height), title(title), graph(nullptr), window(nullptr) {
    
    // Initialize predefined colors (RGB format, values from 0 to 1)
    colors[0][0] = 1.0f; colors[0][1] = 0.0f; colors[0][2] = 0.0f; // Red
    colors[1][0] = 0.0f; colors[1][1] = 0.0f; colors[1][2] = 1.0f; // Blue
    colors[2][0] = 0.0f; colors[2][1] = 0.8f; colors[2][2] = 0.0f; // Green
    colors[3][0] = 1.0f; colors[3][1] = 1.0f; colors[3][2] = 0.0f; // Yellow
    colors[4][0] = 1.0f; colors[4][1] = 0.5f; colors[4][2] = 0.0f; // Orange
    colors[5][0] = 0.5f; colors[5][1] = 0.0f; colors[5][2] = 0.5f; // Purple
    colors[6][0] = 0.0f; colors[6][1] = 1.0f; colors[6][2] = 1.0f; // Cyan
    colors[7][0] = 1.0f; colors[7][1] = 0.0f; colors[7][2] = 1.0f; // Magenta
    colors[8][0] = 0.5f; colors[8][1] = 0.5f; colors[8][2] = 0.5f; // Gray
    colors[9][0] = 0.0f; colors[9][1] = 0.5f; colors[9][2] = 0.0f; // Dark Green
}

Canvas::~Canvas() {
    close();
}

bool Canvas::initialize() {
    // Set error callback
    glfwSetErrorCallback(glfw_error_callback);
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    
    // Create window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    return true;
}

void Canvas::setGraph(Graph* graph) {
    this->graph = graph;
}

void Canvas::render() {
    if (!window || !graph) {
        return;
    }
    
    // Set clear color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Reset transformation matrix
    glLoadIdentity();
    
    // Set up orthographic projection
    glOrtho(0, width, height, 0, -1, 1);
    
    // Render edges first
    for (const auto& edge : graph->getEdges()) {
        renderEdge(edge);
    }
    
    // Then render vertices
    for (const auto& vertex : graph->getVertices()) {
        renderVertex(vertex);
    }
    
    // Swap front and back buffers
    glfwSwapBuffers(window);
    
    // Poll for and process events
    glfwPollEvents();
}

void Canvas::renderVertex(const Vertex& vertex) {
    const float radius = 15.0f;
    const int segments = 20;
    
    float x = vertex.getX() * (width - 2 * radius) + radius;
    float y = vertex.getY() * (height - 2 * radius) + radius;
    
    // Get the color for this vertex
    int colorIndex = graph->getVertexColor(vertex.getId());
    if (colorIndex < 0 || colorIndex >= MAX_COLORS) {
        colorIndex = MAX_COLORS - 1; // Default to last color if invalid
    }
    
    // Set vertex color
    glColor3f(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    
    // Draw filled circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float vx = x + radius * cos(angle);
        float vy = y + radius * sin(angle);
        glVertex2f(vx, vy);
    }
    glEnd();
    
    // Draw black outline
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float vx = x + radius * cos(angle);
        float vy = y + radius * sin(angle);
        glVertex2f(vx, vy);
    }
    glEnd();
    
    // Render vertex ID
    std::string idText = std::to_string(vertex.getId());
    renderText(idText, x - 5.0f, y - 5.0f, 1.0f);
}

void Canvas::renderEdge(const Edge& edge) {
    Vertex* source = graph->getVertex(edge.getSourceId());
    Vertex* target = graph->getVertex(edge.getTargetId());
    
    if (!source || !target) {
        return;
    }
    
    const float radius = 15.0f;
    
    float x1 = source->getX() * (width - 2 * radius) + radius;
    float y1 = source->getY() * (height - 2 * radius) + radius;
    float x2 = target->getX() * (width - 2 * radius) + radius;
    float y2 = target->getY() * (height - 2 * radius) + radius;
    
    // Set edge color (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Set line width to make edges more visible
    glLineWidth(2.5f);
    
    // Draw line
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    
    // Reset line width to default
    glLineWidth(1.0f);
}

void Canvas::renderText(const std::string& text, float x, float y, float scale) {
    // Simple rendering of text using lines (very basic)
    // In a real application, you would use a text rendering library like FreeType
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // For simplicity, we're just drawing a small square for now
    // In a real app, you'd render actual characters
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 10.0f * scale, y);
    glVertex2f(x + 10.0f * scale, y + 10.0f * scale);
    glVertex2f(x, y + 10.0f * scale);
    glEnd();
}

bool Canvas::shouldClose() {
    return window ? glfwWindowShouldClose(window) : true;
}

void Canvas::close() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void Canvas::processInput() {
    if (!window) {
        return;
    }
    
    // Example: Close window on ESC press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* Canvas::getWindow() {
    return window;
}

} // namespace graph_coloring 