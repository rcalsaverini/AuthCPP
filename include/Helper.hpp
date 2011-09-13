#include <vector>
//#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "prettyprint.hpp"
#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

//return the phase
int phaseClassification(double normMaxBet); 
double calcMagnetization(symmetric_matrix<double,lower> adjmatrix, int size);
double calcOverlap(symmetric_matrix<double,lower> adjmatrix1, symmetric_matrix<double,lower> adjmatrix2, int size);


//get the maximum of a vector by return and get the maximum index by reference
template <class a> a getMax(const std::vector<a>& xs, int& i) { 
  a maxval = xs[0];
  int k = 0;
  i = 0;
  for(auto idx = xs.begin(); idx != xs.end(); ++idx){
    if (*idx >= maxval) {
      i = k;
      maxval = *idx;
    }
    ++k;
  }
  return maxval;
}
//get the mean of a vector
template <class a> double getMean(const std::vector<a>& xs){
  double tmp = 0.0;
  for (auto idx = xs.begin(); idx != xs.end(); ++idx) {
    tmp += double(*idx);
  } 
  return tmp/double(xs.size());
}

// //print vector;

// template <class a,class F> void printVecWith(const std::vector<a>& xs, F func){
//   for_each(xs.begin(), xs.end(), [&](a x) {
//       std::cout << std::setiosflags(std::ios::fixed)
// 		<< func(x) << " ";
//     });
// }


