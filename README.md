# Graph Coloring

This project implements a graph coloring algorithm that assigns colors to vertices of a graph such that no adjacent vertices have the same color, using the minimum number of colors possible.

## Features

- Graph class structure with vertices and edges
- Greedy graph coloring algorithm implementation
- GLFW-based visualization of the colored graph
- Command-line output showing vertex color assignments

## Requirements

- CMake 3.10 or higher
- C++17 compatible compiler
- OpenGL

## Building the Project

1. Clone the repository
2. Make sure GLFW is available in the 'glfw' directory
3. Create a build directory and navigate to it:

```bash
mkdir -p build
cd build
```

4. Configure with CMake and build:

```bash
cmake ..
cmake --build .
```

## Running the Program

After building, run the executable from the build directory:

```bash
./GraphColoring
```

## Project Structure

- `include/` - Header files (.hpp)
  - `graph/` - Graph class definitions
  - `vertex/` - Vertex class definitions
  - `edge/` - Edge class definitions
  - `canvas/` - GLFW rendering classes
- `src/` - Implementation files (.cpp)
- `glfw/` - GLFW library

## Graph Coloring Algorithm

The project uses a greedy algorithm for graph coloring:
1. Iterate through each vertex
2. For each vertex, find the first color not used by any adjacent vertices
3. Assign that color to the current vertex

The algorithm doesn't guarantee the minimum possible number of colors (which is an NP-hard problem), but it provides a reasonable approximation.

## Visualization

The GLFW visualization shows:
- Vertices as colored circles
- Edges as black lines connecting vertices
- Vertex IDs displayed on the vertices
- Different colors for each color group 