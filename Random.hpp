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

//random number generator class
class RndGen {
 public:  
  RndGen (int s);					// constructor, s = seed
  double getRndDouble (double minsp, double maxsp);	//get a random uniform double between minsp and maxsp
  int getRndInt (int min, int max);			// get a random integer between min and max
  intPair getIntPair(int min, int max);			// get a random pair of integers between min and max. Output is a boost::tuple<int,int> object
  void getIntPair(int min, int max, int& i, int& j);	// get a random pair of integers between min and max. ouput by reference.

 private:
  //typedef boost::mt19937 gentype;
  typedef boost::rand48  gentype;
  gentype r;
};

#endif // ANNEX_H_INCLUDED
