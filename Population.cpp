#include "Population.h"
#include "Bierwirth.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

Population::Population(unsigned taille,Data& d):taille_(taille),d_(d)
{
	Bierwirth b_tmp(d);			//Bierwirth de base
	//On creer une population a partir de d
	for (unsigned i = 0;i < taille_;i++) {
		b_tmp.shuffle();				//Creation d'un individu
		b_tmp.evaluer();				//Mise a jour des donnees
		b_tmp.recherche_locale();		//RL
		P_.push_back(Bierwirth(b_tmp));	//ajout de l'individu
	}
	std::sort (P_.begin(), P_.end(), sorting_function_bierwirth);	//On trie la population obtenue en fonction du makespan
}


Population::Population::~Population(){}

//On divise les individu en 2 genes (coupe a la moitier)
//On va proceder par une selection par rang 
//le premier des genes retenus se trouve dans les 20% meilleurs resultats
//Le 2 eme est pris uniformement sur les parents
//seed du mersen twistter "bierwirth"
void Population::algo_genetique() {
	//Initialisation du mersenne twistter
	std::string seed_str("bierwirth");
	std::seed_seq seed (seed_str.begin(),seed_str.end());

	unsigned delimiteur = (unsigned)(P_[0].bierwirth_vector_.size() / 2);	//delimiteur de la partie Pere/Mere des parents (ici a la moiter)
	std::vector<unsigned> gene(2);											//numeros des individus à melanger dans l'enfant
	unsigned elite = (unsigned)((float)taille_*0.2);						//delimiteur des meilleurs individus, ici 20%

	std::vector< Bierwirth > P_enf;				// Population d'enfant
	Bierwirth b_temp(d_);						// Bierwirth temporaire, pour creer les enfants
	std::mt19937 mt (seed);						// Mersenne twistter

	//Creation d'une population d'enfant
	for (unsigned i = 0;i < taille_;i++) {
		//Choix parmis les parents des genes a melanger :
		gene[0] = mt() % elite;
		gene[1] = mt() % taille_;

		//Creation de l'enfant par mutation
		b_temp.bierwirth_vector_.clear();
		b_temp.bierwirth_vector_.insert(b_temp.bierwirth_vector_.begin(),
			P_[gene[0]].bierwirth_vector_.begin(), 
			P_[gene[0]].bierwirth_vector_.begin() + delimiteur);			//On copie la premiere moitier du premier gene
		b_union(b_temp.bierwirth_vector_, P_[gene[1]].bierwirth_vector_);	//On fait une union avec le deuxieme gene
		b_temp.evaluer();													//Evaluation du chemin critique

		//affichage pour comparaison
		/*for (unsigned i = 0;i < b_temp.bierwirth_vector_.size();i++) {
			if (i == delimiteur) { std::cout << "-------------------------------" << std::endl; }
			std::cout << P_[gene[0]].bierwirth_vector_[i]->item_ << ";" << P_[gene[0]].bierwirth_vector_[i]->machine_ << "\t";
			std::cout << P_[gene[1]].bierwirth_vector_[i]->item_ << ";" << P_[gene[1]].bierwirth_vector_[i]->machine_ << "\t";
			std::cout << b_temp.bierwirth_vector_[i]->item_ << ";" << b_temp.bierwirth_vector_[i]->machine_ << std::endl;
		}*/

		b_temp.recherche_locale();			//Recherche Locale
		P_enf.push_back(Bierwirth(b_temp));	//On ajoute le nouvel individu a la population enfant
	}
	std::sort(P_enf.begin(), P_enf.end(), sorting_function_bierwirth);	//trie de la population enfant
	fusion(P_enf);														//On fait une union de P_enf et on obtient la nouvelle population
}

void Population::fusion(const std::vector<Bierwirth>& P_enf)
{
	P_.insert(P_.end(),P_enf.begin(),P_enf.end());					//On rajoute les enfants
	std::sort(P_.begin(), P_.end(), sorting_function_bierwirth);	//On trie
	std::unique(P_.begin(), P_.end(),unique_function_bierwirth);	//On supprime les occurences multiples (peut engendrer des pertes 
																	//sur les resultats obtenus puisqu'on reduit ainsi le nombre d'individus 
																	//avec de bons makespan )
	P_.resize(taille_, P_enf[0]);									//On recoupe pour avoir une population de la bonne taille
}

void Population::afficher_makespan(unsigned n)
{
	for (unsigned i = 0;i < n && i < taille_;i++) {
		std::cout << "n" << i << " " << P_[i].get_makespan_() << std::endl;
	}
}

//affiche les makespans de tous les individus
void Population::afficher_makespan()
{
	afficher_makespan(taille_);
}

void Population::afficher_bierwirth(unsigned n)
{
	for (unsigned i=0; i < n; i++) {
		P_[i].afficher_bierwirth();
	}
}

void Population::afficher_bierwirth()
{
	afficher_bierwirth(taille_);
}


bool sorting_function_bierwirth(Bierwirth i, Bierwirth j) { return (i.get_makespan_()<j.get_makespan_()); }
bool unique_function_bierwirth(Bierwirth i, Bierwirth j) { return (i.get_makespan_()==j.get_makespan_()); }


void b_union(std::vector< Job* > & enfant, std::vector< Job* > & mere) {
	unsigned i,j,taille=(unsigned)enfant.size();					//on sauvegarde la taille de l'enfant initiale, car on ne parcourera pas plus
	bool stop;
	for (i = 0;i<mere.size();i++) {									//Parcours du vecteur mere
		stop = false;
		for (j = 0;((j < taille) && (mere[i] != enfant[j]));j++);	//Parcour du vecteur enfant
		if (j==taille) enfant.push_back(mere[i]);					//Si on a parcourue tout le vecteur mere alors cela veut dire
																	//que la piece n'existe pas donc on la rajoute
	}
}


