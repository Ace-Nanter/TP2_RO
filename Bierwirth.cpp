#include "Bierwirth.h"
#include <iostream>
#include <exception>

Bierwirth::Bierwirth(Data& d) : d_(d),
								bierwirth_vector_(d.nbJobs_ * d.nbMachines_),
								tabItem_(d.nbJobs_, liste_items()),
								tabOpe_(d.nbMachines_,  liste_machines()),
								makespan_(d.makespan_)
{
	// Initialisation du vecteur de Bierwith
	for (unsigned i = 0; i < d.jobs_.size(); i++) {
		for (unsigned j = 0; j < d.jobs_[i].size(); j++) {
			bierwirth_vector_[j * d.jobs_.size() + i] = &(d_.jobs_.at(i).at(j));
			bierwirth_vector_[j * d.jobs_.size() + i]->location_ = j * (unsigned)d.jobs_.size() + i;
		}
	}

	// On mélange
	std::random_shuffle(bierwirth_vector_.begin(), bierwirth_vector_.end());
}

Bierwirth::Bierwirth(Data &d, std::vector<unsigned> v)
	: d_(d),
	bierwirth_vector_(d.nbJobs_ * d.nbMachines_),
	tabItem_(d.nbJobs_, liste_items()),
	tabOpe_(d.nbMachines_, liste_machines()),
	makespan_(d.makespan_)
{
	std::vector<unsigned> index(d.nbJobs_, 0);

	if (v.size() != bierwirth_vector_.size())
		throw new ExceptionIncorrectSize();

	for (unsigned i = 0; i < v.size(); i++) {
		bierwirth_vector_[i] = &(d_.jobs_[v[i]][index[v[i]]]);
		index[v[i]]++;
	}
}

Bierwirth::Bierwirth(const Bierwirth& b):
	d_(b.d_),
	bierwirth_vector_(b.bierwirth_vector_),
	tabItem_(b.tabItem_),
	tabOpe_(b.tabOpe_),
	makespan_(b.makespan_),
	last_cp_(b.last_cp_){ }

const int Bierwirth::get_makespan_()
{
	return makespan_;
}

void Bierwirth::display() {

	std::cout << "Vecteur de Bierwirth utilisé :" << std::endl;
	for (unsigned i = 0; i < bierwirth_vector_.size(); i++) {
		if (i % 5 == 0)
			std::cout << std::endl;
		std::cout << "(" << bierwirth_vector_[i]->item_ << ",";
		std::cout << bierwirth_vector_[i]->machine_ << ")";
	}

	std::cout << std::endl << std::endl;
}

