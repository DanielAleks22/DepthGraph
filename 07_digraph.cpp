/* 
 * Tests pour la classe générique Digraph<T>.
 */
 
#include "digraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <set>

class Chrono {
	public:
		Chrono() {}
		~Chrono() {}
		void debut() {
			start = std::chrono::steady_clock::now();
		}
		void fin() {
			end = std::chrono::steady_clock::now();
			duree = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		}
		float duree;
	private:
		std::chrono::steady_clock::time_point start, end;
};

int main(int argc, char * argv[]) {
  int erreur = 0;
  Digraph<int> regular;
  std::string line;
	std::ifstream input_graph(argv[1]);
  while(std::getline(input_graph, line) && !line.empty()) {
    std::stringstream ss(line);
 		int u, v;
    double emprunt;
    ss >> u >> v >> emprunt;
    regular.inserer(u, v, emprunt);
  }
	std::vector<int> dettes, prets;
	std::ifstream input_dp(argv[2]);
  while(std::getline(input_dp, line) && !line.empty()) {
    std::stringstream ss(line);
 		int d, p;
    ss >> d >> p;
		dettes.push_back(d);
		prets.push_back(p);
  }
	std::set<int> sg_1;
	double sg_1_dette = 234362, sg_1_pret = 224141;
	std::ifstream input_sg_1(argv[3]);
  while(std::getline(input_sg_1, line) && !line.empty()) {
  	std::stringstream ss(line);
 		int s;
    ss >> s;
		sg_1.insert(s);
  }
	std::set<int> sg_2;
	double sg_2_dette = 239021, sg_2_pret = 202559;
	std::ifstream input_sg_2(argv[4]);
  while(std::getline(input_sg_2, line) && !line.empty()) {
  	std::stringstream ss(line);
 		int s;
    ss >> s;
		sg_2.insert(s);
  }
	Chrono timer;
	timer.debut();
	if(regular.sommets() != 100 || regular.arcs() != 200)
		erreur++;
	for(int i = 0; i < 100; i++) {
		if(regular.dette(i) != dettes[i])
			erreur++;
	}
	for(int i = 0; i < 100; i++)
		if(regular.pret(i) != prets[i])
			erreur++;
	Digraph<int> sg_one = regular.cooperative(sg_1);
	Digraph<int> sg_two = regular.cooperative(sg_2);
	if(regular.dette(sg_one) != sg_1_dette ||
			regular.dette(sg_two) != sg_2_dette)
		erreur++;
	if(regular.pret(sg_one) != sg_1_pret ||
			regular.pret(sg_two) != sg_2_pret)
		erreur++;
	timer.fin();
	if(erreur != 0 || timer.duree > 25000) {
		std::cerr << "ECHEC - PERFORMANCES" << std::endl;
		return erreur;
	}
	std::cout << "\t==> OK" << std::endl;
  return 0;
}
