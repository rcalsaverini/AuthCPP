#include <iostream>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>


//#include "Graph.hpp"
//#include "Random.hpp"
//#include "Agent.hpp"
#include "Sim.hpp"


//void testRnd();
//void testGraph();
//void testAgent();
void testSim();

int main(){
  //testRnd();
  //testGraph();
  //testAgent();
  testSim();
  return 0;
}



void testSim(){
  double u, alpha, beta = 5.0;
  int mcSteps = 10000, n = 10, h = 100;
  for(int j = 0; j < 10; j++){
    //n = 10 + j;
    mcSteps = 10000*(j+1);
    for(int k = 1; k < h ; k++){
      Results res;
      u = 2*double(k)/double(h);
      alpha = u * n * (n-1)/2.0;
      SimSolo sim(n, beta, alpha);
      sim.metroLoop(mcSteps, mcSteps/10, res); 
      
      std::cout << u  << " ";					//1
      std::cout << 0.5*(sqrt(8.0*alpha+1.0)+1.0) << " ";	//2
      std::cout << mcSteps << " ";                                    //3
      std::cout << res.avgEnergy() << " ";			//4
      std::cout << res.varEnergy() << " ";			//5
      std::cout << res.avgLength() << " ";			//6
      std::cout << res.varLength() << " ";			//7
      std::cout << res.avgAcceptance() << " ";			//8
      std::cout << res.varAcceptance() << " ";			//9
    
      std::cout << res.avgMaxDeg() << " ";			//10
      std::cout << res.varMaxDeg() << " ";			//11
      std::cout << res.avgAvgDeg() << " ";			//12
      std::cout << res.varAvgDeg() << " ";			//13
      
      std::cout << res.avgMaxCen() << " ";			//14
      std::cout << res.varMaxCen() << " ";			//15
      std::cout << res.avgAvgCen() << " ";			//16
      std::cout << res.varAvgCen() << " ";			//17
      std::cout << std::endl;
    }
  }
}

// void testRnd(){
//   RndGen  rng(124);
//   int foo = 0;
//   int n = 100000;
//   for(int i = 0; i < n; i++) {
//     foo += rng.getRndInt(0,1);
//   }
//   std::cout << double(foo)/double(n) << std::endl;
// }

// void testAgent(){
//   int n = 20, seed = 5235, center = 0;
//   double alpha = 1000.0, E0, E;
//   Agent foo(n, seed, alpha,center);
//   RndGen rng(213);
//   E0 = foo.energy();
//   for(int i = 1; i < 100000; ++i){
//     E = foo.propose(1);
//     foo.accept();
//     std::cout << i << " " << E << " " << std::endl;
//   }

// }



// void testGraph() {
//   // variable declaration
//   Graph teste(20);
//   RndGen rng(10);
//   std::vector<int> degs;
//   int k,l;
    
//   // main loop
//   for(int i = 1; i < 1000000; i++){
//     boost::tie(k,l) = rng.getIntPair(0,19);
//     teste.flipEdge(0,1);
//     degs = teste.degrees();
//     std::cout << teste.avgPathLength() << std::endl;
//   }

// }


