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
#include <cmath>

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
	double EPSILON = 0.5;
  int erreur = 0;
  Digraph<int> complete;
  std::string line;
	std::ifstream input_graph(argv[1]);
  while(std::getline(input_graph, line) && !line.empty()) {
    std::stringstream ss(line);
 		int u, v;
    double emprunt;
    ss >> u >> v >> emprunt;
    complete.inserer(u, v, emprunt);
  }
	std::vector<double> dettes, prets;
	std::ifstream input_dp(argv[2]);
  while(std::getline(input_dp, line) && !line.empty()) {
    std::stringstream ss(line);
 		double d, p;
    ss >> d >> p;
		dettes.push_back(d);
		prets.push_back(p);
  }
	std::set<int> S({55,52,47,66,51,24,62,70,21,27,25,18,54,12,5,10,0,60,99,76});
	double dette = 8726093, pret = 8765272;
	Chrono timer;
	timer.debut();
	if(complete.sommets() != 100 || complete.arcs() != 9900)
		erreur++;
	Digraph<int> sg = complete.cooperative(S);
	if(std::fabs(complete.dette(sg) - dette) > EPSILON)
		erreur++;
	if(std::fabs(complete.pret(sg) - pret) > EPSILON)
		erreur++;
	complete.reduire(sg);
	for(int i = 0; i < 100; i++)
		if(std::fabs(complete.dette(i) - dettes[i]) > EPSILON)
			erreur++;
	for(int i = 0; i < 100; i++)
		if(std::fabs(complete.pret(i) - prets[i]) > EPSILON)
			erreur++;
	timer.fin();
	if(erreur != 0 || timer.duree > 15000000) {
		std::cerr << "ECHEC - PERFORMANCES" << std::endl;
		return erreur;
	}
	std::cout << "\t==> OK" << std::endl;
  return 0;
}
