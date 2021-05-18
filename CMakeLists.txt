cmake_minimum_required(VERSION 3.17)
project(SDIZO_PROJECT2)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDIZO_PROJECT2 mainprog.cpp FileNotFoundException.cpp IndexOutOfBoundsException.cpp ListGraph.cpp MatrixGraph.cpp Menu.cpp MenuElement.cpp NodeSet.cpp NotACoherentGraphException.cpp QHeap.cpp Test.cpp)