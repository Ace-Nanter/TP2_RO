#include "Population.h"
#include "Bierwirth.h"
#include <iostream>
#include <algorithm>


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

void Population::algo_genetique() {

}

bool sorting_function(Bierwirth i, Bierwirth j) { return (i.get_makespan_()<j.get_makespan_()); }



