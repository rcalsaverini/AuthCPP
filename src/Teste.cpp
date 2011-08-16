#include <iostream>
#include <vector>
#include "../include/SimMany.hpp"
#include <tclap/CmdLine.h>

using namespace TCLAP;

void run(int n, int burn, int steps, int anSteps, int thin, double beta, double alpha, double q, int lone);

int main(int argc, char** argv){
  try { 
    CmdLine cmd("Runnable simulation for the authority model."
		"This is supposed to give the average overlaps if you input the model parameters."
		, ' ', "0.01");
    UnlabeledValueArg<int>    numAgents	("size"	   , "Number of agents"					                        , true   , 20	 , "numAgents");
    UnlabeledValueArg<int>    mcSteps	("mcSteps" , "Number of Monte Carlo steps"	                			, true   , 50000 , "mcSteps");
    UnlabeledValueArg<int>    burnIn	("burn"	   , "Number of burned steps"                   				, true	 , 25000 , "burnIn");
    UnlabeledValueArg<int>    anSteps   ("anSteps" , "Number of annealing steps"			                	, true	 , 25000 , "anSteps");
    UnlabeledValueArg<double> beta	("beta"	   , "Inverse temperature"		                			, true	 , 5.0	 , "beta");
    UnlabeledValueArg<double> alpha	("alpha"   , "Cognitive capacity"                			                , true	 , 60.0	 , "alpha");
    UnlabeledValueArg<double> qprob	("q"	   , "Gossip ratio - probability of exchanging an edge"	                        , true	 , 0.0	 , "q");
    UnlabeledValueArg<int>    lone	("lone"	   , "simulate a lonely agent if lone = 1, else, simulate n agents"	        , true	 , 0	 , "lone");
    cmd.add(numAgents);
    cmd.add(mcSteps);
    cmd.add(burnIn);
    cmd.add(anSteps);
    cmd.add(beta);
    cmd.add(alpha);
    cmd.add(qprob);
    cmd.add(lone);
    cmd.parse(argc, argv);
    int thin = 1;
    run( numAgents.getValue(),
	 burnIn.getValue(),
	 mcSteps.getValue(),
	 anSteps.getValue(),
	 thin,
	 beta.getValue(),
	 alpha.getValue(),
	 qprob.getValue(),
	 lone.getValue()  );
    
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



void run(int n, int burn, int steps, int anSteps, int thin, double beta, double alpha, double q, int lone) {
  if (lone == 1) {
    //std::cout << "simulate LONE agent" << std::endl;
    SimSolo foo(n, beta, alpha);
    foo.metroLoop(steps, burn, anSteps, thin);
  } 
  else {
    SimMany foo(n, beta, alpha, q);
    foo.metroLoop(steps, burn, anSteps, thin); 
  }
}


