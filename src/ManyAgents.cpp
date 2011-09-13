#include "../include/SimMany.hpp"
ManyAgentsH::ManyAgentsH(int n_, double beta_, double alpha_, double q_)  : n(n_)
								  , alpha(alpha_)
								  , beta(beta_)
								  , q(q_)
								  , rng(getSeed()) 
								  , agents() {
  
  agents.reserve(n_);
  for(int i =0; i < n_; i++){
    Agent tmp(n, getSeed(), alpha, i);
    agents.push_back(tmp);
  }
}


double ManyAgentsH::deltaIntEnergy(int i, int j, int k){
  

}



bool ManyAgentsH::flipStep(double& E0, int i, double betaAtual){
  int flips = 1;
  bool res = false;
  double E = 
  if( exp(-betaAtual * (E-E0)) > rng.getRndDouble(0,1)) {
    E0 = E;
    agents[i].accept();
    res = true;
  }
  return res;
}
