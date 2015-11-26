#include <iostream>
#include <ctime>
#include <fstream>

#include "data.h"
#include "Bierwirth.h"
#include "Population.h"

int main(int, char **)
{
	clock_t	chronometer=clock();				//Chronometre
	std::ofstream file_time("time.csv");
	std::ofstream file_makespan("makspan.csv");
	std::ofstream file_popgen("popgen.csv");
	int taille_pop = 100;

	if (!file_time || !file_makespan || !file_popgen) {
		std::cout << "fichiers non initialises" << std::endl;
	}
	
	std::vector<Data> data_tab;

	data_tab.push_back(Data("INSTANCES/la01.dat"));
	data_tab.push_back(Data("INSTANCES/la02.dat"));
	data_tab.push_back(Data("INSTANCES/la03.dat"));
	data_tab.push_back(Data("INSTANCES/la04.dat"));
	data_tab.push_back(Data("INSTANCES/la05.dat"));
	data_tab.push_back(Data("INSTANCES/la06.dat"));
	data_tab.push_back(Data("INSTANCES/la07.dat"));
	data_tab.push_back(Data("INSTANCES/la08.dat"));
	data_tab.push_back(Data("INSTANCES/la09.dat"));
	data_tab.push_back(Data("INSTANCES/la10.dat"));
	data_tab.push_back(Data("INSTANCES/la11.dat"));
	data_tab.push_back(Data("INSTANCES/la12.dat"));
	data_tab.push_back(Data("INSTANCES/la13.dat"));
	data_tab.push_back(Data("INSTANCES/la14.dat"));
	data_tab.push_back(Data("INSTANCES/la15.dat"));
	data_tab.push_back(Data("INSTANCES/la16.dat"));
	data_tab.push_back(Data("INSTANCES/la17.dat"));
	data_tab.push_back(Data("INSTANCES/la18.dat"));
	data_tab.push_back(Data("INSTANCES/la19.dat"));
	data_tab.push_back(Data("INSTANCES/la20.dat"));

	// Calcul des RL et des 5eme generation de chaque donnee 
	int cpt = 0;
	for (std::vector<Data>::iterator it = data_tab.begin(); it != data_tab.end();it++) {
		file_time << "Data " << cpt << ";";
		file_makespan << "Data " << cpt << std::endl;
		std::cout << "Data " << cpt << std::endl;

		Bierwirth b(*it);
		b.evaluer();
		b.recherche_locale(file_makespan);

		Population P(taille_pop, (*it));
		file_makespan << "Premiere iteration de l'algo genetique : " << std::endl;
		P.algo_genetique(file_makespan);std::cout << ".";
		P.algo_genetique();std::cout << ".";
		P.algo_genetique();std::cout << ".";
		P.algo_genetique();std::cout << ".";
		file_makespan << "Cinquieme iteration de l'algo genetique : " << std::endl;
		P.algo_genetique(file_makespan);std::cout << ".";

		file_time << (float)(clock() - chronometer) / CLOCKS_PER_SEC << std::endl;
		file_makespan << std::endl;
		std::cout << std::endl;

		cpt++;
	}

	//Calcul d'une 100eme generation de la premiere donnee
	Population P(taille_pop, (data_tab[0]));
	for (int i = 0;i < 100;i++) {
		std::cout << i << "%" << std::endl;
		file_popgen << i << ";" << P.get_makespan() << std::endl;
		P.algo_genetique();
	}

	std::cout << "Temps de l'execution : " << (float)(clock() - chronometer) / CLOCKS_PER_SEC << std::endl;

	file_makespan.close();
	file_time.close();
	file_popgen.close();

	return 0;
}

//main d'avant :

/*------------------------------------------------------*/
/* Pour test selon "autre façon"                        */
/*	std::vector<unsigned> v(50);
v = { 2,1,9,9,0,7,6,1,9,5,8,6,2,0,3,3,6,1,8,7,8,7,
2,4,0,7,6,1,5,4,2,1,2,5,0,9,5,3,3,6,8,7,4,3,4
,5,8,9,0,4 };
Bierwirth b(d, v);									*/
/*------------------------------------------------------*/

/*Bierwirth b(d1);
//d.display_all(std::cout);

b.afficher_bierwirth();
b.evaluer();
b.afficher_sequences();
b.afficher_chemin_critique();

b.recherche_locale(file_makespan);

b.afficher_chemin_critique();

Population P(100, d1);
std::cout << "Population initiale, 20 premiers membres :" << std::endl;
P.afficher_makespan(20);
P.algo_genetique(file_makespan);
std::cout << "Nouvelle population 1, 20 premiers membres :" << std::endl;
P.afficher_makespan(20);

P.algo_genetique();std::cout << ".";
P.algo_genetique();std::cout << ".";
P.algo_genetique();std::cout << ".";
P.algo_genetique();std::cout << ".";
std::cout << "Nouvelle population 5, 20 premiers membres :" << std::endl;
P.afficher_makespan(20);

std::cout << "Notre meilleur Bierwirth !" << std::endl;
P.afficher_bierwirth(1);*/