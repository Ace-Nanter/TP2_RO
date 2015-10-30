#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "data.h"


struct element {
	unsigned date_dep;							// Date de départ
	int machine_;								// Machine sur laquelle a lieu le job
	int job_;
	element* prev_op_;							// Opération précédente

	element::element() : date_dep(0), machine_(0), job_(0), prev_op_(nullptr) { }
};

struct liste_machines {
	element* last_op;
	unsigned duree;				// Date de l'opération

	liste_machines() :last_op(nullptr), duree(0) { }
	void afficher_sequence();
};

struct numjob{
	unsigned inc;				// Nombre de fois où le job est appelé
	unsigned duree;				// Date à laquelle le job est appelé

	numjob::numjob() :inc(0), duree(0) { }
};

class Bierwith {
private:
	Data d_;
	std::vector<Job *> v_;		// Vect de bierwith
	std::vector<numjob> tabJob_;
	std::vector< std::vector<element> > tabJobOpe_;
	std::vector<liste_machines> tabOpe_;
	
public:
	Bierwith::Bierwith(Data d);
	void evaluer();
	void display();
	void afficher_sequences();
};