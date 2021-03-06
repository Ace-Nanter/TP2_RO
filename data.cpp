#include "data.h"
#include "Bierwirth.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>


Data::Data (const std::string & filename) : name_(filename), jobs_(0), last_cp_(nullptr), makespan_(0)
{
  std::ifstream is(filename.c_str());

  if (!is)
  {
    std::cerr << "Error: unable to open file \'" << filename << "\'" << std::endl;
    exit (EXIT_FAILURE);
  }

  // step over the first line
  std::string line;
  getline(is, line);

  // get the instance size
  is >> nbJobs_ >> nbMachines_;
  
  // memory allocation
  jobs_.resize(nbJobs_);
  for (unsigned i = 0; i < nbJobs_; ++i)
  {
    jobs_[i].resize(nbMachines_);
  }
  first_.resize(nbMachines_);
  last_.resize(nbMachines_);

  // get the information
  for (unsigned i = 0; i < nbJobs_; ++i)
  {
    for (unsigned m = 0; m < nbMachines_; ++m)
    {
      Job & job = jobs_[i][m];
      job.item_ = i;
      is >> job.machine_ >> job.duration_;
    }
  }
}

Data::Data(const Data & d) {
	nbJobs_=d.nbJobs_;
	nbMachines_=d.nbMachines_;
	jobs_=d.jobs_;
	first_=d.first_;
	last_=d.last_;
	last_cp_=d.last_cp_;
	makespan_=d.makespan_;
	rng_engine_=d.rng_engine_;
}

void Data::clear () {
  for (auto line : jobs_)
  {
    for (auto elt : line)
    {
      elt.clear();
    }
  }
  for (auto & jobptr : first_)
  {
    jobptr = nullptr;
  }
  for (auto & jobptr : last_)
  {
    jobptr = nullptr;
  }
  last_cp_ = nullptr;
  makespan_ = Job::NO_TIME;
}


void Data::display_all (std::ostream & os) const
{
  os << "instance " << name_ << ": " << nbJobs_ << " items " << nbMachines_ << " machines" << std::endl;
  for (auto & line : jobs_)
  {
    for (auto & job : line)
    {
      job.display_all(os);
    }
    os << std::endl;
  }
  os << "last_cp = ";
  if (last_cp_ == nullptr)
  {
    os << "nullptr";
  }
  else
  {
    last_cp_->display_all(os);
  }
  os << std::endl;
}


std::ostream & operator<< (std::ostream & os, const Data & d)
{
  os << "instance " << d.name_ << ": " << d.nbJobs_ << " items " << d.nbMachines_ << " machines" << std::endl;
  for (auto & line : d.jobs_)
  {
    for (auto & job : line)
    {
      os << ' ' << job.machine_ << ' ' << job.duration_;
    }
    os << std::endl;
  }
  return os;
}