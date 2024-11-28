#include "GraphLoader.h"

std::vector<std::vector<int>> GraphLoader::load(const std::string &path) {
  std::ifstream file(path);
  std::vector<std::vector<int>> graph;
  std::string line;

  std::getline(file, line);
  const auto size = std::stoul(line);

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::vector<int> row;
    // nacitam je jako char at nemusi mezi sloupci byt mezery
    char num;
    while (ss >> num) {
      if (num != '0' && num != '1') {
        std::cerr << "File contains different values than 0 or 1" << std::endl;
        return {{}};
      }
      row.push_back(num - '0');
    }
    graph.push_back(row);
  }
  file.close();

  if (!verify(graph, size)) {
    std::cerr << "Graph size different than expected!" << std::endl;
    return {{}};
  }

  return graph;
}

bool GraphLoader::verify(const std::vector<std::vector<int>> &graph, size_t expected) {
  if (graph.size() != expected) return false;

  for (const auto &row : graph) {
    if (row.size() != expected) return false;
  }

  return true;
}

void GraphLoader::print(const std::vector<std::vector<int>> &graph) {
  for (const auto &row : graph) {
    for (const int val : row) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}
