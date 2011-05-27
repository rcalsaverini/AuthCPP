/**
 * @file   Graph.hpp
 * @author Rafael Calsaverini <rafael.calsaverini@gmail.com>
 * @date   May 04 2011
 * 
 * @brief  definition of the Graph class.
 *  
 * This is a wrapper of the igraph C library for use with C++. The wrapper is built only for the basic functions use the in the authority library. 
 * 
 */

#include <igraph.h>
#include <iostream>
//#include <algorithm>
#include <vector>

class Graph
{
private:
  int size;
  igraph_t * graph;
 
public:
  //constructors
  Graph(int size);					// construct fully-connected graph
  Graph(int size, int center);				// construct star-shaped graph
  Graph(int size, double p);                            // construct ER(p) graph Erdos-Renyi
  ~Graph();						// destroy graph
  Graph(Graph const& other);				// copy-constructor
  Graph& operator=(Graph other);			// assignment operator
  void swap(Graph& other);				// swap function, used for assignment with copy-and-swap idiom

  //other methods
  int countNodes() {return int(igraph_vcount(graph)); } // return number of nodes in the graph
  int countEdges() {return int(igraph_ecount(graph)); }	// return number of edges in the graph
  bool isConnected();					// return true if graph is strongly connected
  bool areConnected(int i, int j);			//return true if nodes i and j are connected
  void addEdge(int i, int j);				// safely add an edge between i and j (graph is unchanged if i and j are already connected)
  void delEdge(int i, int j);				// safely delete and edge between i and j (graph is unchanged if i and j are not connected)
  void flipEdge(int i, int j);                          // flip an edge: add edge if unconnected, del edge if connected
  bool flipConn(int i, int j);                          // flip edge (i,j) only if the result is a connected graph. Returns true if flip is succesful
  std::vector<int> degrees();                           // return a std::vector<int> with the degree of each node.
  double avgPathLength();                               // calculate the average path length
  std::vector<double> closeness();                      // determine closeness centrality for all nodes
  std::vector<double> betweenness();                    // determine betweenness centrality for all nodes
};

