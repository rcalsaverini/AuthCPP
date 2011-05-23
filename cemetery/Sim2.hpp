#include "Agent.hpp"

int getSeed();

class Sim {
private:
  int n;
  double alpha;
  double beta;
  RndGen rng;
  Agent agent;

public:
  Sim(int n_, double beta_, double alpha_);
  bool flipStep(double& E0);
  double mcStep(double& E0);
  void metroLoop(int nsteps, int burn);
};


/*
class Bootstrap {
private:
  double mean, variance;
  vector<double> queue;
public:
  Bootstrap(): mean(0.0), variance(0.0){};
  void clear();
  void acc(double x){queue.push_back(x);}
  void calc();
  double getMean();
  double getVariance();
};
*/
