#include "../include/Random.hpp"
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <sys/time.h>

using namespace boost::tuples;
//get current time in milisseconds precision

int getSeed() {  
  struct timeval time;
  gettimeofday(&time, NULL);
  //int seed = (time.tv_sec * 1000)+ (time.tv_usec/1000) ;
  int seed = (int(time.tv_usec) + int(time.tv_sec)*1000);
  return seed;    
}



// OLD VERSION USING BOOST
RndGen::RndGen (int s) {
    r.seed(boost::uint32_t(s));
}

double RndGen::getRndDouble (double minsp, double maxsp) {
  boost::uniform_real<> dist (minsp, maxsp);
  boost::variate_generator<gentype&, boost::uniform_real<> > rndDouble (r, dist);
  return rndDouble ();
}

int RndGen::getRndInt (int min, int max) {
  boost::uniform_int<> dist (min, max);
  boost::variate_generator<gentype&, boost::uniform_int<> > rndInt (r, dist);
  return rndInt ();
}


intPair RndGen::getIntPair(int min, int max) {
  int i = getRndInt(min, max);
  int j = i;
  while(j == i){
    j = getRndInt(min,max);
  }
  return boost::make_tuple(i, j);

}


void RndGen::getIntPair(int min, int max, int& i, int& j){
  i = getRndInt(min, max);
  j = i;
  while(j == i) {
    j = getRndInt(min,max);
  }
}
