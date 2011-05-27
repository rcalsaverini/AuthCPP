//TODO: Many agents!
class SimSolo {
private:
  int n;
  double alpha;
  double beta;
  RndGen rng;
  vector<Agent> agent;
  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > accDouble;
  typedef accumulator_set<int,    stats<tag::mean, tag::variance(lazy)> > accInt;

public:
  SimSolo(int n_, double beta_, double alpha_);		//constructor
  bool flipStep(double& E0);				// a single flipstep
  double mcStep(double& E0);				// a single montecarlo step = n flipsteps
  void metroLoop(int nsteps, int burn, Results& res);	//full montecarlo loop.

};
