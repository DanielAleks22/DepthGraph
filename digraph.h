/* 
 * Classe générique Digraph<T>.
 */
 

#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <set>
#include <map>
#include <tuple>
#include <assert.h>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <stack>
#include <queue>
#include <limits>

template <class T>
class Digraph {
	public:
		Digraph();
		Digraph(const Digraph & autre);
		~Digraph();
		Digraph<T> & operator = (const Digraph<T> & autre);
		
		/*********** Fonctions pour les caractéristiques de graphe ***********/
		// Retourne le nombre de sommets dans graphe.
		int sommets() const;
		// Retourne le nombre d'arcs dans le graphe.
		int arcs() const;
		// Retourne "true" si "u" est un sommet du graphe courant. "false" si 
		// non.
		bool sommet(T u) const;
		// Retourne "true" si "(u,v)" est un arc du graphe courant. "false" si
		// non.
		bool arc(T u, T v) const;

		/*************************** Modificateurs ***************************/
		// Insère le sommet "u" si le graphe ne le contient pas. Ne fait 
		// rien si le graphe contient déjà le sommet "u".
		void inserer(T u);
		// Créé un arc entre les sommets "u" et "v" avec le poids "emprunt", 
		// si le graphe ne contient pas l'arc "(u, v)". Ne fait rien si le
		// graphe contient déjà un arc "(u,v)".
		// Si l'arc doit être créé faut s'assurer que,
		// 	- "u" doit être différent de "v",
		// 	- "emprunt" doit être strictement positif,
		// 		- faut arrêter l'exécution avec la fonction "assert" si les 
		// 		deux conditions plus faut ne sont pas satisfaites,
		// 	- si l'arc "(u,v)" existe déjà, peu importe la valeur de "emprunt",
		//	rien ne	sera fait par la fonction inserer.
		// 	- si l'un ou les deux sommets "u" et "v" n'existent pas dans
		// 	le graphe, ils seront crées.
		void inserer(T u, T v, double emprunt);
		// Supprime le sommet "u" et tous les arcs qui lui sont incidents.
		void supprimer(T u);
		// Supprime l'arc "(u, v)"
		void supprimer(T u, T v);

		/**************************** Sous-graphe ***************************/	
		// Créé un sous-graphe du graphe courant induit par les sommets du 
		// set "S".
		// Un "sous-graphe induit" par les sommets de "S" est un sous-graphe 
		// formé par les sommets de "S" et TOUS les arcs "e=(u,v)" du graphe 
		// courant tel que "u" et "v" sont TOUS deux des sommets de "S".
		//	- Il faut que tous les sommets listés dans "S" soient des
		//	sommets du graphe courant. Faut arrêter l'exécution avec la 
		//	fonction "assert" dans le cas	contraire.
		Digraph<T> cooperative(std::set<T> & S) const;
		
		/********************** Fonctions financières **********************/
		// Retourne le montant total que doit rembourser le sommet "u".
		double dette(T u) const;
		// De même, retourne le montant total que doivent rembourser tous 
		// les sommets du sous-graphe "SG" envers les autres sommets dans 
		// le reste du graphe courant. Attention, on ne comptabilise pas 
		// les dettes internes à "SG", on comptabilise que les dettes d'un 
		// sommet externe à "SG" vers un sommet interne de "SG".
		double dette(const Digraph<T> & SG) const;
		// Retourne le montant total des remboursements que doit recevoir 
		// le sommet "u".
		double pret(T u) const;
		// De même, retourne le montant total des remboursements que doivent
		// recevoir tous les sommets du sous-graphe "SG" de la part des 
		// autres sommets dans le reste du graphe courant. Attention, on ne 
		// comptabilise pas les remboursements internes à "SG", on 
		// comptabilise que les remboursements d'un sommet interne de "SG" 
		// vers un sommet externe à "SG".
		double pret(const Digraph<T> & SG) const;
		// Réduit les dettes circulaires du sommet "s". Voir des explications
		// et un exemple de l'énoncé.
		void reduire(T s);
		// De même, réduit les dettes circulaires d'un sous-graphe "SG". Voir
		// des explications et un exemple dans l'énoncé.
		void reduire(const Digraph<T> & SG);
			
