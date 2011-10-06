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
    Agent tmp(n, getSeed(), alpha, 0.5);
    //tmp.propose(100);
    //tmp.accept();
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


bool SimMany::edgeSwapStep(int i, int j){
    int k;
    bool test = false;
    if(rng.getRndDouble(0,1) < q) {
        k = rng.getRndInt(0,n-1);
        agents[i].setEdge(j,k, agents[j].getEdge(j,k));
        test = true;
    }
    return test;
}

//bool SimMany::edgeSwapStep(int i, int j) {
//  int k;
//  bool test = true;
//  if( (rng.getRndDouble(0,1) < q)) {
//   int cnt = 0;
//   while (test) {
//     k = rng.getRndInt(0,n-1);
//     cnt++;
//     if (agents[j].getEdge(j,k) == 1) {
//        agents[i].setEdge(j,k, agents[j].getEdge(j,k));
//        test = false;
//     }
//     else if (cnt > n) {
//   break;
//     }
//   }
// }
// return (!test) ;



double SimMany::mcStep(std::vector<double>& energies, double betaAtual) {
  int steps = n * (n-1)/2;
  int i,j;
  int accept = 0;
  int count = 0;
  for(int k = 0; k < steps; k++){
   rng.getIntPair(0,n-1,i,j);
   edgeSwapStep(i, j);
   accept += flipStep(energies[i], i, betaAtual);
   count++;
  }
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
  acc maxDeg, avgDeg, corr, energy, acceptRate, centeracc;
  transform(agents.begin(),agents.end(),energies.begin(), tempEnergy);
  //ANNEALING STEPS
  for(int t = 0; t < anSteps; ++t){
    double betaAtual = beta * log(1.0 + double(t))/log(1.0 + double(anSteps)); // queda logaritmica na temperatura
    //double(t)/double(anSteps)  * beta; 
    mcStep(energies, betaAtual);
    //std::cout << "annealing " << t << " " << betaAtual << std::endl;
  }
  // BURN-IN
  for(int t = 0; t < burn; ++t){
    mcStep(energies,beta); 
    //std::cout << "buuuuurn!! " << t << std::endl;

  }
  //ACTUAL CALCULATION
  for(int t = 0; t < nsteps; ++t){ 
    double accept = ksteps(thin, energies, beta);   
    acceptRate(accept);
    std::vector<double> prob(n,0);
    std::vector<int> centers(n,0);
    for(unsigned int k = 0; k < agents.size(); ++k){
      int tmpcnt;
      std::vector<int> degs = agents[k].degrees();
      double max  = getMax(degs,tmpcnt);	
      double mean = getMean(degs);	
      prob[k] = mean / double(n-1);
      centers[k] = tmpcnt;
      maxDeg(max);
      avgDeg(mean);
    }
    energy(getMean(energies));
    //std::cout << t << " " << mean(energy) << " " << mean(maxDeg) << " " << mean(avgDeg) << std::endl;
    
    for(unsigned int i = 0; i < agents.size(); ++i){
      for(unsigned int j = 0; j < i; ++j) {
	corr(calcCorr(prob, i, j));
	centeracc( int(centers[i] == centers[j]) );
      }
    }
  }
    //std::cout << std::setw(10) << std::setprecision(3);
  std::cout	<< mean(maxDeg)			<< " "	//1    
		<< mean(avgDeg)          	<< " "	//2     
     		<< mean(corr)	                << " "	//3    
		<< mean(centeracc)              << " "  //4    
     		<< mean(energy)			<< " "	//5    
		<< mean(acceptRate)		<< " "	//6    
		<< variance(maxDeg)		<< " "	//7    
     		<< variance(avgDeg)		<< " "	//8    
		<< variance(corr)               << " "  //9    
		<< variance(centeracc)          << " "  //10  
     		<< variance(energy)		<< " "	//11  
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
