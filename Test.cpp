#include "MatrixGraph.h"
#include "ListGraph.h"
#include "RandGraphGen.h"
#include <Windows.h>
#include <time.h>


LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		stop;
}

int maintest() {
	const int pomiary = 100;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	const int v_num = 5;
	const int dens_num = 4;

	int V[5] = { 25, 50, 100, 200, 500 };
	int dens[4] = { 25, 50, 75, 99 };

	long double wynikiPrimMatrix[pomiary];
	long double wynikiDijkstraMatrix[pomiary];
	long double wynikiPrimLista[pomiary];
	long double wynikiDijkstraLista[pomiary];
	long double wynikiKruskalMatrix[pomiary];
	long double wynikiBellmanMatrix[pomiary];
	long double wynikiKruskalLista[pomiary];
	long double wynikiBellmanLista[pomiary];

	long double primMatrix[dens_num];
	long double primLista[dens_num];
	long double dijkMatrix[dens_num];
	long double dijkLista[dens_num];
	long double kruskalMatrix[dens_num];
	long double kruskalLista[dens_num];
	long double bellmanMatrix[dens_num];
	long double bellmanLista[dens_num];

	for (int i = 0; i < dens_num; i++) {
			
		primMatrix[i] = 0;
		primLista[i] = 0;
		dijkMatrix[i] = 0;
		dijkLista[i] = 0;
		kruskalMatrix[i] = 0;
		kruskalLista[i] = 0;
		bellmanMatrix[i] = 0;
		bellmanLista[i] = 0;
	}

	char* dirPrim = "prim_";
	char* dirDijk = "dijk_";
	char* dirKrus = "krus_";
	char* dirBell = "bell_";

	char* open = "C:\\Users\\Piotrek\\Documents\\Visual Studio 2015\\Projects\\Algorytmy grafowe - SDiZO 2\\Algorytmy grafowe - SDiZO 2\\Testy\\graf_";

	for (int i = 0; i < v_num; i++) {
		int v = V[i];
		for (int j = 0; j < dens_num;j++) {
			
			int d = dens[j];
			LARGE_INTEGER countStart, countEnd;

			for (int k = 0;k < pomiary;k++) {
				
				
				MatrixGraph mxg = *(new MatrixGraph());
				MatrixGraph mxgW = *(new MatrixGraph());
				
				ListGraph lsg = *(new ListGraph());
				ListGraph lsgW = *(new ListGraph());

				std::string file = "";
				file.append(open);
				std::stringstream ss;
				ss << "v" << v << "_d" << d << "%_nr" << k << ".txt";
				file.append(ss.str());

				mxg.open(file);
				lsg.open(file);

				/*Algorytm Prima - reprezentacja macierzowa*/
				//countStart = startTimer();
				//mxg.Prim(mxgW);
				//countEnd = endTimer();

				//wynikiPrimMatrix[k] = ((double)(countEnd.QuadPart - countStart.QuadPart))/freq.QuadPart;

				//lsg.multiplyEdges();
				/*Algorytm Prima - reprezentacja listowa*/
				//countStart = startTimer();
				//lsg.Prim(lsgW);
				//countEnd = endTimer();

				//lsg.open(file);
				//wynikiPrimLista[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;

				/*Algorytm Kruskala - reprezentacja macierzowa*/
				countStart = startTimer();
				mxg.Kruskal(mxgW);
				countEnd = endTimer();

				wynikiKruskalMatrix[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;
				
				/*Algorytm Kruskala - reprezentacja listowa*/
				countStart = startTimer();
				lsg.Kruskal(lsgW);
				countEnd = endTimer();

				wynikiKruskalLista[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;

				/*Algorytm Dijkstry - reprezentacja macierzowa*/
				//countStart = startTimer();
				//mxg.Dijkstra(0,false);
				//countEnd = endTimer();

				//wynikiDijkstraMatrix[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;

				/*Algorytm Dijkstry - reprezentacja listowa*/
				//countStart = startTimer();
				//lsg.Dijkstra(0,false);
				//countEnd = endTimer();

				//wynikiDijkstraLista[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;

				/*Algorytm Bellmana-Forda - reprezentacja macierzowa*/
				//countStart = startTimer();
				//mxg.BellmanFord(0, false);
				//countEnd = endTimer();

				//wynikiBellmanMatrix[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;

				/*Algorytm Bellmana-Forda - reprezentacja listowa*/
				//countStart = startTimer();
				//lsg.BellmanFord(0, false);
				//countEnd = endTimer();

				//wynikiBellmanLista[k] = ((double)(countEnd.QuadPart - countStart.QuadPart)) /freq.QuadPart;

				std::cout << "Zmierzono czas dla " << "v" << v << "d" << d << "\n";
			}

			

			for (int k = 0; k < pomiary; k++) {
				primMatrix[j] += wynikiPrimMatrix[k];
				primLista[j] += wynikiPrimLista[k];
				dijkMatrix[j] += wynikiDijkstraMatrix[k];
				dijkLista[j] += wynikiDijkstraLista[k];
				kruskalMatrix[j] += wynikiKruskalMatrix[k];
				kruskalLista[j] += wynikiKruskalLista[k];
				bellmanMatrix[j] += wynikiBellmanMatrix[k];
				bellmanLista[j] += wynikiBellmanLista[k];
			}

			primMatrix[j] = primMatrix[j] / pomiary;
			primLista[j] = primLista[j] / pomiary;
			dijkMatrix[j] = dijkMatrix[j] / pomiary;
			dijkLista[j] = dijkLista[j] / pomiary;
			kruskalMatrix[j] = kruskalMatrix[j] / pomiary;
			kruskalLista[j] = kruskalLista[j] / pomiary;
			bellmanMatrix[j] = bellmanMatrix[j] / pomiary;
			bellmanLista[j] = bellmanLista[j] / pomiary;
		}

		/*-----------Utworzenie nazwy pliku-------------*/
		std::fstream plikPM;
		std::fstream plikDM;
		std::fstream plikPL;
		std::fstream plikDL;
		std::fstream plikKM;
		std::fstream plikKL;
		std::fstream plikBM;
		std::fstream plikBL;

		std::stringstream ssPrimM;
		std::stringstream ssDijkM;
		std::stringstream ssPrimL;
		std::stringstream ssDijkL;
		std::stringstream ssKrusM;
		std::stringstream ssBellM;
		std::stringstream ssKrusL;
		std::stringstream ssBellL;
		std::string buf;

		std::string nazwaPrimM ="";
		std::string nazwaDijkM = "";
		std::string nazwaPrimL = "";
		std::string nazwaDijkL = "";
		std::string nazwaKrusM = "";
		std::string nazwaBellM = "";
		std::string nazwaKrusL = "";
		std::string nazwaBellL = "";

		nazwaPrimM.append(dirPrim);
		nazwaDijkM.append(dirDijk);
		nazwaPrimL.append(dirPrim);
		nazwaDijkL.append(dirDijk);
		nazwaKrusM.append(dirKrus);
		nazwaBellM.append(dirBell);
		nazwaKrusL.append(dirKrus);
		nazwaBellL.append(dirBell);

		ssPrimM << "v_" << v << "_matrix.txt";
		ssDijkM << "v_" << v << "_matrix.txt";
		ssPrimL << "v_" << v << "_list.txt";
		ssDijkL << "v_" << v << "_list.txt";
		ssKrusM << "v_" << v << "_matrix.txt";
		ssBellM << "v_" << v << "_matrix.txt";
		ssKrusL << "v_" << v << "_list.txt";
		ssBellL << "v_" << v << "_list.txt";

		nazwaPrimM.append(ssPrimM.str());
		nazwaDijkM.append(ssDijkM.str());
		nazwaPrimL.append(ssPrimL.str());
		nazwaDijkL.append(ssDijkL.str());
		nazwaKrusM.append(ssKrusM.str());
		nazwaBellM.append(ssBellM.str());
		nazwaKrusL.append(ssKrusL.str());
		nazwaBellL.append(ssBellL.str());
		

		/*plikPM.open(nazwaPrimM, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikPM << primMatrix[i] << ";";
		plikPM.close();

		plikDM.open(nazwaDijkM, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikDM << dijkMatrix[i] << ";";
		plikDM.close();

		plikPL.open(nazwaPrimL, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikPL << primLista[i] << ";";
		plikPL.close();

		plikDL.open(nazwaDijkL, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikDL << dijkLista[i] << ";";
		plikDL.close();
		*/
		plikKM.open(nazwaKrusM, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikKM << kruskalMatrix[i] << ";";
		plikKM.close();

		/*plikBM.open(nazwaBellM, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikBM << bellmanLista[i] << ";";
		plikBM.close();*/

		plikKL.open(nazwaKrusL, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikKL << kruskalLista[i] << ";";
		plikKL.close();

		/*plikBL.open(nazwaBellL, std::ios::out);
		for (int i = 0; i < 4; i++)
			plikBL << bellmanLista[i] << ";";
		plikBL.close();*/

	}
	return 0;
}