void Bierwirth::evaluer(std::vector<Job*>& b_new) {
	Job * cur;										// Pointeur actuel et précédent
	liste_machines * machine_tmp;					// Variable machine
	liste_items * item_tmp;							// Variable pièce
	unsigned time, wait_machine, wait_item;			// Variables de temps

	bierwirth_vector_ = b_new;						// On met a jour le nouveau vecteur de Bierwirth passe en parametre

	// On nettoie les tableaux au cas où il existe deja avant
	for (unsigned i=0;i < tabItem_.size();i++) {
		tabItem_[i].machines.clear();
		tabItem_[i].last_op = nullptr;
		tabItem_[i].duree = 0;
	}		// Nettoyage du vecteur des pièces

	for (unsigned i=0;i < tabOpe_.size();i++) {
		tabOpe_[i].jobs.clear();
		tabOpe_[i].last_op = nullptr;
		tabOpe_[i].duree = 0;
	}		// Nettoyage du vecteur des machines

	// Pour le premier job
	cur = bierwirth_vector_[0];
	cur->prev_ = nullptr;									// Pas de précédent
	cur->father_ = nullptr;									// Pas de père car c'est le premier
	cur->starting_ = 0;										// Démarre à t = 0
	cur->location_ = 0;										// Premier élément du tableau

	// Mise à jour des données par machine
	tabOpe_[cur->machine_].jobs.push_back(cur);				// On l'ajoute à la machine
	tabOpe_[cur->machine_].last_op = cur;					// C'est la dernière opération
	tabOpe_[cur->machine_].duree += cur->duration_;			// Mise à jour de la durée

	// Mise à jour des données par pièce
	tabItem_[cur->item_].machines.push_back(cur);			// Première opération pour la pièce
	tabItem_[cur->item_].last_op = cur;						// C'est la dernière opération
	tabItem_[cur->item_].duree += cur->duration_;			// Mise à jour de la durée
	
	for (unsigned i = 1; i < bierwirth_vector_.size(); i++) {
		// Mise en place des variables
		cur = bierwirth_vector_[i];
		machine_tmp = &(tabOpe_[cur->machine_]);
		item_tmp = &(tabItem_[cur->item_]);

		// Chainage
		//bierwirth_vector_[i - 1]->next_ = cur;					// Chainage suivant
		//cur->prev_ = bierwirth_vector_[i - 1];					// Chainage précédent
		//ici prev est redondant pusiqu'on a deja i
		
		if (machine_tmp->last_op != nullptr) machine_tmp->last_op->next_ = cur;
		cur->prev_ = machine_tmp->last_op;						// Chainage précédent : 

		cur->location_ = i;										// Enregistrement de la place dans Bierwirth

		// Gestion du temps
		if (machine_tmp->duree > item_tmp->duree) {				// On attend la machine
			time = machine_tmp->duree;
			wait_machine = 0;									// La machine n'attend pas
			wait_item = machine_tmp->duree - item_tmp->duree;	// La pièce attend après la machine

			// Father est le dernier job exécuté par la machine
			cur->father_ = (machine_tmp->jobs.size() < 1) ? nullptr
				:machine_tmp->jobs.at(machine_tmp->jobs.size() - 1);
						// Si on n'a pas encore d'éléments on met nullptr
		}else if (machine_tmp->duree == item_tmp->duree) {		// Pas d'attente
			time = machine_tmp->duree;
			wait_machine = 0;
			wait_item = 0;

			// Choix arbitraire ? Je prend la pièce comme référence
			
			cur->father_ = (std::max(item_tmp->machines.size(), machine_tmp->jobs.size()) < 1) ? nullptr
				: (item_tmp->machines.size() >= machine_tmp->jobs.size()) ?
				item_tmp->last_op
				: machine_tmp->last_op;
		}else {														// On attend la pièce d'une autre machine
			time = item_tmp->duree;
			wait_machine = item_tmp->duree - machine_tmp->duree;	// La machine est obligée d'attendre
			wait_item = 0;											// La pièce n'attend pas
			// Father est la dernière opération effectuée sur la pièce
			cur->father_ = (item_tmp->machines.size() < 1) ? nullptr
				: item_tmp->machines.at(item_tmp->machines.size() - 1);
			// Si on n'a pas encore d'éléments on met nullptr
		}

		// Mise à jour des données par machine
		machine_tmp->jobs.push_back(cur);
		machine_tmp->last_op = cur;
		machine_tmp->duree += wait_machine + cur->duration_;

		// Mise à jour des données par pièce
		item_tmp->machines.push_back(cur);
		item_tmp->last_op = cur;
		item_tmp->duree += wait_item + cur->duration_;

	}	// Fin for principal

	// Evaluation du makespan et de last_op
	makespan_ = tabItem_[0].duree;
	last_cp_ = tabItem_[0].last_op;								// Par défaut on prend la première pièce

	for (unsigned i = 0; i < tabItem_.size(); i++)
	{
		if (tabItem_[i].duree > makespan_) {
			makespan_ = tabItem_[i].duree;						// Mise à jour du makespan
			last_cp_ = tabItem_[i].last_op;						// Mise à jour de la dernière opération
		}
	}
}

// Méthode appelée pour evaluer le chemin critique avec le Bierwirth ALEATOIRE
void Bierwirth::evaluer()
{
	evaluer(bierwirth_vector_);

	// Mise a jour du makespan_ dans data
	d_.makespan_ = makespan_;
	d_.last_cp_ = last_cp_;
}

