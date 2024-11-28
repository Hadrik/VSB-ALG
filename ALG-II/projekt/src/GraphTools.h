#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#pragma once

#include <queue>
#include <vector>

class GraphTools {
public:
  /**
   * @brief Check if graph is bipatre
   * 
   * @param graph adjacency matrix of the graph
   * @return ```bool```
   */
  static bool isBiparte(const std::vector<std::vector<int>> &graph);

private:
  GraphTools() = delete;
};

#endif