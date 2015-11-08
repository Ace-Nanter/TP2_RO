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
};

bool sorting_function(Bierwirth i, Bierwirth j);

