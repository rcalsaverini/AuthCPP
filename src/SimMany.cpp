#include "../include/SimMany.hpp"

SimMany::SimMany(int n_, double beta_, double alpha_, double q_)  : n(n_)
								  , alpha(alpha_)
								  , beta(beta_)
								  , q(q_)
								  , rng(getSeed()) 
								  , agents() {
					      
  
  agents.reserve(n_);
  for(int i =0; i < n_; i++){
    Agent tmp(n, getSeed(), alpha,0);
    tmp.propose(100);
    tmp.accept();
    agents.push_back(tmp);
  }
}




bool SimMany::flipStep(double& E0, int i, double betaAtual){
  int flips = 1;
  bool res = false;
  double E = agents[i].propose(flips);
  if( exp(-betaAtual * (E-E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agents[i].accept();
    res = true;
  }
  return res;
}

bool SimMany::edgeSwapStep(int i, int j) {
  int k;
  bool test = true;
  if( (rng.getRndDouble(0,1) < q)) {
    //rng.getIntPair(0, n-1,k,l); <- segunda opcao
  
    int cnt = 0;
    while (test) {
      k = rng.getRndInt(0,n-1);
      cnt++;
      //std::cout << cnt << " " << k << " - " << i << " " << j << " - " << agents[j].getEdge(j,k) << " " << std::endl;
      if (agents[j].getEdge(j,k) == 1) {
	agents[i].setEdge(j,k, agents[j].getEdge(j,k));
	test = false;
      }
      else if (cnt > n) {
	break;
      }
    }
  }
  return (!test) ;
}


double SimMany::mcStep(std::vector<double>& energies, double betaAtual) {
  int steps = n * (n-1)/2;
  int i,j;
  int accept = 0;
  int count = 0;
  for(int k = 0; k < steps; k++){
     i = rng.getRndInt(0,n-1);
     accept += flipStep(energies[i], i, betaAtual);
     count++;
  }
  rng.getIntPair(0,n-1,i,j);
  edgeSwapStep(i, j);
  return double(accept)/double(count);
}


double SimMany::ksteps(int thin, std::vector<double>& energies, double betaAtual){
  double accept = 0;
  int count = 0;
  for(int k = 0; k < thin; ++k){
    accept += mcStep(energies, betaAtual);
    count++;
  }
  return accept/double(count);
}


void SimMany::metroLoop(int nsteps, int burn, int anSteps, int thin) {
  std::vector<double> energies(n);
  acc maxDeg, avgDeg, centerCorr, energy, acceptRate;
  transform(agents.begin(),agents.end(),energies.begin(),
	    [](Agent ag) {return ag.energy();} 
	    );

  //ANNEALING STEPS
  for(int t = 0; t < anSteps; ++t){
    double betaAtual = double(t)/double(anSteps)  * beta; 
    mcStep(energies, betaAtual); 
  }
  // BURN-IN
  for(int t = 0; t < burn; ++t){
    mcStep(energies,beta); 
  }
  //ACTUAL CALCULATION
  for(int t = 0; t < nsteps; ++t){ 
    double accept = ksteps(thin, energies, beta);   
    acceptRate(accept);
    std::vector<int> center(n,0);
    for(unsigned int k = 0; k < agents.size(); ++k){
      int tmpcnt;
      std::vector<int> degs = agents[k].degrees();
      double max  = getMax(degs,tmpcnt);	
      double mean = getMean(degs);	
      center[k] = tmpcnt;
      maxDeg(max);
      avgDeg(mean);
    }
    energy(getMean(energies));

    /*double scenter = 0;
    for(unsigned int k = 0; k < agents.size(); ++k)
      for(unsigned int l = 0; l < k; ++l)
	scenter += (center[k] == center[l])? 1.0 : 0.0;
	centerCorr(2.0 * scenter / double(n * (n-1)));*/

  }
  std::cout << std::setw(10) << std::setprecision(3);
  std::cout << mean(maxDeg) << " " 
	    << mean(avgDeg) << " " 
	    << mean(energy) << " " 
	    << mean(acceptRate) << " " 
    //<< mean(centerCorr) << " " 
	    << variance(maxDeg) << " " 
	    << variance(avgDeg) << " " 
	    << variance(energy) << " " 
    // << variance(centerCorr) << " "
    
	    << std::endl;
}
