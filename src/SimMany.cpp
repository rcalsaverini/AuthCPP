#include "../include/SimMany.hpp"
//TESTE

SimMany::SimMany(int n_, double beta_, double alpha_, double q_)  : n(n_)
								  , alpha(alpha_)
								  , beta(beta_)
								  , q(q_)
								  , rng(getSeed()) 
								  , agents() {
					      
  
  agents.reserve(n_);
  for(int i =0; i < n_; i++){
    Agent tmp(n, getSeed(), alpha);
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

double SimMany::calcCorr(std::vector<double> prob, int i, int j) {
  double q = 0;
  for(unsigned int k = 0; k < agents.size(); ++k)
    {
      for(unsigned int l = 0; l < k; ++l)
	{
	  double xi = agents[i].getEdge(k,l);
	  double xj = agents[j].getEdge(k,l);
	  q += ((xi - prob[i]) * (xj - prob[j]));
	}
    }
  return (2 * q/ double(n * (n-1)));
}

double tempEnergy(Agent ag);
double tempEnergy(Agent ag) {
  return ag.energy();
}

void SimMany::metroLoop(int nsteps, int burn, int anSteps, int thin) {
  std::vector<double> energies(n);
  acc maxDeg, avgDeg, corr, energy, acceptRate;
  transform(agents.begin(),agents.end(),energies.begin(), tempEnergy);
  //ANNEALING STEPS
  for(int t = 0; t < anSteps; ++t){
    double betaAtual = beta * log(1.0 + double(t))/log(1.0 + double(anSteps)); // queda logaritmica na temperatura
    //double(t)/double(anSteps)  * beta; 
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
    std::vector<double> prob(n,0);
    for(unsigned int k = 0; k < agents.size(); ++k){
      int tmpcnt;
      std::vector<int> degs = agents[k].degrees();
      double max  = getMax(degs,tmpcnt);	
      double mean = getMean(degs);	
      prob[k] = mean / double(n-1);
      maxDeg(max);
      avgDeg(mean);
    }
    energy(getMean(energies));
    
    
    for(unsigned int i = 0; i < agents.size(); ++i){
      for(unsigned int j = 0; j < i; ++j) {
	corr(calcCorr(prob, i, j));
      }
    }
  }
    //std::cout << std::setw(10) << std::setprecision(3);
  std::cout	<< mean(maxDeg)			<< " "	//3    0
		<< mean(avgDeg)          	<< " "	//4    1 
     
		<< mean(corr)	                << " "	//5    2
     		<< mean(energy)			<< " "	//6    3
		<< mean(acceptRate)		<< " "	//7    4
    
		<< variance(maxDeg)		<< " "	//8    5
     		<< variance(avgDeg)		<< " "	//9    6
     		<< variance(energy)		<< " "	//10   7
		<< variance(corr)               << " "  //11   8
                << std::endl;
  
}


  // std::vector<double> prob(n,0);
  
  // for(unsigned int k = 0; k < agents.size(); ++k){
  //     int tmpcnt;
  //     std::vector<int> degs = agents[k].degrees();
  //     double max  = getMax(degs,tmpcnt);	
  //     double mean = getMean(degs);	
  //     std::cout << k << " " << tmpcnt << " " << mean/max << std::endl;
  //     prob[k] = mean / double(n - 1);
  // }
  // std::cout << std::endl;
  // std::cout << std::setw(10) << std::setprecision(3) << std::endl;  
  
  // for(unsigned int i = 0; i < agents.size(); ++i){      
  //   for(unsigned int j = 0; j < i; j++){
  //     double corr = 0;
      
  //     for(unsigned int k = 0; k < agents.size(); ++k){
  // 	for(unsigned int l = 0; l < k; ++l){
  // 	  double xi = agents[i].getEdge(k,l);
  // 	  double xj = agents[j].getEdge(k,l);
  // 	  corr += (xi - prob[i]) * (xj - prob[j]);
  // 	}
  //     }
  //     std::cout << i << " " << j << " - " << 2 * corr /double(n * (n-1)) << std::endl;
  //   }
  // }
