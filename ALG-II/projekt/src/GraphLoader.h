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
  /**
   * @brief Load graph adjacency matrix
   * 
   * @param path path to the file
   * @return adjacency matrix
   */
  static std::vector<std::vector<int>> load(const std::string &path);

  /**
   * @brief Verify that the matrix size is as expected
   * 
   * @param matrix adjacency matrix
   * @param expected expected matrix size
   * @return true if correct size
   */
  static bool verify(const std::vector<std::vector<int>> &matrix, size_t expected);
  /**
   * @brief Print matrix to standard output
   * 
   * @param matrix matrix to print
   */
  static void print(const std::vector<std::vector<int>> &matrix);
private:
  GraphLoader() = delete;
};

#endif