#include <iostream>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>


//#include "Graph.hpp"
//#include "Random.hpp"
//#include "Agent.hpp"
#include "Sim.hpp"


void testRnd();
void testGraph();
void testAgent();
void testSim();


int main(){
  //testRnd();
  //testGraph();
  //testAgent();
  testSim();
  return 0;
}

void testSim(){
  double beta = 5;
  double u, alpha;
  //double E, vE, avg, max,accept;
  int mcSteps = 300000, n = 20, h = 100;
  //SimSolo sim(n,beta,alpha);
  //sim.metroLoop(10000, 0, true, E, vE, avg, max,accept);
  for(int k = 1; k < h ; k++){
    u = 2*double(k)/double(h);
    alpha = u * n * (n-1)/2.0;
    std::cout << u  << " " <<  0.5*(sqrt(8.0*alpha+1.0)+1.0) << " ";
    SimSolo sim(n, beta, alpha);
    sim.metroRun(5, mcSteps, 2 * mcSteps/10);
    //std::cout << "\n";
    }
}
  //std::vector<int> ns(10,0);
void testRnd(){
  RndGen  rng(124);
  int foo = 0;
  int n = 100000;
  for(int i = 0; i < n; i++) {
    foo += rng.getRndInt(0,1);
  }
  std::cout << double(foo)/double(n) << std::endl;
}

void testAgent(){
  int n = 20, seed = 5235, center = 0;
  double alpha = 1000.0, E0, E;
  Agent foo(n, seed, alpha,center);
  RndGen rng(213);
  E0 = foo.energy();
  for(int i = 1; i < 100000; ++i){
    E = foo.propose(1);
    foo.accept();
    std::cout << i << " " << E << " " << std::endl;
  }

}



void testGraph() {
  // variable declaration
  Graph teste(20);
  RndGen rng(10);
  std::vector<int> degs;
  int k,l;
    
  // main loop
  for(int i = 1; i < 1000000; i++){
    boost::tie(k,l) = rng.getIntPair(0,19);
    teste.flipEdge(0,1);
    degs = teste.degrees();
    std::cout << teste.avgPathLength() << std::endl;
  }

}