	private:
		
		// Par défaut, le "map" et le "set" sont parcourus en ordre croissant, 
		// ils sont ordonnés (standard C++11).
		std::map<T,std::set<std::tuple<T,double>>> graphe;
		
		//Fonction qui s'occupe de reduire une dette circulaire 
		void reduireDetteCirculaire (std::vector<T>& circuit);

		//Fonction qui trouve un circuit a partir d'un sommet donner
		std::vector<T> rechercheProfondeur(T u);
		//Fonction helper
		void rechercheProfondeur(T u, std::set<T>& visiter, std::vector<T>& order, T debut, bool& trouver);

		//Fonction qui trouve un circuit a partir d'un sous-graphe donner
		std::vector<T> rechercheProfondeurSG(const Digraph<T>& SG);
		//Fonction helper
		void rechercheProfondeurSG(T courrant, std::set<T>& visiter, const Digraph<T>& SG, std::vector<T>& chemin, bool& trouver, bool exterieurSG);
};

/*
//////////////////////////////////////////////////////////
                Fonctions publiques
//////////////////////////////////////////////////////////
*/
template <class T>
Digraph<T>::Digraph() {}

template <class T>
Digraph<T>::Digraph(const Digraph & autre) : graphe(autre.graphe) {}

template <class T>
Digraph<T>::~Digraph() {}

template <class T>
Digraph<T>& Digraph<T>::operator=(const Digraph<T>& autre) {
    if (this != &autre) {
        graphe = autre.graphe;
    }
    return *this;
}


template <class T>
int Digraph<T>::sommets() const {
    return graphe.size();
}

template <class T>
int Digraph<T>::arcs() const {
    int nbArcs = 0;
    for (const auto& paire: graphe) {
        for (const auto& arc: paire.second) {
            nbArcs++;
        }
    }
    return nbArcs;
}

template <class T>
bool Digraph<T>::sommet(T u) const {
    return graphe.find(u) != graphe.end();
}

template <class T>
bool Digraph<T>::arc(T u, T v) const {
    auto it = graphe.find(u);
    if (it != graphe.end()) {
        const auto& voisins = it->second;
        for (auto vit = voisins.begin(); vit != voisins.end(); ++vit) {
            if (std::get<0>(*vit) == v) {
                return true;
            }
        }
    }
    return false;
}

template <class T>
void Digraph<T>::inserer(T u) {
    if (graphe.find(u) != graphe.end()) {
        return;
    }
    graphe[u] = {};
}

template <class T>
void Digraph<T>::inserer(T u, T v, double emprunt) {
    assert(u != v && emprunt >= 0);
    inserer(u);
    inserer(v);
    auto& voisins = graphe[u];
    for (const auto& voisin : voisins) {
        if (std::get<0>(voisin) == v) {
            return;
        }
    }
    voisins.insert(std::make_tuple(v, emprunt));
}

template <class T>
void Digraph<T>::supprimer(T u) {
    graphe.erase(u);
    for (auto& pair : graphe) {
        auto& voisins = pair.second;
        auto it = voisins.begin();
        while (it != voisins.end()) {
            if (std::get<0>(*it) == u) {
                it = voisins.erase(it);
            } else {
                ++it;
            }
        }
    }
}

template <class T>
void Digraph<T>::supprimer(T u, T v) {
    auto it = graphe.find(u);
    if (it != graphe.end()) {
        auto& voisins = it->second;
        auto vit = voisins.begin();
        while (vit != voisins.end()) {
            if (std::get<0>(*vit) == v) {
                vit = voisins.erase(vit);
                return;
            } else {
                ++vit;
            }
        }
    }
}

