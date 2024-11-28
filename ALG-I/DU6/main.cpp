#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
#include <random>

using std::vector, std::next_permutation, std::cout, std::numeric_limits, std::chrono::high_resolution_clock, std::chrono::_V2::system_clock;

int assignmentProblem(const vector<vector<int>>& costMatrix) {
  size_t size = costMatrix.size();
  if (size != costMatrix[0].size()) return -1;
  int min_cost = numeric_limits<int>::max();
  vector<size_t> assignment(size);
  for (size_t i = 0; i < size; i++) {
    assignment[i] = i;
  }

  do {
    int current_cost = 0;
    for (size_t i = 0; i < size; i++) {
      current_cost += costMatrix[i][assignment[i]];
    }
    if (current_cost < min_cost) min_cost = current_cost;
  } while (next_permutation(assignment.begin(), assignment.end()));

  return min_cost;
}

vector<vector<int>> randomMatrix(size_t size, int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  vector<vector<int>> result(size);
  for (auto &v : result) {
    for (size_t i = 0; i < size; i++) {
      v.push_back(distribution(gen)); 
    }
  }

  return result;
}

int main() {
  vector<vector<int>> testCostMatrix = {
    {9, 2, 7, 8},
    {6, 4, 3, 7},
    {5, 8, 1, 8},
    {7, 6, 9, 4}
  };
  cout << assignmentProblem(testCostMatrix) << "\n";

  system_clock::time_point start, end;
  std::chrono::duration<double> duration;
  size_t size = 5;
  do {
    auto a = randomMatrix(size, 1, 9);
    start = high_resolution_clock::now();
    auto result = assignmentProblem(a);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "Lowest cost: " << result << "\n";
    cout << "Matrix size: " << size << "\n";
    cout << "Duration: " << duration.count() << "\n\n";
    size++;
  } while (duration.count() < 10.0);
  
  return 0;
}