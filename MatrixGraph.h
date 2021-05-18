#pragma once
#include "IndexOutOfBoundsException.h"
#include "FileNotFoundException.h"
#include "NotACoherentGraphException.h"
#include "QHeap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>


class MatrixGraph
{
private:
	struct Edge {
		int beg, end, val;
	};
	class Heap {
	public:

	Edge* root;
	volatile int size;
	bool isEmpty;

	Heap();
	~Heap();

	void push(Edge e);
	Edge pop();
	void heap_fix_up();
	void heap_fix_down();
	};
	int edgeNum; // Liczba krawêdzi grafu
	int nodeNum; // Liczba wierzcho³ków grafu

	int* edgeValues; // Tablica wag krawêdzi
	short int** matrixGraph; // Macierz grafu: wiersze - krawêdzie, kolumny - wierzcho³ki

public:

	MatrixGraph();
	~MatrixGraph();
	void open(std::string fileName);
	void save(std::string fileName);
	void Prim(MatrixGraph &resultTree);
	void Kruskal(MatrixGraph &resultTree);
	void Dijkstra(int start, int end, bool printResult);
	bool BellmanFord(int start, int end, bool printResult);
	void addEdge(Edge e, int idx);
	friend std::ostream& operator << (std::ostream& output, MatrixGraph& graph);
	int getNodeNum() { return nodeNum; }
};