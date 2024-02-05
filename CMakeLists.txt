cmake_minimum_required(VERSION 3.10)

project(Kruskal-Algorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SOURCES DisjointSet.cpp Graph.cpp)
SET(TEST_SOURCES test.cpp testDisjointSet.cpp testGraph.cpp)

add_executable(Kruskal-Algorithm main.cpp ${SOURCES} ${TEST_SOURCES})