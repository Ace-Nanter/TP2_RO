#include "Population.h"
#include "Bierwirth.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

Population::Population(unsigned taille,Data& d):taille_(taille),d_(d)
{
	Bierwirth b_tmp(d);
	for (unsigned i = 0;i < taille_;i++) {
		b_tmp.shuffle();
		b_tmp.evaluer();
		P_.push_back(Bierwirth(b_tmp));
	//	std::cout << "individu n" << i << " : makespan:" << P_[i].get_makespan_() << "\t;";
		P_[i].recherche_locale();
	//	std::cout << "RL:" << P_[i].get_makespan_() << std::endl;
	}
	std::sort (P_.begin(), P_.end(), sorting_function);
	std::cout << "Population initiale :" << std::endl;
	for (unsigned i = 0;i < taille_;i++) {
		std::cout << "n" << i << " " << P_[i].get_makespan_() << std::endl;
	}
}


Population::Population::~Population()
{

}

//On divise les individu en 3 gene
//On va proceder par une selection par rang (speciale)
//2 des genes retenu se trouve dans les 20% meilleurs resultats
//Le 3 eme est pris uniformement sur les parents
//seed du mersen twistter "bierwirth"
void Population::algo_genetique() {
	std::string seed_str("bierwirth");
	std::seed_seq seed (seed_str.begin(),seed_str.end());
	unsigned delimiteur1 = (unsigned)((float)(P_[0].bierwirth_vector_.size()) / 3);
	unsigned delimiteur2 = 2 * delimiteur1;
	std::vector<unsigned> gene(3);						//numeros du bierwirth des 3 genes a melanger dans l'enfant
	unsigned elite = (unsigned)((float)taille_*0.2);	//delimiteur des meilleurs individus, ici 20%

//	unsigned modulo = ((taille_ - 1)*taille_) / 2;//valeur du modulo sur le mersenne twistter pour faire la selection par rang
	std::vector< Bierwirth > P_enf;						// Population d'enfant
	Bierwirth b_temp(d_);								//Bierwirth temporaire, pour creer les enfants
	std::mt19937 mt (seed);

	//Creation d'une population d'enfant
	for (unsigned i = 0;i < taille_;i++) {
		//Choix parmis les parents des genes a melanger :
		gene[0] = mt() % elite;
		gene[1] = mt() % elite;
		gene[2] = mt() % taille_;
		/*for (unsigned j = 0;j < taille_;j++) {
			if (x < tmp) {
				gene1 = j;
			}
			tmp += j;
		}*/

		/************************************************************************/
		/** Cette mutation engendre des problemes parce qu'on se retrouve avec **/
		/** des vecteurs de Bierwirth à plusieurs occurences d'un même Job,    **/
		/** ce qui entraine des boucles infinies                               **/
		/** Il faut trouver un autre systeme de mutation                       **/
		/************************************************************************/

		//Creation de l'enfant par mutation
		std::copy(P_[gene[0]].bierwirth_vector_.begin(), P_[gene[0]].bierwirth_vector_.begin() + delimiteur1,b_temp.bierwirth_vector_.begin());
		std::copy(P_[gene[1]].bierwirth_vector_.begin() + delimiteur1, P_[gene[1]].bierwirth_vector_.begin() + delimiteur2, b_temp.bierwirth_vector_.begin()+delimiteur1);
		std::copy(P_[gene[2]].bierwirth_vector_.begin() + delimiteur2, P_[gene[2]].bierwirth_vector_.end(), b_temp.bierwirth_vector_.begin()+delimiteur2);
		b_temp.evaluer();					//Evaluation du chemin critique
		b_temp.recherche_locale();			//Recherche Locale
		P_enf.push_back(Bierwirth(b_temp));
		std::cout << "makespan enfant n" << i << ": " << P_enf[i].makespan_ << " " << b_temp.makespan_ << std::endl;
	}
	std::sort(P_enf.begin(), P_enf.end(), sorting_function);
	fusion(P_enf);//On fait une union de P_enf et on obtient la nouvelle population
}

void Population::fusion(const std::vector<Bierwirth>& P_enf)
{
	std::set_union(P_.begin(), P_.end(), P_enf.begin(), P_enf.end(), P_.begin(),sorting_function);//J'espere que set_union ne depasse pas P_ jusqua la seg fault mais pas sur
}

bool sorting_function(Bierwirth i, Bierwirth j) { return (i.get_makespan_()<j.get_makespan_()); }



