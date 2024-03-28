#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

struct Graph {
  std::unordered_map<int, std::vector<int>> adjacency_list;
  int no_of_verticies;
  int no_of_edges;
  int largest_vertex;
};

using Matrix = std::vector<std::vector<int>>;

void printGraph(const Graph &graph) {
  std::cout << "Graph:\n";
  for (const auto &[vertex, neighbours] : graph.adjacency_list) {
    std::cout << vertex << ": ";
    for (const auto &neighbour : neighbours) {
      std::cout << neighbour << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}

void printMatrix(const Matrix &matrix) {
  std::cout << "Matrix:\n ";
  for (int i = 0; i < matrix.size(); ++i) {
    std::cout << "_" << i;
  }
  std::cout << "\n";
  int counter = 0;
  for (const auto &line : matrix) {
    std::cout << counter++ << "|";
    for (const auto &val : line) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}

void removeDuplicatesFromGraph(Graph &graph) {
  for (auto &[vertex, neighbours] : graph.adjacency_list) {
    for (auto &neighbour : neighbours) {
      auto &nn = graph.adjacency_list[neighbour];
      nn.erase(std::remove(nn.begin(), nn.end(), vertex), nn.end());
    }
  }
}

Graph readGraphFromFile(const std::string &filename) {
  Graph graph;
  std::ifstream file(filename);
  std::set<int> verticies;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::stringstream ss(line);
      int key;
      ss >> key;
      ss.ignore(); // ':'
      verticies.insert(key);

      int value;
      while (ss >> value) {
        graph.adjacency_list[key].push_back(value);
        verticies.insert(value);
        if (ss.peek() == ',') {
          ss.ignore();
        }
      }
    }
    file.close();
  } else {
    std::cerr << "Error: Cannot to open file \"" << filename << "\"" << std::endl;
  }

  removeDuplicatesFromGraph(graph);
  graph.no_of_verticies = verticies.size();
  graph.largest_vertex = *verticies.rbegin();
  for (const auto &[vertex, neighbours] : graph.adjacency_list) {
    graph.no_of_edges += neighbours.size();
  }
  return graph;
}

void mirrorMatrix(Matrix &matrix) {
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      if (matrix[i][j] == 1) {
        matrix[j][i] = 1;
      }
    }
  }
}

Matrix createAdjacencyMatrix(const Graph &graph) {
  int n = graph.largest_vertex + 1;
  Matrix matrix(n, std::vector<int>(n, 0));
  for (const auto &[vertex, neighbours] : graph.adjacency_list) {
    for (const auto &neighbour : neighbours) {
      matrix[vertex][neighbour] = 1;  
    }
  }
  mirrorMatrix(matrix);
  return matrix;
}

int main() {
  Graph graph = readGraphFromFile("in.txt");
  printGraph(graph);
  Matrix matrix = createAdjacencyMatrix(graph);
  printMatrix(matrix);
  return 0;
}
