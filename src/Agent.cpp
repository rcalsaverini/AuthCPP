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


double Agent::propose(int flips) {
  newgraph = graph;
  int i,j,k = 0;
  int cnt = 0;
  /*while(k < flips){
    cnt++;
    rng.getIntPair(0, size - 1, i, j);
    newgraph.flipConn(i,j);
    edges = newgraph.countEdges();
    if (edges >= (size - 1)) {
      k++;
    }
    else {
      newgraph.flipEdge(i,j);
    }
  }*/

  while(k < flips) {
    //boost::tie(i,j) = rng.getIntPair(0,size-1);
    rng.getIntPair(0, size - 1, i, j);
    cnt++;
    if (newgraph.flipConn(i,j)) 
       k++;
    }
  return energycalc(alpha, newgraph); //newgraph.countEdges() + alpha * newgraph.avgPathLength();
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
