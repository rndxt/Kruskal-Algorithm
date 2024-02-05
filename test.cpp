#include "test.h"

#include "testDisjointSet.h"
#include "testGraph.h"

#include <iostream>

void NSProject::runAllTests() {
  std::cout << "Run tests:" << std::endl;

  NSTestsDSU::testCorrectInitialization();
  NSTestsDSU::testFind();
  NSTestsDSU::testJoin();

  NSTestsGraph::testEdgeOrdering();
  NSTestsGraph::testDefaultGraph();
  NSTestsGraph::testAddEdge();
  NSTestsGraph::testRemoveEdge();
  NSTestsGraph::testMST();

  std::cout << "Done" << std::endl;
}
