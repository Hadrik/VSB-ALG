#include <iostream>
#include <GraphLoader.h>
#include <GraphTools.h>

int main(int argc, char const *argv[]) {
  std::string path = "./in.txt";
  if (argc == 1) {
    std::cout << "Neni zadana cesta k souboru grafu, pouzivam " << path << "\n";
  } else {
    path = argv[1];
  }

  auto g = GraphLoader::load(path);

  std::cout << "\nNacteny graf:\n";
  GraphLoader::print(g);
  std::cout << "Graph " << (GraphTools::isBiparte(g) ? "JE" : "NENI") << " bipartitni." << std::endl;
  return 0;
}
