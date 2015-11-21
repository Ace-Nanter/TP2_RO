#pragma once
#include <iostream>
#include "Bierwirth.h"
#include "data.h"

class Population
{
private:
	std::vector< Bierwirth > P_;
	unsigned taille_;
	Data& d_;
public:
	Population(unsigned,Data&);
	~Population();

	void algo_genetique();
	void fusion(const std::vector< Bierwirth > &);	//fusionne 2 Pop
	void afficher_makespan(unsigned n);				//affiche les n meilleurs makespans
	void afficher_makespan();						//affiche les makespans
	void afficher_bierwirth(unsigned n);				//affiche les bierwirths
	void afficher_bierwirth();						//affiche les n meilleurs 
};

bool sorting_function_bierwirth(Bierwirth i, Bierwirth j);
bool unique_function_bierwirth(Bierwirth i, Bierwirth j);
void b_union(std::vector< Job* > &, std::vector< Job* > &);


