/**
 * @file main.cpp
 * @author Richard Travnicek (TRA0117)
 * @date 2024-05-10
 */

#include <iostream>
#include <array>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using std::string, std::vector, std::array, std::ifstream, std::getline, std::cout, std::endl;
enum Pomeranc {
  Zadny = 0,
  Dobry,
  Nakazeny
};
using Police = vector<vector<Pomeranc>>;
struct Pozice {
  uint radek;
  uint sloupec;

  /// Potrebne pro std::sort => std::set
  friend bool operator<(const Pozice& a, const Pozice& b) {
    if (a.radek < b.radek) return true;
    else if (a.radek > b.radek) return false;
    else {
      if (a.sloupec < b.sloupec) return true;
    }
    return false;
  }
};
using setPozic = std::set<Pozice>;

/**
 * @brief Nacte soubor pomerancu
 * 
 * @param cesta Cesta k souboru
 * @return Police pomerancu
 */
Police nacti_soubor(string cesta) {
  Police p;
  ifstream s(cesta);
  if (!s.is_open()) {
    cout << "Chyba otevirani souboru" << endl;
    std::exit(-2);
  }

  string abcd;
  uint radky, sloupce;
  getline(s, abcd);
  radky = std::stoul(abcd);
  getline(s, abcd);
  sloupce = std::stoul(abcd);

  p.reserve(radky);
  for (uint i = 0; i < radky; i++) {
    getline(s, abcd);

    vector<Pomeranc> radek;
    for (uint j = 0; j < sloupce; j++) {
      radek.push_back(static_cast<Pomeranc>(abcd[j] - '0'));
    }

    p.push_back(radek);
  }
  return p;
}

/**
 * @brief Vykresli do konzole stav police
 * 
 * @param p Police pro vykresleni 
 */
void vykresli_polici([[maybe_unused]] const Police &p) {
#ifdef DEBUG
  for (const auto& r : p) {
    for (const auto& s : r) {
      cout << s;
    }
    cout << "\n";
  }
  cout << endl;
#endif
}

/**
 * @brief Zkontroluje jestli dana pozice neni mimo polici
 * 
 * @param p Police
 * @param poz Pozice kterou zkontrolovat
 * @return `true` pokud je pozice platna
 */
bool zkontroluj_pozici(const Police& p, const Pozice& poz) {
  if (poz.radek > p.size() - 1 || poz.sloupec > p[0].size() - 1) return false;
  return true;
}

/**
 * @brief Nakazi sousedy pomerance na dane pozici
 * 
 * @param p Police s pomeranci
 * @param[out] set Set pozic s nove nakazenymi pomeranci
 * @param poz Pozice pomerance ktery nakazi ostatni
 */
void nakaz_sousedy(Police& p, setPozic& set, const Pozice& poz) {
  array<Pozice, 4> tyhle;
  tyhle[0] = {poz.radek - 1, poz.sloupec}; // Nad
  tyhle[1] = {poz.radek, poz.sloupec + 1}; // Vpravo
  tyhle[2] = {poz.radek + 1, poz.sloupec}; // Pod
  tyhle[3] = {poz.radek, poz.sloupec - 1}; // Vlevo

  for (const auto& t : tyhle) {
    if (!zkontroluj_pozici(p, t)) continue;
    if (p[t.radek][t.sloupec] == Dobry) {
      p[t.radek][t.sloupec] = Nakazeny;
      set.insert(t);
    }
  }
}

/**
 * @brief Prohleda polici a najde vsechny pomerance daneho stavu
 * 
 * @param p Police kterou prohledat
 * @param stav Jake pomerace najit
 * @return Set pozic pomerancu
 */
setPozic najdi_typ(const Police& p, Pomeranc stav) {
  setPozic hledane;
  for (uint i = 0; i < p.size(); i++) {
    for (uint j = 0; j < p[0].size(); j++) {
      auto& pomeranc = p[i][j];
      if (pomeranc != stav) continue;

      Pozice tady = {i, j};
      hledane.insert(tady);
    }
  }
  return hledane;
}

/**
 * @brief Hlavni funkce programu
 * 
 * @param p Police kterou nakazit
 * @return Pocet kroku do uplneho nakazeni. Pokud neni zadny nakazeny `-1`
 */
int delej(const Police& p) {
  Police kopie = p;
  setPozic nakazene;
  int pocetKroku = 0;
  
  nakazene = najdi_typ(p, Nakazeny);

  while (!nakazene.empty()) {
    pocetKroku++;
    setPozic noveNakazene;
    for (const auto& poz : nakazene) {
      nakaz_sousedy(kopie, noveNakazene, poz);
    }
    vykresli_polici(kopie);
    nakazene = noveNakazene;
  }

  // Pokud po nakazeni vsech jeste existuji dobre musi existovat oddeleny ostrov
  if (!najdi_typ(kopie, Dobry).empty()) return -1;
  return --pocetKroku;
}

/**
 * @brief `./main soubor.txt`
 * Bere jeden parametr, adresu souboru s polici pomerancu.
 * Pokud neni dan zkusi najit `./test.txt`
 * 
 * @return Pocet kroku do nakazeni vsech nebo `-1`
 */
int main(int argc, char const *argv[]) {
  string cesta = "./test.txt";
  if (argc == 2) {
    cesta = argv[1];
  }

  Police pol = nacti_soubor(cesta);
  vykresli_polici(pol);
  cout << "Vysledek: " << delej(pol) << endl;
  return 0;
}
