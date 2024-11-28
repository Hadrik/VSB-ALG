#include <iostream>
#include <vector>

void printArr(const std::vector<int> &vec) {
  for (const auto &n : vec) {
    std::cout << n << "\n";
  }
  std::cout << std::endl;
}

void selectionSort(std::vector<int> &vec) {
  for (size_t i = 0; i < vec.size() - 1; i++) {
    auto min = i;
    for (size_t j = i + 1; j < vec.size(); j++) {
      if (vec[j] < vec[min]) {
        min = j;
      }
    }
    std::swap(vec[i], vec[min]);
  }
}

void bubbleSort(std::vector<int> &vec) {
  for (size_t i = 0; i < vec.size() - 1; i++) {
    for (size_t j = 0; j < vec.size() - i - 1; j++) {
      if (vec[j] > vec[j + 1]) {
        std::swap(vec[j], vec[j + 1]);
      }
    }
  }
}

void shakerSort(std::vector<int> &vec) {
  size_t left = 0;
  size_t right = vec.size() - 1;
  do {
    // Right to left
    size_t last = 0;
    for (size_t i = left; i < right; i++) {
      if (vec[i] > vec[i + 1]) {
        std::swap(vec[i], vec[i + 1]);
        last = i;
      }
    }
    right = last;

    // Left to right
    last = 0;
    for (size_t i = right; i > left; i--) {
      if (vec[i - 1] > vec[i]) {
        std::swap(vec[i], vec[i - 1]);
        last = i;
      }
    }
    left = last;
  } while (left < right);
}

int main() {
  std::vector<int> vector = {2, 1, 5, 6, 9, 4, 3};
  printArr(vector);
  shakerSort(vector);
  printArr(vector);
  return 0;
}