#include "GraphTools.h"

bool GraphTools::isBiparte(const std::vector<std::vector<int>> &graph) {
  // -1 = neprirazena; 0,1 = strany
  std::vector<int> side(graph.size(), -1);
  side[0] = 0;

  // zacnu na vrcholu 0
  std::queue<int> q;
  q.push(0);

  // prochazim vsechny vrcholy
  while (!q.empty()) {
    int vert = q.front();
    q.pop();

    for (std::size_t nbr = 0; nbr < graph.size(); nbr++) {
      // jsou propojene?
      if (graph.at(vert).at(nbr) == 0) continue;

      // nenavstiveny?
      if (side[nbr] == -1) {
        side[nbr] = side[vert] ^ 1; // xor 1 = toggle
        q.push(nbr);
      }

      // stejna strana?
      if (side[nbr] == side[vert]) {
        // kdyz ma vrchol a jeho soused stejnou stranu neni bipartitni
        return false;
      }
    }
  }
  
  return true;
}