template <class T>
Digraph<T> Digraph<T>::cooperative(std::set<T> & S) const {
    for (const auto& u : S) {
        assert(sommet(u));
    }
    Digraph<T> SG;
    for (const auto& u : S) {
        SG.inserer(u);
    }
    for (const auto& u : S) {
        for (const auto& voisin : graphe.at(u)) {
            T v = std::get<0>(voisin);
            if (S.count(v) > 0) {
                double emprunt = std::get<1>(voisin);
                SG.inserer(u, v, emprunt);
            }
        }
    }
    return SG;
}

template <class T>
double Digraph<T>::dette(T u) const {
    double total = 0;
    for (const auto& paire : graphe) {
        T v = paire.first;
        if (v != u) {
            for (const auto& voisin : paire.second) {
                if (std::get<0>(voisin) == u) {
                    total += std::get<1>(voisin);
                }
            }
        }
    }
    return total;
}

template <class T>
double Digraph<T>::dette(const Digraph<T> & SG) const {
    double totalDette = 0;
    for (const auto& paire : graphe) {
        T u = paire.first;
        if (!SG.sommet(u)) {
            for (const auto& voisin : paire.second) {
                T v = std::get<0>(voisin);
                double emprunt = std::get<1>(voisin);
                if (SG.sommet(v)) {
                    totalDette += emprunt;
                }
            }
        }
    }

    return totalDette;
}

template <class T>
double Digraph<T>::pret(T u) const {
    double total = 0;
    const auto& voisins = graphe.at(u);
    for (const auto& voisin : voisins) {
        T v = std::get<0>(voisin);
        double emprunt = std::get<1>(voisin);
        total += emprunt;
    }
    
    return total;
}

template <class T>
double Digraph<T>::pret(const Digraph<T> & SG) const {
    double totalPret = 0.0;
    for (const auto& paire : graphe) {
        T u = paire.first;
        if (SG.sommet(u)) {
            for (const auto& voisin : paire.second) {
                T v = std::get<0>(voisin);
                double emprunt = std::get<1>(voisin);
                if (!SG.sommet(v)) {
                    totalPret += emprunt;
                }
            }
        }
    }
    return totalPret;
}

template <class T>
void Digraph<T>::reduire(T s) {
    assert(sommet(s));

    std::vector<T> circuit = rechercheProfondeur(s);
    while (!circuit.empty()) {
        reduireDetteCirculaire(circuit);
        circuit.clear();
        circuit = rechercheProfondeur(s);
    }

}

template <class T>
void Digraph<T>::reduire(const Digraph<T> & SG) {

    std::vector<T> circuit = rechercheProfondeurSG(SG);
    while(!circuit.empty()) {
        reduireDetteCirculaire(circuit);
        circuit.clear();
        circuit = rechercheProfondeurSG(SG);
    }

}

/*
//////////////////////////////////////////////////////////
                Fonctions privees
//////////////////////////////////////////////////////////
*/
template <class T>
void Digraph<T>::reduireDetteCirculaire (std::vector<T>& circuit) {
    //permet d'initialiser la dette a la valeur max possible
    double minDette = std::numeric_limits<double>::max();
    for (std::size_t i = 0; i < circuit.size() - 1; ++i) {
        T u = circuit[i];
        T v = circuit[i + 1];
        for (const auto& arc : graphe[u]) {
            if (std::get<0>(arc) == v) {
                double debt = std::get<1>(arc);
                minDette = std::min(minDette, debt);
            }
        }
    }
    //Reduit la dette dans le chemin trouver
    for (std::size_t i = 0; i < circuit.size() - 1; ++i) {
        T u = circuit[i];
        T v = circuit[i + 1];
        auto& voisins = graphe[u];
        auto it = voisins.begin();
        while (it != voisins.end()) {
            if (std::get<0>(*it) == v) {
                auto& arc = const_cast<std::tuple<T, double>&>(*it); 
                double& emprunt = std::get<1>(arc); 
                emprunt -= minDette;
                if (emprunt <= 0) {
                    it = voisins.erase(it);
                } else {
                    ++it;
                }
                break;
            } else {
                ++it;
            }
        }
    }
    //Mettre a jour la dette entre le debut et la fin du circuit si necessaire
    T start = circuit.front();
    T end = circuit.back();
        if (start != end) {
            auto &voisins_start = graphe[start];
            auto &voisins_end = graphe[end];

            if (arc(start, end)) {
                auto &voisins_start = graphe[start];
                for (auto it = voisins_start.begin(); it != voisins_start.end(); ++it) {
                    if (std::get<0>(*it) == end) {
                        auto& arc = const_cast<std::tuple<T, double>&>(*it);
                        double& emprunt = std::get<1>(arc);
                        emprunt += minDette;
                        if (emprunt <= 0) {
                            it = voisins_start.erase(it);
                        }
                        break;
                    }
                }
            } else if (arc(end, start)) {
                auto &voisins_end = graphe[end];
                for (auto it = voisins_end.begin(); it != voisins_end.end(); ++it) {
                    if (std::get<0>(*it) == start) {
                        auto& arc = const_cast<std::tuple<T, double>&>(*it);
                        double& emprunt = std::get<1>(arc);
                        emprunt -= minDette;
                        if (emprunt <= 0) {
                            it = voisins_end.erase(it);
                        }
                        break;
                    }
                }
            } else {
                inserer(start, end, minDette);
            }
        }
}

