#include <sys/time.h>
#include "Sim2.hpp"
//#define NULL 0

int getSeed() {  
  struct timeval time;
  gettimeofday(&time, NULL);
  int seed = (time.tv_sec * 1000) + (time.tv_usec / 1000);
  return seed;    
}

Sim::Sim(int n_, double beta_, double alpha_) 
  : n(n_)
  , alpha(alpha_)
  , beta(beta_)
  , rng(getSeed() * getSeed())
  , agent(n_, getSeed(), alpha_, 0) {};


bool Sim::flipStep(double& E0) {
  int flips = 1;
  double E = agent.propose(flips);
  if (exp(- beta * (E - E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agent.accept();
    return true;
  }
  return false;  
}

double Sim::mcStep(double &E0) {
  double E = E0;
  int accept = 0;
  for(int j = 0; j < n; j++) {
    accept += flipStep(E);
  }
  E0 = E;
  return double(accept)/double(n);
}
o

void Sim::metroLoop(int nsteps, int burn) {
  double E0 = agent.energy();
  double accept = 0;
  int i = 0;
  while(i < nsteps) {
    accept += mcStep(E0);
    ++i;
    //std::cout << i << " " << accept << " " << E0 << std::endl;
  }
  std::cout << n << " " << accept / double(nsteps) << std::endl;
}


