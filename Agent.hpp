/**
 * @file   Agent.hpp
 * @author Rafael Calsaverini <rafael.calsaverini@gmail.com>
 * @date   May 05 2011
 * 
 * @brief  definition of the Agent class.
 *  
 * 
 */

#include "Graph.hpp"
#include "Random.hpp"

class Agent 
{
private:
  int size;
  double alpha;
  RndGen rng;
  Graph graph;
  Graph newgraph;
  
public:
  //constructors
  Agent(int seed, double alpha_, Graph graph_)  // create an agent with a given graph
    : size(graph_.countNodes())
    , alpha(alpha_)
    , rng(seed)
    , graph(graph_)
    , newgraph(graph_) {};    

  Agent(int size_, int seed, double alpha_)		// create an agent with standard graph. mode: 0 - full graph, j>0 - star graph centered at j 
    : size(size_)
    , alpha(alpha_)
    , rng(seed)
    , graph(size_)
    , newgraph(size_) {};

  Agent(int size_, int seed, double alpha_, int center_) 	// create an agent with standard graph. mode: 0 - full graph, j>0 - star graph centered at j 
    : size(size_)
    , alpha(alpha_)
    , rng(seed)
    , graph(size_, center_)
    , newgraph(size_, center_) {};
  
  Agent(int size_, int seed, double alpha_, double p)            //  create an agent with an Erdos-Renyi(p) graph
    : size(size_)
    , alpha(alpha_)
    , rng(seed)
    , graph(size_, p)
    , newgraph(size_, p) {};

  //other methods
  void setEdge(int i, int j, int value);						//set edge (i,j) to disconnected if value = 0, connected if value = 1
  int  getEdge(int i, int j);								//get edge status: 0 if unconnected, 1 if connected
  double energy();									// calculate energy = Nedges + alpha * avgPathLength
  double propose(int flips);            			                        // propose a new graph for the monte carlo algorithm by randomly fliping a number of edges, returns the energy of the new graph. 
  void accept();									// accept the proposed graph  
  void reject();                                                                        // reject the proposed graph
  Graph getGraph();
  std::vector<int> degrees()       { return graph.degrees()      ;}
  double avgLength()               { return graph.avgPathLength();}
  std::vector<double> closeness()  { return graph.closeness();}
  std::vector<double> betweenness() {return graph.betweenness();}
  



// THERE'S NO NEED OF RESOURCE MANAGEMENT - DEFAULT COPY CTOR, ASSIGNMENT OP AND DCTOR ARE SAFE
	// ~Agent(){};					        				//destructor
	// Agent(Agent const& other);                                                            //copy constructor
	// Agent& operator=(Agent other);							// assignment op
	// void swap(Agent& other);								//swap function for copy-and-swap assignment

};
