#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#pragma once

#include <queue>
#include <vector>

class GraphTools {
public:
  static bool isBiparte(const std::vector<std::vector<int>> &graph);

private:
  GraphTools() = delete;
};

#endif