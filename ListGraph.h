#pragma once
#include "IndexOutOfBoundsException.h"
#include "FileNotFoundException.h"
#include "NotACoherentGraphException.h"
#include "QHeap.h"
#include "NodeSet.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>


class ListGraph
{
private:
	
	
	class Edge {
		friend class EdgeHeap;
		friend class ListGraph;
	private:
		Edge* next;
		Edge* prev;
		int value;
		int beg;
		int end;

		Edge();
		Edge(int val, int begN, int endN);
		~Edge();
	};
	class NodesArray {
		friend class ListGraph;
		friend std::ostream& operator << (std::ostream& output, ListGraph& graph);
	private:
		int size;
		Edge** nArray;

		NodesArray(NodesArray &temp);
		NodesArray();
		NodesArray(int nNodes);
		~NodesArray();

		void addEdge(int beg, int end, int val);
		std::string listNodeConnections(int nodeId);
	};
	class EdgeHeap {
		friend class ListGraph;
		private:
		Edge** root;
		volatile int size;
		bool isEmpty;

		EdgeHeap();
		~EdgeHeap();

		void push(Edge& edge);
		Edge pop();
		void heap_fix_up();
		void heap_fix_down();
	};

	
	int nodeNum;
	int edgeNum;
	NodesArray listGraph;

public:
	ListGraph(ListGraph &temp);
	ListGraph();
	~ListGraph();

	/* £aduje graf z pliku. Opis grafu w odpowiednim formacie:
		1. Pierwsza linijka -> iloœæ krawêdzi grafu, iloœæ wierzcho³ków
		2. Kolejne linijki -> opis kolejnych krawêdzi: pocz¹tek, koniec, waga*/
	void open(std::string fileName);
	/* Zapisuje graf do pliku w odpowiednim formacie:
		1. Pierwsza linijka -> iloœæ krawêdzi grafu, iloœæ wierzcho³ków
		2. Kolejne linijki -> opis kolejnych krawêdzi: pocz¹tek, koniec, waga*/
	void save(std::string fileName);
	void Prim(ListGraph& resultTree);
	void Kruskal(ListGraph &resultTree);
	void Dijkstra(int start, int end, bool printResult);
	bool BellmanFord(int start, int end, bool printResult);
	void multiplyEdges();
	friend std::ostream& operator << (std::ostream& output, ListGraph& graph);
};