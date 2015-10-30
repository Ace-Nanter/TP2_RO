#include "Bierwith.h"

Bierwith::Bierwith(Data d) : d_(d),
								v_(d.nbJobs_ * d.nbMachines_),
								tabJob_(d.nbJobs_, numjob()),
								tabOpe_(d.nbMachines_,  liste_machines()),
								tabJobOpe_(d.nbJobs_,std::vector<element>(d.nbMachines_, element()))
{
	unsigned i;										// Variable de boucle

	// Initialisation du vecteur de Bierwith
	for (i = 0; i < d.jobs_.size(); i++) {
		for (unsigned j = 0; j < d.jobs_[i].size(); j++) {
			v_[j * d.jobs_.size() + i] = &(d_.jobs_.at(i).at(j));
		}
	}
	std::random_shuffle(v_.begin(), v_.end());
}

void Bierwith::display() {
	
	for (unsigned i = 0; i < v_.size(); i++)
		std::cout << v_[i]->item_ << " ; ";

	std::cout << std::endl;
}

void Bierwith::evaluer() {
	// Variables temporaires
	unsigned item_tmp;
	unsigned machine_tmp;
	unsigned duration_tmp;
	element* elt_tmp;//elt_tmp est l'elt courant de tabJobOpe
	element * prev_op = NULL;
	liste_machines lm_tmp;//lm est la case courante de tabOpe


	for (unsigned i = 0; i < v_.size(); i++) {
		// Mise en place des variables temporaires
		item_tmp = v_[i]->item_;							// Récupération du numéro du job
		machine_tmp = v_[i]->machine_;						// Récupération du numéro machine
		duration_tmp = v_[i]->duration_;

		
		elt_tmp=&(tabJobOpe_[item_tmp][tabJob_[item_tmp].inc]);
		lm_tmp = tabOpe_[v_[i]->machine_];

		//Init d'element courant
		elt_tmp->machine_ = machine_tmp;
		elt_tmp->job_ = item_tmp;
		elt_tmp->prev_op_ = tabOpe_[machine_tmp].last_op;	//On fait pointer sur la derniere op traite
		elt_tmp->date_dep = tabOpe_[machine_tmp].duree;		//la date de depart est egale a la duree totale courante

		tabOpe_[machine_tmp].last_op = elt_tmp;				//elt_tmp devient la derniere op, on fait pointer tabOpe dessus
		tabOpe_[machine_tmp].duree += duration_tmp;			//on incremente la duree totale

		tabJob_[item_tmp].inc++;							// Incrémentation de l'appel du job
		tabJob_[item_tmp].duree += duration_tmp;			// Ecriture de la duree totale

	}
}

void liste_machines::afficher_sequence() {
	element * tmp = last_op;
	std::cout << tmp->job_;
	tmp = tmp->prev_op_;
	while (tmp != NULL) {
		std::cout << " <- " << tmp->job_ ;
		tmp = tmp->prev_op_;
	}
	std::cout << std::endl;
}

void Bierwith::afficher_sequences() {
	for (unsigned i = 0; i < tabOpe_.size(); i++) {
		std::cout << "Chemin critique de la machine num. " << i << std::endl;
		tabOpe_[i].afficher_sequence();
	}
}