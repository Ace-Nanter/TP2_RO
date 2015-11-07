#include <iostream>
#include "data.h"
#include "Bierwirth.h"

/*
void recherche_locale(Bierwirth& b0);

void recherche_locale(Bierwirth& b0) {
	bool stop = false;
	Bierwirth b_new(b0);
	do
	{
		stop=!b0.amelioration(b_new);
	} while (!stop);
}*/

int main(int, char **)
{
	
	Data d("INSTANCES/la01.dat");

/*------------------------------------------------------*/
/* Pour test selon "autre façon"                        */
/*	std::vector<unsigned> v(50);						*/
/*	v = { 2,1,9,9,0,7,6,1,9,5,8,6,2,0,3,3,6,1,8,7,8,7,	*/
/*		2,4,0,7,6,1,5,4,2,1,2,5,0,9,5,3,3,6,8,7,4,3,4	*/
/*		,5,8,9,0,4 };									*/
/*	Bierwirth b(d, v);									*/
/*------------------------------------------------------*/

	Bierwirth b(d);
	//d.display_all(std::cout);

	b.display();
	b.evaluer();
	b.afficher_sequences();
	b.afficher_chemin_critique();

	//recherche_locale(b);

	return 0;
}