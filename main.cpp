#include <iostream>
#include "data.h"
#include "Bierwirth.h"

void recherche_locale(Bierwirth& b0);

void recherche_locale(Bierwirth& b0) {
	bool stop = false;
	Bierwirth b_new(b0);
	do
	{
		stop=!b0.amelioration(b_new);
	} while (!stop);
}

int main(int, char **)
{
	
	Data d("INSTANCES/la01.dat");


	Bierwirth b(d);

	//d.display_all(std::cout);
	
	//b.display();
	b.evaluer();
	b.afficher_sequences();
	b.afficher_chemin_critique();

	recherche_locale(b);

	b.afficher_chemin_critique();

	return 0;
}