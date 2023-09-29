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
  Digraph<int> dorogovtsev;
  std::string line;
	std::ifstream input_graph(argv[1]);
  while(std::getline(input_graph, line) && !line.empty()) {
    std::stringstream ss(line);
 		int u, v;
    double emprunt;
    ss >> u >> v >> emprunt;
    dorogovtsev.inserer(u, v, emprunt);
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
	std::set<int> sg_1;
	double sg_1_dette = 4755298, sg_1_pret = 4542022;
	std::ifstream input_sg_1(argv[3]);
  while(std::getline(input_sg_1, line) && !line.empty()) {
  	std::stringstream ss(line);
 		int s;
    ss >> s;
		sg_1.insert(s);
  }
	std::set<int> sg_2;
	double sg_2_dette = 4374310, sg_2_pret = 5991193;
	std::ifstream input_sg_2(argv[4]);
  while(std::getline(input_sg_2, line) && !line.empty()) {
  	std::stringstream ss(line);
 		int s;
    ss >> s;
		sg_2.insert(s);
  }
	Chrono timer;
	timer.debut();
	if(dorogovtsev.sommets() != 3282 || dorogovtsev.arcs() != 6561)
		erreur++;
	for(int i = 0; i < 3282; i++)
		if(std::fabs(dorogovtsev.dette(i) - dettes[i]) > EPSILON)
			erreur++;
	for(int i = 0; i < 3282; i++)
		if(std::fabs(dorogovtsev.pret(i) - prets[i]) > EPSILON)
			erreur++;
	Digraph<int> sg_one = dorogovtsev.cooperative(sg_1);
	Digraph<int> sg_two = dorogovtsev.cooperative(sg_2);
	if(std::fabs(dorogovtsev.dette(sg_one) - sg_1_dette) > EPSILON ||
			std::fabs(dorogovtsev.dette(sg_two) != sg_2_dette) > EPSILON)
		erreur++;
	if(std::fabs(dorogovtsev.pret(sg_one) - sg_1_pret) > EPSILON ||
			std::fabs(dorogovtsev.pret(sg_two) - sg_2_pret) > EPSILON)
		erreur++;
	timer.fin();
	if(erreur != 0 || timer.duree > 3000000) {
		std::cerr << "ECHEC - PERFORMANCES" << std::endl;
		return erreur;
	}
	std::cout << "\t==> OK" << std::endl;
  return 0;
}
