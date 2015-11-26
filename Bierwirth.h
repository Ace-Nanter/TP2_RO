#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stack>
#include <fstream>

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
	void afficher_sequence();			// Affiche les op�rations de chaque machine
	void afficher_sequence_reverse();

};

/*--------------------------------*/
/* Contient les op�rations par    */
/* pi�ces	                      */
/*--------------------------------*/
struct liste_items {
	std::vector<Job *> machines;	// Machine par lesquelles la pi�ce est pass�e
	Job* last_op;					// Derni�re op�ration sur la pi�ce
	unsigned duree;					// Date � laquelle la pi�ce est appel�e

	liste_items() :last_op(nullptr), duree(0) { }
};

class Bierwirth {
private:
	Data& d_;										// R�f�rence vers les donn�es utilis�es
	std::vector<Job *> bierwirth_vector_;			// Vecteur de bierwith
	std::vector<liste_items> tabItem_;				// Ordre des machines pour une pi�ce
	std::vector<liste_machines> tabOpe_;			// Ordre des pi�ces par machine

	unsigned	makespan_;							// Makespan et last operation local au vecteur courant de Bierwirth
	Job*		last_cp_;

	void shuffle();									// M�lange al�atoirement le vecteur de Bierwirth

public:
	Bierwirth(Data&);								// Par d�faut, il faut donner une r�f�rence vers data
	Bierwirth::Bierwirth(Data &d, std::vector<unsigned> v);
	Bierwirth(const Bierwirth& b);					// Constructeur par copie
	
	const int get_makespan_();						// getter pour le makespan
	void evaluer(std::vector<Job*>& b_new);			// Lance l'algorithme evaluer sur un vecteur donn�
	void evaluer();									// Lance l'algorithme evaluer sur le vecteur local
	
	void afficher_sequences();						// Affiche les s�quences pour chaque machine
	void afficher_chemin_critique();				// Affiche le chemin critique
	void afficher_bierwirth();						// Affiche le vecteur de Bierwirth
	void recherche_locale();						// Lance l'algorithme de recherche locale
	void recherche_locale(std::ofstream& f);

	Bierwirth &Bierwirth::operator=(const Bierwirth&);

	class ExceptionIncorrectSize : public std::exception { };
	
	friend class Population;
};