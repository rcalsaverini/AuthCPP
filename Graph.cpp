#include "Graph.hpp"
#include <numeric>
#include <algorithm>

Graph::Graph(int size) : size(size) {
  graph = new igraph_t;
  igraph_full(graph, size, 0, 0);
}

Graph::Graph(int size, int center) : size(size){ 
  graph  = new igraph_t;
  igraph_star(graph, size, IGRAPH_STAR_UNDIRECTED, center);   
}

Graph::Graph(int size, double p) : size(size){ 
  graph  = new igraph_t;
  igraph_erdos_renyi_game(graph, IGRAPH_ERDOS_RENYI_GNP, size, p, 0, 0);
}


Graph::~Graph() {
  igraph_destroy(graph);
  delete graph;
}

Graph::Graph(Graph const& other) : size(other.size), graph(new igraph_t) {
  igraph_copy(graph, other.graph);
}  

Graph& Graph::operator=(Graph other) {  
   other.swap(*this); 
   return *this; 
}  

void Graph::swap(Graph& other) {
  std::swap(size, other.size);
  std::swap(graph, other.graph);
}

bool Graph::isConnected() {
  int errorMSG;
  igraph_bool_t res;
  errorMSG =  igraph_is_connected(graph, &res, IGRAPH_STRONG);
  return bool(res);
}

bool Graph::areConnected(int i, int j) {
  int errorMSG;
  igraph_bool_t res;
  errorMSG = igraph_are_connected(graph, i, j,&res);
  return bool(res);
}

void Graph::addEdge(int i, int j) {
  if (not areConnected(i,j))
    igraph_add_edge(graph, i, j);
}

void Graph::delEdge(int i, int j) {
  if (areConnected(i,j))
    {
      igraph_integer_t eid;
      igraph_es_t es;
      igraph_get_eid(graph, &eid, i,j,0);
      es = igraph_ess_1(eid);
      igraph_delete_edges(graph, es);
    }
}

void Graph::flipEdge(int i, int j) {
  areConnected(i,j) ? delEdge(i,j):addEdge(i,j);
}

bool Graph::flipConn(int i, int j) {
  if (not areConnected(i,j))
    addEdge(i,j);
  else {
    delEdge(i,j);
    if (not isConnected()) {
      addEdge(i,j);
      return false;
    }
  }
  return true;
}

double Graph::avgPathLength() {
  igraph_real_t res;
  igraph_average_path_length(graph, &res, 0, 0);
  return ((double) res);
} 


std::vector<int> Graph::degrees() {
  igraph_vector_t results;
  igraph_vs_t allnds;
  std::vector<int> degs;
  igraph_vs_all(&allnds);
  igraph_vector_init(&results, size);
  igraph_vector_null(&results);
  igraph_degree(graph, &results, allnds, IGRAPH_ALL, IGRAPH_NO_LOOPS);
  degs.insert(degs.begin(), VECTOR(results), VECTOR(results)+size);
  igraph_vector_destroy(&results);
  igraph_vs_destroy(&allnds);
  return degs;
}

std::vector<double> Graph::closeness() {
  igraph_vector_t results;
  igraph_vs_t allnods;
  std::vector<double> clos;
  igraph_vector_init(&results, size);
  igraph_vector_null(&results);
  igraph_vs_all(&allnods);
  igraph_closeness(graph, &results, allnods, IGRAPH_IN);
  clos.insert(clos.begin(), VECTOR(results), VECTOR(results) + size);
  igraph_vector_destroy(&results);
  igraph_vs_destroy(&allnods);
  return clos;
}

std::vector<double> Graph::betweenness() {
  igraph_vector_t results;
  igraph_vs_t allnods;
  std::vector<double> bet;
  igraph_vector_init(&results, size);
  igraph_vector_null(&results);
  igraph_vs_all(&allnods);
  igraph_betweenness(graph, &results, allnods, false);
  bet.insert(bet.begin(), VECTOR(results), VECTOR(results) + size);
  igraph_vector_destroy(&results);
  igraph_vs_destroy(&allnods);
  return bet;
}

