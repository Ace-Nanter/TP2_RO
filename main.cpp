#include <iostream>
#include "data.h"
#include "Bierwith.h"

int main(int, char **)
{
	
	Data d("INSTANCES/la01.dat");


	Bierwirth b(d);

	//d.display_all(std::cout);
	
	//b.display();
	b.evaluer();
	b.afficher_sequences();
	b.afficher_chemins_critiques();

	return 0;
}