#include <iostream>
#include "data.h"
#include "Bierwirth.h"

Bierwirth recherche_locale(Bierwirth& b0);

Bierwirth recherche_locale(Bierwirth& b0) {
	bool changer,stop = false;
	Bierwirth b_new(b0);
	do
	{
		b0.amelioration(b_new);
		if (changer) {
			b0 = b_new;
		}
		else {
			stop = true;
		}
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

	return 0;
}