template <class T>
std::vector<T> Digraph<T>::rechercheProfondeur(T u) {
    std::set<T> visiter;
    std::vector<T> circuit;
    std::vector<T> circuitVide;
    bool trouver = false;
    rechercheProfondeur(u, visiter, circuit, u, trouver);
    if(circuit.size() > 2) {
        return circuit;
    }

    return circuitVide;
    
}

template <class T>
void Digraph<T>::rechercheProfondeur(T u, std::set<T>& visiter, std::vector<T>& circuit, T debut, bool& trouver) {
    visiter.insert(u);
    circuit.push_back(u);
    for (const auto& voisin : graphe.at(u)) {
        T v = std::get<0>(voisin);
        if (v == debut && visiter.count(u) > 0) {
            circuit.push_back(debut);
            trouver = true;
            return;
        }
        if (visiter.count(v) == 0 && !trouver) {
            rechercheProfondeur(v, visiter, circuit, debut, trouver);
            if(trouver) {
                return;
            }
        }
    }
    circuit.pop_back();
}

template <class T>
std::vector<T> Digraph<T>::rechercheProfondeurSG(const Digraph<T>& SG) {
    std::vector<T> chemin;
    std::vector<T> cheminVide;

    for (const auto& sommet : SG.graphe) {
        T start = sommet.first;
        std::set<T> visiter;
        bool trouver = false;

        rechercheProfondeurSG(start, visiter, SG, chemin, trouver, false);
        if (trouver) {
            return chemin;
        }
        chemin.clear();
    }

    return cheminVide;
}

template <class T>
void Digraph<T>::rechercheProfondeurSG(T courrant, std::set<T>& visiter, const Digraph<T>& SG, std::vector<T>& chemin, bool& trouver, bool exterieurSG) {
    visiter.insert(courrant);
    chemin.push_back(courrant);

    for (const auto& voisin : graphe.at(courrant)) {
        T neighbor = std::get<0>(voisin);
        bool voisinDansSG = SG.graphe.count(neighbor) > 0;
        bool liaisonExterieur = this->arc(courrant, neighbor);
        
        if(!voisinDansSG) {
            exterieurSG = true;
        }

        if (!exterieurSG && voisinDansSG) {
            continue;
        }
        bool arcExists = this->arc(courrant, neighbor);

        if (voisinDansSG && exterieurSG && liaisonExterieur) {
            chemin.push_back(neighbor);
            trouver = true;
            return;
        }

        if (visiter.count(neighbor) == 0 && !trouver) {
            rechercheProfondeurSG(neighbor, visiter, SG, chemin, trouver, !voisinDansSG);
            if (trouver) {
                return;
            }
        }
        if (!voisinDansSG) {
            exterieurSG = false;
        }
    }
    chemin.pop_back();
}

#endif

