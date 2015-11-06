#pragma once

#include "job.h"

#include <vector>
#include <random>


struct Data
{
  std::string name_;
  unsigned nbJobs_;
  unsigned nbMachines_;
  std::vector< std::vector<Job> > jobs_;
  std::vector<Job*> first_;
  std::vector<Job*> last_;

  /*----------------------------------------------------*/
  /* Une machine = une liste de jobs					*/
  /* Donc dans data puisqu'on a une liste de machines	*/
  /* On a une liste de listes de jobs					*/
  /* Et donc on a une listes de premiers jobs et une	*/
  /* liste de derniers jobs								*/
  /* Et du coup les indices doivent correspondre		*/
  /*----------------------------------------------------*/

  Job *  last_cp_;					// 
  unsigned makespan_;

  std::mt19937 rng_engine_;

  Data (const std::string &);
  void clear ();										// ?

  void display_all (std::ostream &) const;				// Affichage des données
};

std::ostream & operator<< (std::ostream &, const Data &);
