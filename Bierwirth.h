#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stack>

#include "data.h"



/*--------------------------------*/
/* Contient les opérations par    */
/* machines                       */
/*--------------------------------*/
struct liste_machines {
	std::vector<Job *>	jobs;			// Pièces qui passent par la machine
	Job*				last_op;		// Dernière opération sur la machine
	unsigned			duree;			// Date de l'opération

	liste_machines() :last_op(nullptr), duree(0) { }
	void afficher_sequence();	// Affiche les opérations de chaque machine
	void afficher_sequence_reverse();

};

struct liste_items{
	std::vector<Job *> machines;	// Machine par lesquelles la pièce est passée
	Job* last_op;					// Dernière opération sur la pièce
	unsigned duree;					// Date à laquelle la pièce est appelée

	liste_items() :last_op(nullptr), duree(0) { }
};

class Bierwirth {
private:
	Data& d_;
	std::vector<Job *> bierwirth_vector_;			// Vecteur de bierwith
	std::vector<liste_items> tabItem_;				// Ordre des machines pour une pièce
	std::vector<liste_machines> tabOpe_;			// Ordre des pièces par machine

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