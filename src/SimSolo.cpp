#include "../include/SimMany.hpp"


SimSolo::SimSolo(int n_, double beta_, double alpha_) 
  : n(n_), alpha(alpha_)
  , beta(beta_)
  , rng(getSeed()*getSeed()) 
  , agent(n_,getSeed(), alpha_,0)  {}


bool SimSolo::flipStep(double& E0, double betaAtual){
  int flips = 1;
  double E = agent.propose(flips);
  if (exp(- betaAtual * (E - E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agent.accept();
    return true;
  }
  return false;
}


double SimSolo::mcStep(double &E0, double betaAtual){ 
  int steps = n * (n-1)/2;
  double E = E0;
  int accept = 0, count = 0;
  for(int j = 0; j < steps; j++) {
    accept += flipStep(E, betaAtual);
    count++;
  }
  E0 = E;
  return double(accept)/double(count);
}

double SimSolo::ksteps(int thin, double&E, double betaAtual){
  double accept = 0;
  int count = 0;
  for(int k = 0; k < thin; ++k){
    accept += mcStep(E, betaAtual);
    count++;
  }
  return accept/double(count);
}


void SimSolo::metroLoop(int nsteps, int burn, int anSteps, int thin) {
  double E = agent.energy();
  acc maxDeg, avgDeg, energy, acceptRate;
 
  //ANNEALING STEPS
  for(int t = 0; t < anSteps; ++t){
    double betaAtual = double(t)/double(burn)  * beta; 
    mcStep(E, betaAtual); 
  }
  // BURN-IN
  for(int t = 0; t < burn; ++t){
    mcStep(E,beta); 
  }
  //ACTUAL CALCULATION
  for(int t = 0; t < nsteps; ++t){ 
    double accept = ksteps(thin, E, beta);   
    acceptRate(accept);
    int center = 0;
    std::vector<int> degs = agent.degrees();
    double max  = getMax(degs,center);	
    double mean = getMean(degs);	
    maxDeg(max);
    avgDeg(mean);
    energy(E);
  }
  std::cout << std::setw(10) << std::setprecision(3);
  std::cout << mean(maxDeg) << " " 
	    << mean(avgDeg) << " " 
            << 0.0 << " "  // mean(corr)
	    << mean(energy) << " " 
	    << mean(acceptRate) << " " 
	    << variance(maxDeg) << " " 
	    << variance(avgDeg) << " " 
	    << variance(energy) << " " 
            << 0.0 << " "  //var(corr)
	    << std::endl;
}





/*void SimSolo::metroLoop(int nsteps, int burn, int anneal, int thin) {
  double E0 = agent.energy();
  double maxbet = double( (n-1)*(n-2)/2);
  double accept = 0;
  std::vector<int>    tmpdegrees    = agent.degrees();
  std::vector<double> tmpcentrality = agent.betweenness();
  //main loop
  for(int i = 0; i < nsteps; ++i) {
    accept = mcStep(E0, beta);
    if (i > burn) {
      tmpdegrees    = agent.degrees();
      tmpcentrality = agent.betweenness();
    }
  }
  }*/


