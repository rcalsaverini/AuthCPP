#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/symmetric.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;
using namespace boost::accumulators;


class Overlap{
private:

  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > acc;
  int size;
  symmetric_matrix<acc, lower> accumatrix; 
  

public:
  Overlap(int n) : size(n), accumatrix(n,n) {};
  void operator()(const symmetric_matrix<double, lower> data) {
    for(int i = 0; i < size; ++i)
      for(int j = 0; j < i; ++j){
	accumatrix(i,j)(data(i,j));
      }
  }
  
  void operator()(int i, int j, double data) {
    accumatrix(i,j)(data);
  }
  
  symmetric_matrix<double, lower> getMean() {
    symmetric_matrix<double, lower> means(size,size);
    for(int i = 0; i < size; ++i)
      for(int j = 0; j < i; ++j){
	means(i,j) = mean(accumatrix(i,j));
      }
    return means;
  }

  double getMean(int i, int j) {
    double meanij;
    meanij = mean(accumatrix(i,j));
    return meanij;
  }  

  double getFullMean() {
    double tmp = 0.0;
    double cnt = 0.0;
    for(int i = 0; i < size; ++i) 
      for(int j = 0; j < i; ++j) {
	tmp += mean(accumatrix(i,j));
	cnt += 1.0;
      }
    return tmp/cnt;
  }  


};

class StatVector{
private:
  typedef accumulator_set<double, stats<tag::mean, tag::variance(lazy)> > acc;
  int size;
  std::vector<acc> accvector; 
  

public:
  StatVector(int n) : size(n), accvector(n) {};
  
  void operator()(std::vector<double> data) {
    for(int i = 0; i < size; ++i)
      accvector[i](data[i]);
  }
  
  void operator()(int i, double data) {
    accvector[i](data);
  }
  
  std::vector<double> getMean() {
    std::vector<double> means(size);
    for(int i = 0; i < size; ++i)
      means[i]= mean(accvector[i]);
    return means;
  }
  
  double getMean(int i) {
    return mean(accvector[i]);
  }  

  double getFullMean() {
    double tmp = 0.0;
    for(int i = 0; i < size; i++) 
      tmp += mean(accvector[i]);
    return tmp/double(size);
  }  


};
