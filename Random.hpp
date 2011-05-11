#ifndef ANNEX_H_INCLUDED
#define ANNEX_H_INCLUDED
//#include <gsl/gsl_rng.h>
//#include <gsl/gsl_randist.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/tuple/tuple.hpp>

typedef boost::tuple<int,int> intPair;

class RndGen {
 public:
  RndGen (int s); 
  double getRndDouble (double minsp, double maxsp); 
  int getRndInt (int min, int max); 
  int getRndInt2 (int min, int max); 
  intPair getIntPair(int min, int max);
  void getIntPair(int min, int max, int& i, int& j);
  
 private:
  //typedef boost::mt19937 gentype;
  typedef boost::rand48  gentype;
  gentype r;
};

#endif // ANNEX_H_INCLUDED
