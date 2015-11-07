#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "data.h"



/*--------------------------------*/
/* Liste les opérations d'une     */
/* machine                        */
/*--------------------------------*/
struct liste_machines {
	Job* last_op;
	unsigned duree;				// Date de l'opération

	liste_machines() :last_op(nullptr), duree(0) { }
	void afficher_sequence();
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
	std::vector< std::vector<Job> > tabJobOpe_;		//x=ope, y=Job
	std::vector<liste_machines> tabOpe_;

public:
	Bierwirth(Data d);
	Bierwirth(const Bierwirth& b);
	void evaluer();
	void display();
	void afficher_sequences();
	void afficher_chemin_critique();
	bool amelioration(Bierwirth& b2);
};