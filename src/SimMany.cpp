#include <algorithm>
#include <vector>
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



bool SimMany::flipStep(double& E0, int i){
  int flips = 1;
  double E = agents[i].propose(flips);
  if( exp(-beta * (E-E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agents[i].accept();
    return true;
  }
  return false;
}

bool SimMany::edgeSwapStep(int i, int j) {
  int k;
  if(rng.getRndDouble(0,1) < q) {
    //rng.getIntPair(0, n-1,k,l); <- segunda opcao
    k = rng.getRndInt(0,n-1);
    agents[i].setEdge(j,k, agents[j].getEdge(j,k));
    return true;
  }
  return false;
}


void SimMany::mcStep(int i, int j, double& E0) {
  double E = E0;
  //int accept = 0, edgeSwap = 0;
  for(int k = 0; k < n; k++){
   flipStep(E,i);
   edgeSwapStep(i, j);
  }
  E0 = E;
}



void SimMany::metroLoop(int nsteps, int burn) {
  std::vector<double> energies(n);
  Overlap    overlap(n);
  StatVector magnetization(n); 
  transform(agents.begin(),agents.end(),energies.begin(),
	    [](Agent ag) {return ag.energy();} 
	    );

  for(int t = 0; t < nsteps; ++t){ 
    int i, j;
    rng.getIntPair(0, n-1,i,j);
    mcStep(i, j, energies[i]);
    if (t > burn) {
      std::vector<double> tmpMag(n);
      for(int k = 0; k < agents.size(); ++k){
	auto adjMatrix1 = agents[k].adjacency();
	double mag = calcMagnetization(adjMatrix1, n);
	magnetization(k, mag);
	tmpMag[k] = mag;
	for(int l = 0; l < k; ++l){
	  auto adjMatrix2 = agents[l].adjacency();
	  double over = calcOverlap(adjMatrix1, adjMatrix2, n);
	  overlap(k,l,over);
	  }
      }
      //std::cout << tmpMag;//magnetization.getMean();
      //std::cout << std::endl;
    }
  }
  double m = magnetization.getFullMean();
  double q = overlap.getFullMean();
  double rho = q > m*m ? sqrt(q - m * m) : 0.0;
  std::cout << m << " " << rho << std::endl;
}
