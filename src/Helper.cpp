#include "../include/Helper.hpp"

int phaseClassification(double normMaxBet) {
  if (normMaxBet > 0.8) 
    return 0; //graph is in the star phase (hub-phase, asymmetric phase)
  else if (normMaxBet > 0.2)
    return 2; //graph is in transitional phase 1 - <max degree> drops suddenly
  else if (normMaxBet > 0.01)
    return 3; //graph is in transitional phase 2 - <max degree> slowly recovers
  else 
    return 1; //graph in in symmetric, strongly connected phase
}

double calcMagnetization(symmetric_matrix<double,lower> adjmatrix, int size){
  double sum = 0, num = 0;
  for(int i = 0; i < size; ++i){
    for(int j = 0; j < i; ++j) {
      sum += adjmatrix(i,j);
      num += 1.0;
    }
  }
  return (sum/num);
}

double calcOverlap(symmetric_matrix<double,lower> adjmatrix1,
		   symmetric_matrix<double,lower> adjmatrix2,
		   int size){
  double sum = 0, num = 0;
  for(int i = 0; i < size; ++i){
    for(int j = 0; j < i; ++j) {
      sum += adjmatrix1(i,j) *  adjmatrix2(i,j);
      num += 1.0;
    }
  }
  return (sum/num);
}
