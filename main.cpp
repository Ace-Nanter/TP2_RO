#include <iostream>
#include "data.h"
#include "Bierwirth.h"

Bierwirth recherche_locale(Bierwirth& b0);
bool amelioration(Bierwirth& b2);

Bierwirth recherche_locale(Bierwirth& b0) {
	bool changer,stop = false;
	Bierwirth b2(b0);
	do
	{
		changer=amelioration(b2);
		if (changer) {
			b0 = b2;
		}
		else {
			stop = true;
		}
	} while (!stop);
}

void amelioration(Bierwirth& b2) {


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