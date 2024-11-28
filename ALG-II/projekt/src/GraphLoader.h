#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class GraphLoader {
public:
  static std::vector<std::vector<int>> load(const std::string &path);

  static bool verify(const std::vector<std::vector<int>> &graph, size_t expected);
  static void print(const std::vector<std::vector<int>> &graph);
private:
  GraphLoader() = delete;
};

#endif