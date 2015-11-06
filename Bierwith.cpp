#include "Bierwirth.h"

Bierwirth::Bierwirth(Data d) : d_(d),
								v_(d.nbJobs_ * d.nbMachines_),
								tabJob_(d.nbJobs_, numjob()),
								tabOpe_(d.nbMachines_,  liste_machines()),
								tabJobOpe_(d.nbJobs_,std::vector<Job>(d.nbMachines_, Job()))
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

Bierwirth::Bierwirth(const Bierwirth& b) {
	d_=b.d_;
	v_ = b.v_;
	tabJob_=b.tabJob_;
	tabJobOpe_=b.tabJobOpe_;
	tabOpe_=b.tabOpe_;
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

	Job* elt_tmp;//elt_tmp est l'elt courant de tabJobOpe
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
		elt_tmp->item_ = item_tmp;

		// On fait pointer le pointeur next sur l'element suivant(si l'element tmp existe, ce qui n'est pas le cas a la premiere iteration)
		if(tabOpe_[machine_tmp].last_op != nullptr)
			tabOpe_[machine_tmp].last_op->next_=elt_tmp;	// On lie la dernière de la machine donnée
		elt_tmp->prev_ = tabOpe_[machine_tmp].last_op;	// On fait pointer sur la derniere op traite
		elt_tmp->starting_ = tabOpe_[machine_tmp].duree;		// La date de depart est egale a la duree totale courante

		tabOpe_[machine_tmp].last_op = elt_tmp;				//elt_tmp devient la derniere op, on fait pointer tabOpe dessus
		tabOpe_[machine_tmp].duree += duration_tmp;			//on incremente la duree totale

		tabJob_[item_tmp].inc++;							// Incrémentation de l'appel du job
		tabJob_[item_tmp].duree += duration_tmp;			// Ecriture de la duree totale

		//On compare la duree du job et de la machine lie a cet element
		if (tabJob_[elt_tmp->item_].duree < tabOpe_[elt_tmp->machine_].duree) {
			elt_tmp->father_ = elt_tmp->prev_;//si la duree de la machine est la plus grande le father est egale a l'ele prec de l'element
		}
		else {//si la duree du job est le plus grand le father correspond à la case precedente du job dans le tabJobOpe
			bool_tmp = tabJob_[elt_tmp->item_].inc - 2;//bug si on fait le calcul dans le if ...
			if (bool_tmp >= 0) {//On evite une seg fault
				elt_tmp->father_ = &tabJobOpe_[elt_tmp->item_][tabJob_[elt_tmp->item_].inc - 2];
			}
			else {
				elt_tmp->father_ = nullptr;
			}
		}

		if (d_.makespan_ < tabJob_[item_tmp].duree)
		{
			d_.makespan_ = tabJob_[item_tmp].duree;
			d_.last_cp_ = elt_tmp;
		}
	}
}

void liste_machines::afficher_sequence() {
	Job * tmp = last_op;
	std::cout << tmp->item_;
	tmp = tmp->prev_;
	while (tmp != NULL) {
		std::cout << " <- " << tmp->item_ ;
		tmp = tmp->prev_;
	}
	std::cout << std::endl;
}

void Bierwirth::afficher_chemin_critique() {
	Job * tmp = d_.last_cp_;
	std::cout << tmp->item_;
	tmp = tmp->father_;
	while (tmp != NULL) {
		std::cout << " <- " << tmp->item_;
		tmp = tmp->father_;
	}
	std::cout << std::endl;
}


void Bierwirth::afficher_sequences() {
	for (unsigned i = 0; i < tabOpe_.size(); i++) {
		std::cout << "Sequence de la machine num. " << i << std::endl;
		tabOpe_[i].afficher_sequence();
	}
}