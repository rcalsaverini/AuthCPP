#include <vector>
#include "../include/Random.hpp"
#include "../include/Agent.hpp"
#include "../include/Helper.hpp"
#include "../include/Measures.hpp"
#include "../include/prettyprint.hpp"

using namespace boost::numeric::ublas;
using namespace boost::accumulators;


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




/*class Measures {
private:
  int size;
  std::vector<double> maxCen,  avgCen;
  std::vector<int>    centerCen, centerDeg;
  std::vector<int>    maxDeg; 
  std::vector<double> avgDeg;

public:
  Measures(int n) : size(n) 
		  , maxCen(n)    , avgCen(n)
		  , centerCen(n) , centerDeg(n)
		  , maxDeg(n)    , avgDeg(n)  {};

  void acc(const std::vector<Agent>& agents) {
    int k = 0;
    double maxbet = double( (size-1) * (size-2) / 2);
    for(auto ag = agents.begin(); ag != agents.end(); ++ag){
      int tmpCenter = 0;
      std::vector<double> tmpCentrality = (*ag).betweenness();
      std::vector<int>    tmpDegrees    = (*ag).degrees();
      maxCen[k]		= getMax(tmpCentrality, tmpCenter)/maxbet;
      avgCen[k]		= getMean(tmpCentrality)/maxbet;
      centerCen[k]	= tmpCenter;
      maxDeg[k]		= getMax(tmpDegrees, tmpCenter);
      avgDeg[k]		= getMean(tmpDegrees);
      centerDeg[k]	= tmpCenter;
      ++k;
    }
  }

  //friend std::ostream& operator<< (std::ostream &out, Measures meas) {
  void printMeasures() {
    std::cout << std::setw(5) << std::setprecision(3);
    std::cout << maxDeg << "  " << avgDeg;
    //printVec(avgDeg);
    //printVec(maxDeg);
    //printVecWith(avgDeg,  [&](double x){ return x/double(size);});
    //printVec(centerCen);
    //std::cout << "\t";
    //printVecWith(maxCen, phaseClassification);
    //std::cout << "\t";
    //printVecWith(maxDeg,  [&](int x){ return double(x)/double(size);});
    //printVec(centerDeg);
    //printVec(avgCen);
  }

  

  };*/
