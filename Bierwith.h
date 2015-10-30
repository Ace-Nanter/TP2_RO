#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "data.h"


struct element {
	unsigned date_dep;							// Date de départ
	unsigned machine_;								// Machine sur laquelle a lieu le job
	unsigned job_;

	element* prev_op_;							// Opération précédente
	element* next_op_;
	element* father;

	element::element() : date_dep(0), machine_(0), job_(0), prev_op_(nullptr) { }
};

struct liste_machines {
	element* last_op;
	unsigned duree;				// Date de l'opération

	liste_machines() :last_op(nullptr), duree(0) { }
	void afficher_sequence();
	void afficher_chemin_critique();
};

struct numjob{
	unsigned inc;				// Nombre de fois où le job est appelé
	unsigned duree;				// Date à laquelle le job est appelée

	numjob::numjob() :inc(0), duree(0) { }
};

class Bierwirth {
private:
	Data d_;
	std::vector<Job *> v_;								// Vect de bierwith
	std::vector<numjob> tabJob_;
	std::vector< std::vector<element> > tabJobOpe_;		//x=ope, y=Job
	std::vector<liste_machines> tabOpe_;
	
public:
	Bierwirth(Data d);
	void evaluer();
	void display();
	void afficher_sequences();
	void afficher_chemins_critiques();
};