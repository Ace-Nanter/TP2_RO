#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stack>

#include "data.h"



/*--------------------------------*/
/* Contient les op�rations par    */
/* machines                       */
/*--------------------------------*/
struct liste_machines {
	std::vector<Job *>	jobs;			// Pi�ces qui passent par la machine
	Job*				last_op;		// Derni�re op�ration sur la machine
	unsigned			duree;			// Date de l'op�ration

	liste_machines() :last_op(nullptr), duree(0) { }
	void afficher_sequence();	// Affiche les op�rations de chaque machine
	void afficher_sequence_reverse();

};

struct liste_items{
	std::vector<Job *> machines;	// Machine par lesquelles la pi�ce est pass�e
	Job* last_op;					// Derni�re op�ration sur la pi�ce
	unsigned duree;					// Date � laquelle la pi�ce est appel�e

	liste_items() :last_op(nullptr), duree(0) { }
};

class Bierwirth {
private:
	Data& d_;
	std::vector<Job *> bierwirth_vector_;			// Vecteur de bierwith
	std::vector<liste_items> tabItem_;				// Ordre des machines pour une pi�ce
	std::vector<liste_machines> tabOpe_;			// Ordre des pi�ces par machine

	unsigned	makespan_;							//Makespan et last operation local au vecteur courant de Bierwirth
	Job*		last_cp_;

public:
	Bierwirth(Data&);
	Bierwirth::Bierwirth(Data &d, std::vector<unsigned> v);
	Bierwirth(const Bierwirth& b);
	
	const int get_makespan_();
	void evaluer(std::vector<Job*>& b_new);
	void evaluer();
	void display();
	void afficher_sequences();
	void afficher_chemin_critique();
	void recherche_locale();
	void shuffle();

	Bierwirth &Bierwirth::operator=(const Bierwirth&);

	class ExceptionIncorrectSize : public std::exception { };
	
	friend class Population;
};