#pragma once

#include <iostream>
#include <limits>


struct Job
{
    static const unsigned NO_TIME;
    static const unsigned NO_LOCATION;

  unsigned item_;			// ID du job
  unsigned machine_;		// ID de la machine
  unsigned duration_;		// Durée du job

  Job * next_;				// TODO: set an in-class initialization
  Job * prev_;				// TODO: set an in-class initialization
  Job * father_;			// TODO: set an in-class initialization		// Job de départ qui permet de fixer la date de départ, permet de remonter le chemin critique = tête de liste
  unsigned starting_;		// TODO: set an in-class initialization		// Temps où le job démarre
  unsigned location_;		// TODO: set an in-class initialization		// Machine où il se trouve
  
  Job () : item_(0), machine_(0), duration_(0), next_(nullptr), prev_(nullptr), father_(nullptr), starting_(NO_TIME), location_(NO_LOCATION) {}
  //Job (unsigned i, unsigned m, unsigned d) : item_(i), machine_(m), duration_(d), next_(nullptr), prev_(nullptr), father_(nullptr), starting_(NO_TIME) {}
  
  void clear () {next_ = prev_ = father_ = nullptr; starting_ = NO_TIME; location_ = NO_LOCATION;}

  void display_all (std::ostream &) const;

};

std::ostream & operator<< (std::ostream &, const Job &);


