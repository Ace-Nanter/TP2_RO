#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>

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
	void afficher_sequence();			// Affiche les opérations de chaque machine
	void afficher_sequence_reverse();

};

/*--------------------------------*/
/* Contient les opérations par    */
/* pièces	                      */
/*--------------------------------*/
struct liste_items {
	std::vector<Job *> machines;	// Machine par lesquelles la pièce est passée
	Job* last_op;					// Dernière opération sur la pièce
	unsigned duree;					// Date à laquelle la pièce est appelée

	liste_items() :last_op(nullptr), duree(0) { }
};

class Bierwirth {
private:
	Data& d_;										// Référence vers les données utilisées
	std::vector<Job *> bierwirth_vector_;			// Vecteur de bierwith
	std::vector<liste_items> tabItem_;				// Ordre des machines pour une pièce
	std::vector<liste_machines> tabOpe_;			// Ordre des pièces par machine

	unsigned	makespan_;							// Makespan et last operation local au vecteur courant de Bierwirth
	Job*		last_cp_;

	void shuffle();									// Mélange aléatoirement le vecteur de Bierwirth

public:
	Bierwirth(Data&);								// Par défaut, il faut donner une référence vers data
	Bierwirth::Bierwirth(Data &d, std::vector<unsigned> v);
	Bierwirth(const Bierwirth& b);					// Constructeur par copie
	
	const int get_makespan_();						// getter pour le makespan
	void evaluer(std::vector<Job*>& b_new);			// Lance l'algorithme evaluer sur un vecteur donné
	void evaluer();									// Lance l'algorithme evaluer sur le vecteur local
	
	void afficher_sequences();						// Affiche les séquences pour chaque machine
	void afficher_chemin_critique();				// Affiche le chemin critique
	void afficher_bierwirth();						// Affiche le vecteur de Bierwirth
	void recherche_locale();						// Lance l'algorithme de recherche locale
	void recherche_locale(std::ofstream& f);

	Bierwirth &Bierwirth::operator=(const Bierwirth&);

	class ExceptionIncorrectSize : public std::exception { };
	
	friend class Population;
};