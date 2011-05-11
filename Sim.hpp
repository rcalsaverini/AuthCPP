#include "Agent.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
using namespace boost::accumulators;

int getms();

class SimSolo {
private:
  int n;
  double alpha;
  double beta;
  RndGen rng;
  Agent agent;
  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > accDouble;
  typedef accumulator_set<int,    stats<tag::mean, tag::variance(lazy)> > accInt;


public:
  SimSolo(int n_, double beta_, double alpha_);  
  bool metropStep(double& E0);
  void metroLoop(int nsteps, int burn, bool verbose, double& energy, double& varEnergy, double& avgDeg, double& maxDeg, double& meanAccept, double& maxCen, double& avgCen, double& len);
  void metroRun(int msteps, int nsteps, int burn);
      
 
};
