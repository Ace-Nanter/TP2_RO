#include "Bierwith.h"

Bierwirth::Bierwirth(Data d) : d_(d),
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

void Bierwirth::display() {
	
	for (unsigned i = 0; i < v_.size(); i++)
		std::cout << v_[i]->item_ << " ; ";

	std::cout << std::endl;
}

void Bierwirth::evaluer() {
	// Variables temporaires
	unsigned item_tmp;
	unsigned machine_tmp;
	unsigned duration_tmp;
	int bool_tmp;

	element* elt_tmp;//elt_tmp est l'elt courant de tabJobOpe
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

		//On fait pointer le pointeur next sur l'element suivant(si l'element tmp existe, ce qui n'est pas le cas a la premiere iteration)
		if(tabOpe_[machine_tmp].last_op!=nullptr) tabOpe_[machine_tmp].last_op->next_op_=elt_tmp;
		elt_tmp->prev_op_ = tabOpe_[machine_tmp].last_op;	//On fait pointer sur la derniere op traite
		elt_tmp->date_dep = tabOpe_[machine_tmp].duree;		//la date de depart est egale a la duree totale courante

		tabOpe_[machine_tmp].last_op = elt_tmp;				//elt_tmp devient la derniere op, on fait pointer tabOpe dessus
		tabOpe_[machine_tmp].duree += duration_tmp;			//on incremente la duree totale

		tabJob_[item_tmp].inc++;							// Incrémentation de l'appel du job
		tabJob_[item_tmp].duree += duration_tmp;			// Ecriture de la duree totale

		if (tabJob_[elt_tmp->job_].duree < tabOpe_[elt_tmp->machine_].duree) {
			elt_tmp->father = elt_tmp->prev_op_;
		}
		else {
			bool_tmp = tabJob_[elt_tmp->job_].inc - 2;
			if (bool_tmp >= 0) {
				elt_tmp->father = &tabJobOpe_[elt_tmp->job_][tabJob_[elt_tmp->job_].inc - 2];
			}
			else {
				elt_tmp->father = nullptr;
			}
		}

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

void liste_machines::afficher_chemin_critique() {
	element * tmp = last_op;
	std::cout << tmp->job_;
	tmp = tmp->father;
	while (tmp != NULL) {
		std::cout << " <- " << tmp->job_;
		tmp = tmp->father;
	}
	std::cout << std::endl;
}


void Bierwirth::afficher_sequences() {
	for (unsigned i = 0; i < tabOpe_.size(); i++) {
		std::cout << "Sequence de la machine num. " << i << std::endl;
		tabOpe_[i].afficher_sequence();
	}
}

void Bierwirth::afficher_chemins_critiques() {
	for (unsigned i = 0; i < tabOpe_.size(); i++) {
		std::cout << "Chemin critique de la machine num. " << i << std::endl;
		tabOpe_[i].afficher_chemin_critique();
	}
}