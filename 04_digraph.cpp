/* 
 * Tests pour la classe générique Digraph<T>.
 */
#include "digraph.h"
#include <iostream>

int main() {
  int erreur = 0, som = 15, arr = 34;
  Digraph<std::string> graphe;
	std::string vertices [] = {"BIC","BMO","BNP","ATB","BEA","AXA","NBG", 
													"BOC","RBC","BOA","LCL","BNS","CIC","BNC", 
													"ING"};
	std::string arcs [] = {"NBG","LCL","NBG","AXA","LCL","RBC","LCL","BOA", 
												"LCL","BNS","BNS","BOA","BNS","BIC","BNS","CIC", 
												"CIC","LCL","CIC","ING","ATB","CIC","ATB","BIC", 
												"ATB","BNP","ING","ATB","ING","BNC","BNC","NBG", 
												"BNC","BEA","BOC","NBG","BOC","AXA","BNP","BMO", 
												"BNP","BEA","BIC","BMO","BIC","BNP","BMO","BOA", 
												"BMO","NBG","BMO","AXA","BOA","RBC","BOA","NBG",
												"RBC","NBG","BEA","AXA","BEA","BOC","BEA","ING", 
												"BEA","ATB","AXA","BNP"};
	double emprunts [] = {5320,1500,4420,3900,8010,6370,5320,2313,5500,4200,
												7622,1700,3050,1700,1302,4710,4500,1740,2200,4000,
												5000,3012,3220,2410,3240,3440,5100,7400,3800,1100,
												3900,9390,2100,9200};
	for(int i = 0, j = 0; i < arr && j < 2 * arr; i++, j += 2)
		graphe.inserer(arcs[j], arcs[j + 1], emprunts[i]);
  if(graphe.sommets() != som || graphe.arcs() != arr) {
    std::cerr << "ECHEC - I" << std::endl;
    erreur++;
  }
	if(graphe.dette("NBG") != 3800 + 7400 + 3240 + 1740 + 4710 ||
			graphe.dette("BNP") != 3220 + 3050 + 9200 ||
			graphe.dette("CIC") != 7622 + 2313 ||
			graphe.dette("ING") != 4200 + 9390 ||
			graphe.dette("BNS") != 8010 ||
			graphe.dette("LCL") != 5320 + 5500 ||
			graphe.dette("BOA") != 3900 + 6370 + 2410 ||
			graphe.dette("BEA") != 4500 + 5000 ||
			graphe.dette("BMO") != 4000 + 3012 ||
			graphe.dette("BOC") != 3900 ||
			graphe.dette("BNC") != 1302) {
		std::cerr << "ECHEC - II" << std::endl;
		erreur++;
	}
	Digraph<std::string> copy(graphe);
	copy.supprimer("BEA", "BOC");
	copy.supprimer("ING", "BNC");
	copy.supprimer("BMO");
	copy.supprimer("CIC");
	if(copy.dette("BOC") != 0 ||
			copy.dette("BNC") != 0 ||
			copy.dette("BOA") != 3900 + 6370 ||
			copy.dette("NBG") != 3800 + 7400 + 1740 + 4710 ||
			copy.dette("AXA") != 1500 + 2200 + 1100 || 
			copy.dette("LCL") != 5320 ||
			copy.dette("ING") != 9390) {
		std::cerr << "ECHEC - III" << std::endl;
		erreur++;
	}
	std::set<std::string> S({"BIC", "BMO", "BNP", "BEA", "AXA", "ATB"});
	Digraph<std::string> sous_graphe = graphe.cooperative(S);
  if(sous_graphe.sommets() != 6 || sous_graphe.arcs() != 10) {
    std::cerr << "ECHEC - IV" << std::endl;
    erreur++;
	}
	int old_erreur = erreur;
	for(std::set<std::string>::iterator i = S.begin(); i != S.end(); ++i)
		if(!sous_graphe.sommet(*i))
			erreur++;
  if(old_erreur != erreur ||
			!sous_graphe.arc("ATB", "BIC") ||
			!sous_graphe.arc("ATB", "BNP") ||
			!sous_graphe.arc("AXA", "BNP") ||
			!sous_graphe.arc("BEA", "ATB") ||
			!sous_graphe.arc("BEA", "AXA") ||
			!sous_graphe.arc("BIC", "BMO") ||
			!sous_graphe.arc("BIC", "BNP") ||
			!sous_graphe.arc("BMO", "AXA") ||
			!sous_graphe.arc("BNP", "BEA") ||
			!sous_graphe.arc("BNP", "BMO")) {
		std::cerr << "ECHEC - V" << std::endl;
		erreur++;
	}
	if(graphe.dette(sous_graphe) != 4500 + 1700 + 5320 + 1500 + 2200) {
    std::cerr << "ECHEC - VI" << std::endl;
    erreur++;
	}
	if(graphe.dette(graphe) != 0 || sous_graphe.dette(sous_graphe) != 0) {
		std::cerr << "ECHEC - VII" << std::endl;
		erreur++;
	}
	sous_graphe.supprimer("BNP", "BEA");
	sous_graphe.supprimer("AXA", "BNP");
	if(graphe.dette(sous_graphe) != 4500 + 1700 + 5320 + 1500 + 2200) {
    std::cerr << "ECHEC - VIII" << std::endl;
    erreur++;
	}
	sous_graphe.supprimer("BNP");
	if(graphe.dette(sous_graphe) != 4500 + 1700 + 5320 + 1500 + 2200 + 5000 + 4000) {
    std::cerr << "ECHEC - IX" << std::endl;
    erreur++;
	}
	std::set<std::string> T({"LCL"});
  sous_graphe = graphe.cooperative(T);
	if(graphe.dette("LCL") != graphe.dette(sous_graphe) ||
			graphe.dette("LCL") != 5320 + 5500 ||
			graphe.dette(sous_graphe) != 5320 + 5500) {
		std::cerr << "ECHEC - X" << std::endl;
		erreur++;
	}
	if(sous_graphe.dette("LCL") != 0 || sous_graphe.dette(sous_graphe) != 0) {
		std::cerr << "ECHEC - XI" << std::endl;
		erreur++;
	}
	T.insert("NBG");
	sous_graphe = graphe.cooperative(T);
	if(sous_graphe.dette("NBG") != 0 || 
			sous_graphe.dette("LCL") != 5320 ||
			graphe.dette(sous_graphe) != 4710 + 1740 + 3240 + 7400 + 3800 + 5500) {
    std::cerr << "ECHEC - XII" << std::endl;
    erreur++;
  }
	T.insert("ING");
	sous_graphe = graphe.cooperative(T);
	if(sous_graphe.dette("NBG") != 0 ||
			sous_graphe.dette("ING") != 0 ||
			sous_graphe.dette("LCL") != 5320 ||
			graphe.dette(sous_graphe) != 4710 + 1740 + 3240 + 7400 + 3800 + 5500 + 4200 + 9390) {
    std::cerr << "ECHEC - XIII" << std::endl;
    erreur++;
  }
	T.insert("BNC");
	sous_graphe = graphe.cooperative(T);
	if(sous_graphe.dette("NBG") != 4710 ||
			sous_graphe.dette("ING") != 0 ||
			sous_graphe.dette("BNC") != 1302 ||
			sous_graphe.dette("LCL") != 5320 ||
			graphe.dette(sous_graphe) != 1740 + 3240 + 7400 + 3800 + 5500 + 4200 + 9390) {
    std::cerr << "ECHEC - XIV" << std::endl;
    erreur++;
  }
	Digraph<int> digraph;
	std::set<int> N;
	for(int i = 10; i < 1000; i += 10) {
		N.insert(i);
		for(int j = 1; j < 10; j++) {
			digraph.inserer(i, i + j, 3105);
			digraph.inserer(i, i - j, 3173);
		}
	}
	Digraph<int> subgraph = digraph.cooperative(N);
	if(subgraph.sommets() != 99 || subgraph.arcs() != 0) {
		std::cerr << "ECHEC - XVI" << std::endl;
		erreur++;
	}
	old_erreur = erreur;
	for(int i = 20; i < 990; i += 10)
		if(digraph.dette(i) != 0 ||
				digraph.dette(i + 1) != 3105 + 3173 ||
				digraph.dette(i - 1) != 3105 + 3173 ||
				digraph.dette(i + 5) != 3105 + 3173 ||
				digraph.dette(i - 5) != 3105 + 3173)
			erreur++;
	if(old_erreur != erreur) {
		std::cerr << "ECHEC - XVII" << std::endl;
		erreur++;
	}
	if(digraph.dette(subgraph) != 0) {
		std::cerr << "ECHEC - XVIII" << std::endl;
    erreur++;
	}
	std::set<int> M;
	N.clear();
	for(int i = 10; i < 1000; i += 20) {
		N.insert(i + 1);
		N.insert(i);
		M.insert(i);
		M.insert(i - 1);
	}
	subgraph = digraph.cooperative(N);
	if(digraph.dette(subgraph) != 3173 * 49) {
		std::cerr << "ECHEC - XIX" << std::endl;
		erreur++;
	}	
	subgraph = digraph.cooperative(M);
	if(digraph.dette(subgraph) != 3105 * 49) {
		std::cerr << "ECHEC - XX" << std::endl;
		erreur++;
	}	
  if(erreur == 0)
    std::cout << "\t==> OK" << std::endl;
  return erreur;
}