void liste_machines::afficher_sequence() {
	for (unsigned i = 0; i < jobs.size(); i++)
		std::cout << jobs[i]->item_ << " ";

	std::cout << std::endl;
}

void liste_machines::afficher_sequence_reverse() {
	Job* cur = last_op;
	for (Job* cur = last_op; cur!=nullptr; cur=cur->prev_)
		std::cout << cur->item_ << " ";

	std::cout << std::endl;
}

void Bierwirth::afficher_chemin_critique() {
	std::stack<Job *> p;				// Pile pour afficher le chemin critique dans le bon ordre
	Job * tmp = d_.last_cp_;

	p.push(tmp);
	
	tmp = tmp->father_;
	while(tmp != nullptr) {
		p.push(tmp);
		tmp = tmp->father_;
	}
	std::cout << "Chemin critique : " << std::endl;
	while ( !p.empty() ) {
		std::cout << "Job : " << std::setw(4) << p.top()->item_;
		std::cout << "\tMachine : " << std::setw(4) << p.top()->machine_;
		std::cout << std::endl;
		p.pop();
	}
	std::cout << std::endl;
	std::cout << "Makespan : " << makespan_ << std::endl;
	std::cout << std::endl;
}

void Bierwirth::afficher_sequences() {
	for (unsigned i = 0; i < tabOpe_.size(); i++) {
		std::cout << "Sequence de la machine num. " << i << std::endl;
		tabOpe_[i].afficher_sequence();
	}
	std::cout << std::endl;
}

void Bierwirth::recherche_locale() {
	Bierwirth b_new(*this);
	Job* cur;
	bool stop;													//si stop = false on a parcourue tout le chemin critique sans trouver d'arc disjonctif
	unsigned cpt_amelioration = 0, cpt_modification_Bierwirth = 0;	//cpt d'amelioration trouver, et cpt d'iteration total
	do {
		cur = b_new.last_cp_;
		stop = false;
		while (cur != NULL && !stop) {
			if (cur->prev_!=nullptr && cur->prev_ == cur->father_) {						//Si le lien entre la piece courante et son father est un arc disjonctif
																							//on echange les 2 jobs dans bierwirth
				std::swap(b_new.bierwirth_vector_[cur->location_],b_new.bierwirth_vector_[cur->father_->location_]);	
				b_new.evaluer(b_new.bierwirth_vector_);										//On réévalue bierwirth
				if (b_new.makespan_ < makespan_) {											//Si le makespan est meilleur -> on actualise nos element (le chemin critique)
					//Copie des nouvelles donnees
					bierwirth_vector_ = b_new.bierwirth_vector_;
					tabItem_ = b_new.tabItem_;
					tabOpe_ = b_new.tabOpe_;
					makespan_ = b_new.makespan_;
					last_cp_ = b_new.last_cp_;

					//mise a jour du makespan_ dans data
					d_.makespan_ = makespan_;
					d_.last_cp_ = last_cp_;
					stop = true;					//si stop = true, on a trouve une solution
					
					cpt_amelioration++;
				}
				cpt_modification_Bierwirth++;
			}
			if (cur == cur->father_) throw std::logic_error("Boucle infinie dans la Recherche Locale (chemin critique erroné)");
			cur = cur->father_;						//increment
		}
	} while (stop);									//Tant qu'on a des modifications, on continu

	//std::cout << "RL terminee en " << cpt_modification_Bierwirth << " tours, " << cpt_amelioration << " ameliorations ont ete apportees" << std::endl;
}

void Bierwirth::shuffle()
{
	std::random_shuffle(bierwirth_vector_.begin(), bierwirth_vector_.end());
}

Bierwirth & Bierwirth::operator=(const Bierwirth & b)
{
	if (&b != this) {
		d_=b.d_;
		bierwirth_vector_=b.bierwirth_vector_;
		tabItem_=b.tabItem_;
		tabOpe_=b.tabOpe_;
		makespan_=b.makespan_;
		last_cp_=b.last_cp_;
	}
	return *this;
}
