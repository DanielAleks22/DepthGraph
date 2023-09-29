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
	if(graphe.pret("NBG") != 5320 + 1500 ||
			graphe.pret("BNP") != 4000 + 5000 ||
			graphe.pret("CIC") != 4200 + 5500 ||
			graphe.pret("ING") != 1700 + 1302 ||
			graphe.pret("BNS") != 6370 + 5320 + 2313 ||
			graphe.pret("LCL") != 4420 + 3900 + 8010 ||
			graphe.pret("BOA") != 5100 + 7400 ||
			graphe.pret("BEA") != 1100 + 3900 + 9390 + 2100 ||
			graphe.pret("BMO") != 2410 + 3240 + 3440 ||
			graphe.pret("BOC") != 1740 + 2200 ||
			graphe.pret("BNC") != 4710 + 4500) {
		std::cerr << "ECHEC - II" << std::endl;
		erreur++;
	}
	Digraph<std::string> copy(graphe);
	copy.supprimer("BOC", "AXA");
	copy.supprimer("ING", "BNC");
	copy.supprimer("BMO");
	copy.supprimer("CIC");
	if(copy.pret("BOC") != 1740 ||
			copy.pret("BNC") != 4710 + 4500 ||
			copy.pret("BOA") != 5100 + 7400 ||
			copy.pret("ATB") != 3050 + 1700 ||
			copy.pret("AXA") != 9200 || 
			copy.pret("BNS") != 6370 + 5320 ||
			copy.pret("ING") != 1700) {
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
	if(graphe.pret(sous_graphe) != 3240 + 2410 + 7622 + 9390 + 3900) {
    std::cerr << "ECHEC - VI" << std::endl;
    erreur++;
	}
	if(graphe.pret(graphe) != 0 || sous_graphe.pret(sous_graphe) != 0) {
		std::cerr << "ECHEC - VII" << std::endl;
		erreur++;
	}
	sous_graphe.supprimer("BNP", "BEA");
	sous_graphe.supprimer("AXA", "BNP");
	if(graphe.pret(sous_graphe) != 3240 + 2410 + 7622 + 9390 + 3900) {
    std::cerr << "ECHEC - VIII" << std::endl;
    erreur++;
	}
	sous_graphe.supprimer("BNP");
	if(graphe.pret(sous_graphe) != 3240 + 2410 + 7622 + 9390 + 3900 + 9200 + 3220 + 3050) {
    std::cerr << "ECHEC - IX" << std::endl;
    erreur++;
	}
	std::set<std::string> T({"BOA"});
  sous_graphe = graphe.cooperative(T);
	if(graphe.pret("BOA") != graphe.pret(sous_graphe) ||
			graphe.pret("BOA") != 5100 + 7400 ||
			graphe.pret(sous_graphe) != 5100 + 7400) {
		std::cerr << "ECHEC - X" << std::endl;
		erreur++;
	}
	if(sous_graphe.pret("BOA") != 0 || sous_graphe.pret(sous_graphe) != 0) {
		std::cerr << "ECHEC - XI" << std::endl;
		erreur++;
	}
	T.insert("NBG");
	sous_graphe = graphe.cooperative(T);
	if(sous_graphe.pret("NBG") != 0 || 
			sous_graphe.pret("BOA") != 7400 ||
			graphe.pret(sous_graphe) != 5100 + 5320 + 1500) {
    std::cerr << "ECHEC - XII" << std::endl;
    erreur++;
  }
	T.insert("ING");
	sous_graphe = graphe.cooperative(T);
	if(sous_graphe.pret("NBG") != 0 ||
			sous_graphe.pret("ING") != 0 ||
			sous_graphe.pret("BOA") != 7400 ||
			graphe.pret(sous_graphe) != 5100 + 5320 + 1500 + 1302 + 1700) {
    std::cerr << "ECHEC - XIII" << std::endl;
    erreur++;
  }
	T.insert("BNC");
	sous_graphe = graphe.cooperative(T);
	if(sous_graphe.pret("NBG") != 0 ||
			sous_graphe.pret("ING") != 1302 ||
			sous_graphe.pret("BNC") != 4710 ||
			sous_graphe.pret("BOA") != 7400 ||
			graphe.pret(sous_graphe) != 5100 + 5320 + 1500 + 1700 + 4500) {
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
		if(digraph.pret(i) != (3105 + 3173) * 9 ||
				digraph.pret(i + 1) != 0 ||
				digraph.pret(i - 1) != 0 ||
				digraph.pret(i + 5) != 0 ||
				digraph.pret(i - 5) != 0) 
			erreur++;
	if(old_erreur != erreur) {
		std::cerr << "ECHEC - XVII" << std::endl;
		erreur++;
	}
	if(digraph.pret(subgraph) != 3105 * 9 * 99 + 3173 * 9 * 99) {
		std::cerr << "ECHEC - XVIII" << std::endl;
    erreur++;
	}
	std::set<int> M;
	N.clear();
	for(int i = 10; i < 1000; i += 10) {
		N.insert(i + 1);
		N.insert(i);
		M.insert(i);
		M.insert(i - 1);
	}
	subgraph = digraph.cooperative(N);
	if(digraph.pret(subgraph) != 3105 * 8 * 99 + 3173 * 8 * 99 + 3173) {
		std::cerr << "ECHEC - XIX" << std::endl;
		erreur++;
	}
	subgraph = digraph.cooperative(M);
	if(digraph.pret(subgraph) != 3105 * 8 * 99 + 3105 +  3173 * 8 * 99) {
		std::cerr << "ECHEC - XX" << std::endl;
		erreur++;
	}	
  if(erreur == 0)
    std::cout << "\t==> OK" << std::endl;
  return erreur;
}
