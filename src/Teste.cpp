#include <iostream>

#include "../include/SimMany.hpp"

void testSim();
void testVec();
void testSimMany();

int main(){
  testSimMany();
  return 0;
}


void testSimMany(){
  //std::cout << "declare shit" << std::endl;
  SimMany foo(30, 1.0, 120.0, 0.0);
  //std::cout << "run shit" << std::endl;
  foo.metroLoop(10000, 0);
}

