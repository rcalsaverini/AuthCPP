#include <vector>
#include "../include/Random.hpp"
#include "../include/Agent.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

template <class a> a getMax(const std::vector<a>& xs, int& i);
template <class a> double getMean(const std::vector<a>& xs);
template <class a> void printVec(const std::vector<a>& xs);


using namespace boost::accumulators;

//template <class a> a getMax(std::vector<a>& xs);
//template <class a> double getMean(std::vector<a>& xs);



class SimMany {
private:
  int n;			//number of agents 
  double alpha;			//agent's cognitive capacity
  double beta;			// inverse temperature
  double q;			// probability of edge swapping (gossip)
  RndGen rng;			// random number generator
  std::vector<Agent> agents;	// a vector of agents;


public:
  SimMany(int n_, double beta_, double alpha_, double q_);	//constructor
  bool flipStep(double& E0, int i);		// a single flipstep
  bool edgeSwapStep(int i, int j);		// a single edgeSwapStep
  void mcStep(int i, int j, double& E0);	// a single montecarlo step = n flipsteps, q = probability of an edge swap step
  void metroLoop(int nsteps, int burn);		//full montecarlo loop.

};
