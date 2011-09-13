#include "../include/Agent.hpp"
#include <algorithm>
#include <boost/tuple/tuple.hpp>

double energycalc(double alpha, const Graph &gr){
  int edges = gr.countEdges();
  double length = gr.avgPathLength();
  //  std::cout << edges << " " << length << std::endl;
  double efit = edges + alpha * length;
  return efit;
} 

void Agent::setEdge(int i, int j, int value) {
  bool isc = graph.areConnected(i,j);
  if ((not isc) && (value == 1))
    graph.addEdge(i,j);
  else if ((isc) && (value == 0))
    graph.delEdge(i,j);
}

int Agent::getEdge(int i, int j) {
  return int(graph.areConnected(i,j));
}

double Agent::energy() {
  return energycalc(alpha, graph);
}


double Agent::propose(int flips, int k, int l) {
  newgraph = graph;
  int  i,j,k = 0;
  int  edges = 0;
  while(true){
    rng.getIntPair(0, size - 1, i, j);
    newgraph.flipEdge(i,j);
    edges = newgraph.countEdges();
    if (edges < (size - 1)) {
      newgraph.flipEdge(i,j);
    }
    else{
      break;
    }
  }

  return (newgraph.countEdges() + alpha * newgraph.avgPathLength());
  /*while(k < flips) {
  //boost::tie(i,j) = rng.getIntPair(0,size-1);
  rng.getIntPair(0, size - 1, i, j);
  
  //if (newgraph.flipConn(i,j)) 
  k++;
  }*/
}

void Agent::accept() {
  graph = newgraph;
}

void Agent::reject() {
  newgraph = graph;
}

/*Graph Agent::getGraph(){ 
  return graph;
  }*/
