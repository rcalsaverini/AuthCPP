#include "Agent.hpp"
#include <algorithm>
#include <boost/tuple/tuple.hpp>

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
  return graph.countEdges() + alpha * graph.avgPathLength();
}


double Agent::propose(int flips) {
  newgraph = graph;
  int i,j,k = 0;
  while(k < flips) {
    //boost::tie(i,j) = rng.getIntPair(0,size-1);
    rng.getIntPair(0, size - 1, i, j);
    if (newgraph.flipConn(i,j)) 
      k++;
  }
  return newgraph.countEdges() + alpha * newgraph.avgPathLength();
}

void Agent::accept() {
  graph = newgraph;
}

void Agent::reject() {
  newgraph = graph;
}

Graph Agent::getGraph(){ 
  return graph;
}
