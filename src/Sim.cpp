#include <cmath>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "../include/Sim.hpp"

//get current time in milisseconds precision
int getSeed() {  
  struct timeval time;
  gettimeofday(&time, NULL);
  //int seed = (time.tv_sec * 1000)+ (time.tv_usec/1000) ;
  int seed = (int(time.tv_usec) + int(time.tv_sec)*1000);
  return seed;    
}

//get the maximum of a vector
template <class a> 
a getMax(std::vector<a>& xs) {
  auto maxfun = [](a x, a y){ return std::max(x,y);};
  return std::accumulate(xs.begin(), xs.end(), 0, maxfun);
}

//get the mean of a vector
template <class a> 
double getMean(std::vector<a>& xs) {
  return double(std::accumulate(xs.begin(), xs.end(), 0.0))/double(xs.size());
}

//new random agent
Agent newRndAgent(int size, double alpha) {
  Agent tmp(size,getSeed(), alpha);
  tmp.propose(20*size);
  tmp.accept();
  return tmp;
}

  


SimSolo::SimSolo(int n_, double beta_, double alpha_) 
  : n(n_), alpha(alpha_)
  , beta(beta_)
  , rng(getSeed()*getSeed()) 
  , agent(n_,getSeed(), alpha_,0)  {}




bool SimSolo::flipStep(double& E0){
  int flips = 1;
  double E = agent.propose(flips);
  if (exp(- beta * (E - E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agent.accept();
    return true;
  }
  return false;
  
}


double SimSolo::mcStep(double &E0){ 
  double E = E0;
  int accept = 0;
  for(int j = 0; j < n; j++) {
    accept += flipStep(E);
  }
  E0 = E;
  return double(accept)/double(n);
}


void SimSolo::metroLoop(int nsteps, int burn, Results& res) {

  double E0 = agent.energy();
  double maxbet = double( (n-1)*(n-2)/2);
  double accept = 0;
  std::vector<int>    tmpdegrees    = agent.degrees();
  std::vector<double> tmpcentrality = agent.betweenness();
  //main loop
  for(int i = 0; i < nsteps; ++i) {
    accept = mcStep(E0);
    if (i > burn) {
      tmpdegrees    = agent.degrees();
      tmpcentrality = agent.betweenness();
      res.acc(E0, 
	      accept, 
	      getMax(tmpdegrees), 
	      getMean(tmpdegrees), 
	      agent.avgLength(), 
	      getMax(tmpcentrality)/maxbet, 
	      getMean(tmpcentrality)/maxbet );
    }
  }
}

