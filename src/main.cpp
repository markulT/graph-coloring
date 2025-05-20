#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>
#include <memory>
#include <string>
#include "../include/graph/graph.hpp"
#include "../include/canvas/canvas.hpp"

using namespace graph_coloring;

// Function to create a complete graph (K5)
Graph createCompleteGraph() {
    Graph graph;
    
    // Add vertices in a regular pentagon layout (more standard for K5)
    const float centerX = 0.5f;
    const float centerY = 0.5f;
    const float radius = 0.35f;
    
    // Add vertices in a pentagon arrangement
    for (int i = 0; i < 5; i++) {
        float angle = 2.0f * 3.14159f * i / 5;  // evenly spaced around a circle
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        graph.addVertex(x, y);
    }
    
    // Connect every vertex to every other vertex (complete graph definition)
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            graph.addEdge(i, j);
        }
    }
    
    std::cout << "K5 requires exactly 5 colors because each vertex connects to all others." << std::endl;
    
    return graph;
}

// Function to create a cycle graph
Graph createCycleGraph() {
    Graph graph;
    
    // Create vertices in a circular arrangement
    const int numVertices = 8;
    const float centerX = 0.5f;
    const float centerY = 0.5f;
    const float radius = 0.35f;
    
    // Add vertices in a circle
    for (int i = 0; i < numVertices; i++) {
        float angle = 2.0f * 3.14159f * i / numVertices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        graph.addVertex(x, y);
    }
    
    // Connect vertices in a cycle
    for (int i = 0; i < numVertices; i++) {
        graph.addEdge(i, (i + 1) % numVertices);
    }
    
    return graph;
}

// Function to create a grid graph
Graph createGridGraph() {
    Graph graph;
    
    // Create a 4x4 grid graph
    const int gridSize = 4;
    const float spacing = 1.0f / (gridSize + 1);
    
    // Add vertices in a grid pattern
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            float x = spacing * (col + 1);
            float y = spacing * (row + 1);
            graph.addVertex(x, y);
        }
    }
    
    // Connect vertices in the grid
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            int currentIndex = row * gridSize + col;
            
            // Connect to right neighbor
            if (col < gridSize - 1) {
                graph.addEdge(currentIndex, currentIndex + 1);
            }
            
            // Connect to bottom neighbor
            if (row < gridSize - 1) {
                graph.addEdge(currentIndex, currentIndex + gridSize);
            }
        }
    }
    
    return graph;
}

// Function to create a star graph
Graph createStarGraph() {
    Graph graph;
    
    // Create a central vertex
    graph.addVertex(0.5f, 0.5f);  // id: 0 (center)
    
    // Create outer vertices
    const int numRays = 10;
    const float radius = 0.4f;
    
    for (int i = 0; i < numRays; i++) {
        float angle = 2.0f * 3.14159f * i / numRays;
        float x = 0.5f + radius * cos(angle);
        float y = 0.5f + radius * sin(angle);
        graph.addVertex(x, y);  // id: 1 to numRays
    }
    
    // Connect center to all outer vertices
    for (int i = 1; i <= numRays; i++) {
        graph.addEdge(0, i);
    }
    
    return graph;
}

// Function to create a petersen graph (a common test case for graph coloring)
Graph createPetersenGraph() {
    Graph graph;
    
    // Create outer pentagon vertices
    const float outerRadius = 0.4f;
    const float innerRadius = 0.2f;
    const float centerX = 0.5f;
    const float centerY = 0.5f;
    
    // Add outer pentagon vertices (0-4)
    for (int i = 0; i < 5; i++) {
        float angle = 2.0f * 3.14159f * i / 5;
        float x = centerX + outerRadius * cos(angle);
        float y = centerY + outerRadius * sin(angle);
        graph.addVertex(x, y);
    }
    
    // Add inner pentagon vertices (5-9)
    for (int i = 0; i < 5; i++) {
        float angle = 2.0f * 3.14159f * i / 5 + 3.14159f / 5;  // offset by half a segment
        float x = centerX + innerRadius * cos(angle);
        float y = centerY + innerRadius * sin(angle);
        graph.addVertex(x, y);
    }
    
    // Connect outer pentagon
    for (int i = 0; i < 5; i++) {
        graph.addEdge(i, (i + 1) % 5);
    }
    
    // Connect each outer vertex to its corresponding inner vertex
    for (int i = 0; i < 5; i++) {
        graph.addEdge(i, i + 5);
    }
    
    // Connect inner vertices (create a star)
    for (int i = 0; i < 5; i++) {
        graph.addEdge(5 + i, 5 + ((i + 2) % 5));
    }
    
    return graph;
}

