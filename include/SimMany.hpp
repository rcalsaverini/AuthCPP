#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>

#include "../include/Helper.hpp"
#include "../include/Random.hpp"
#include "../include/Agent.hpp"
#include "../include/Measures.hpp"
#include "../include/prettyprint.hpp"

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>


using namespace boost::numeric::ublas;
using namespace boost::accumulators;

typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > acc;

class ManyAgentsH {
private:
  int n;			//number of agents 
  double alpha;			//agent's cognitive capacity
  double beta;			// inverse temperature
  double J;			// interaction
  RndGen rng;			// random number generator
  std::vector<Agent> agents;	// a vector of agents;
 


public:
  SimMany(int n_, double beta_, double alpha_, double q_ );	     	     //constructor
  double deltaIntEnergy(int i, int j, int k);                                   // variation in the interaction energy if we flip (j,k) edge in agent i.
  bool flipStep(double& E0, int i, double beta);		     	     // a single flipstep
  double mcStep(std::vector<double>& energies, double betaAtual);    	     // a single montecarlo step = n flipsteps, q = probability of an edge swap step
  double ksteps(int thin, std::vector<double>& energies, double beta); 	     // run thin montecarlo steps without measuring anything  
  double calcCorr(std::vector<double> prob, int i, int j);  
  void metroLoop(int nsteps, int burn, int anSteps, int thin);		     //full montecarlo loop.

};

class ManyAgentsPassMessage {
private:
  int n;			//number of agents 
  double alpha;			//agent's cognitive capacity
  double beta;			// inverse temperature
  double q;			// probability of edge swapping (gossip)
  RndGen rng;			// random number generator
  std::vector<Agent> agents;	// a vector of agents;
 


public:
  SimMany(int n_, double beta_, double alpha_, double q_ );	     	     //constructor
  bool flipStep(double& E0, int i, double beta);		     	     // a single flipstep
  bool edgeSwapStep(int i, int j);				     	     // a single edgeSwapStep
  double mcStep(std::vector<double>& energies, double betaAtual);    	     // a single montecarlo step = n flipsteps, q = probability of an edge swap step
  double ksteps(int thin, std::vector<double>& energies, double beta); 	     // run thin montecarlo steps without measuring anything  
  double calcCorr(std::vector<double> prob, int i, int j);  
  void metroLoop(int nsteps, int burn, int anSteps, int thin);		     //full montecarlo loop.

};

class SimSolo {
private:
  int n;
  double alpha;
  double beta;
  RndGen rng;
  Agent agent;

public:
  SimSolo(int n_, double beta_, double alpha_);					//constructor
  bool flipStep(double& E0, double beta);					// a single flipstep
  double mcStep(double& E0, double beta);					// a single montecarlo step = n flipsteps
  double ksteps(int thin, double& E0, double beta);				// run thin mcsteps
  void metroLoop(int nsteps, int burn, int anSteps, int thin);	                //full montecarlo loop.
  
};
