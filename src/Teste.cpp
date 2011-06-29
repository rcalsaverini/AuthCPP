#include <iostream>
#include <vector>
#include "../include/SimMany.hpp"
#include <tclap/CmdLine.h>

//#include "../include/Helper.hpp"

//using namespace std;
using namespace TCLAP;

void runMany(int n, int burn, int steps, double beta, double alpha, double q);
//void testHelper();

int main(int argc, char** argv){
  try { 
    CmdLine cmd("Runnable simulation for the authority model."
		"This is supposed to give the average overlaps if you input the model parameters."
		, ' ', "0.01");
    UnlabeledValueArg<int> numAgents("size",    "Number of agents",            true, 20,    "numAgents");
    UnlabeledValueArg<int> mcSteps  ("mcSteps", "Number of Monte Carlo steps", true, 50000, "mcSteps");
    UnlabeledValueArg<int> burnIn   ("burn",    "Number of burned steps",      true, 25000, "burnIn");
    UnlabeledValueArg<double> beta  ("beta",    "Inverse temperature",         true, 5.0,   "beta");
    UnlabeledValueArg<double> alpha ("alpha",   "Cognitive capacity",          true, 60.0,  "alpha");
    UnlabeledValueArg<double> qprob ("q",       "Gossip ratio - probability of exchanging an edge", true, 0.0,  "q");
    cmd.add(numAgents);
    cmd.add(mcSteps);
    cmd.add(burnIn);
    cmd.add(beta);
    cmd.add(alpha);
    cmd.add(qprob);
    cmd.parse(argc, argv);
    runMany( numAgents.getValue(),
		 burnIn.getValue(),
		 mcSteps.getValue(),
		 beta.getValue(),
		 alpha.getValue(),
		 qprob.getValue());
    
  } 
  catch(ArgException &e) {
    std::cerr << "error: " 
	      << e.error() 
	      << " for arg " 
	      << e.argId() 
	      << std::endl; 
  }
  return 0;
}



void runMany(int n, int burn, int steps, double beta, double alpha, double q) {
  //int n = 20, burn = 25000, steps = 50000;
  //double beta = 5.0, alpha = double(n * (n-1)/2.0) * 0.3, q = 0.02; 
  SimMany foo(n, beta, alpha, q);
  foo.metroLoop(steps, burn); 
}

/*void testHelper(){
  std::vector<double> foo({12,23,2,3,2});
  int j = 0;
  std::cout << "Escrever vetor na tela:" << foo           << std::endl;
  std::cout << "media do vetor:"         << getMean(foo)  << std::endl;
  std::cout << "maximo do vetor:"        << getMax(foo,j) << std::endl;
  std::cout << "indice do maximo:"       << j             << std::endl;
  }*/