// Function to randomly select a graph from the available options
Graph getRandomGraph() {
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Choose a random graph type (0-4)
    int graphType = std::rand() % 5;
    
    std::cout << "Selected graph type: ";
    
    switch (graphType) {
        case 0:
            std::cout << "Complete Graph (K5)" << std::endl;
            return createCompleteGraph();
        case 1:
            std::cout << "Cycle Graph" << std::endl;
            return createCycleGraph();
        case 2:
            std::cout << "Grid Graph" << std::endl;
            return createGridGraph();
        case 3:
            std::cout << "Star Graph" << std::endl;
            return createStarGraph();
        case 4:
            std::cout << "Petersen Graph" << std::endl;
            return createPetersenGraph();
        default:
            std::cout << "Default: Complete Graph (K5)" << std::endl;
            return createCompleteGraph();
    }
}

void printUsage() {
    std::cout << "Usage: GraphColoring [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --algorithm=<alg>    Coloring algorithm: 'greedy', 'sf', or 'exact' (default: greedy)" << std::endl;
    std::cout << "  --help               Show this help message" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "Graph Coloring Demonstration" << std::endl;
    
    // Parse command line arguments
    ColoringAlgorithm algorithm = ColoringAlgorithm::Greedy;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            printUsage();
            return 0;
        } else if (arg.find("--algorithm=") == 0) {
            std::string value = arg.substr(12);
            if (value == "sf") {
                algorithm = ColoringAlgorithm::SF;
            } else if (value == "greedy") {
                algorithm = ColoringAlgorithm::Greedy;
            } else if (value == "exact") {
                algorithm = ColoringAlgorithm::Exact;
            } else {
                std::cerr << "Invalid algorithm: " << value << std::endl;
                printUsage();
                return 1;
            }
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
            printUsage();
            return 1;
        }
    }
    
    // Create a random sample graph
    Graph graph = getRandomGraph();
    
    // Apply graph coloring algorithm
    auto startTime = std::chrono::high_resolution_clock::now();
    graph.colorGraph(algorithm);
    auto endTime = std::chrono::high_resolution_clock::now();
    
    // Calculate and print execution time
    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    std::cout << "Coloring completed in " << duration.count() << " ms" << std::endl;
    
    // Print results
    std::cout << "Number of colors used: " << graph.getNumberOfColors() << std::endl;
    std::cout << "Vertex colors:" << std::endl;
    
    for (const auto& vertex : graph.getVertices()) {
        int id = vertex.getId();
        std::cout << "Vertex " << id << ": Color " << graph.getVertexColor(id) << std::endl;
    }
    
    std::cout << "Is coloring valid? " << (graph.isValidColoring() ? "Yes" : "No") << std::endl;
    
    // Initialize rendering
    const int windowWidth = 800;
    const int windowHeight = 600;
    Canvas canvas(windowWidth, windowHeight, "Graph Coloring Visualization");
    if (!canvas.initialize()) {
        std::cerr << "Failed to initialize GLFW window" << std::endl;
        return -1;
    }
    
    // Set the graph for rendering
    canvas.setGraph(&graph);
    
    // Main loop
    while (!canvas.shouldClose()) {
        canvas.processInput();
        canvas.render();
        
        // Simple frame rate limiting
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    
    return 0;
}
