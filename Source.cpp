//#include "MatrixGraph.h"
//#include "ListGraph.h"
//#include "RandGraphGen.h"
//
//int ma() {
//
//	const int v_num = 5;
//	const int dens_num = 4;
//
//	int V[5] = { 25, 50, 100, 200, 500 };
//	int dens[4] = { 25, 50, 75, 99 };
//
//	char* dir = "C:\\Users\\Piotrek\\Documents\\Visual Studio 2015\\Projects\\Algorytmy grafowe - SDiZO 2\\Algorytmy grafowe - SDiZO 2\\Testy\\graf_";
//
//	for (int i = 0; i < v_num; i++) {
//		int v = V[i];
//		for (int j = 0; j < dens_num; j++) {
//			int d = dens[j];
//			for (int i = 0; i < 100; i++) {
//				RandGraphGen gen = *(new RandGraphGen(v, d, v, true));
//				gen.generate();
//				std::string file = "";
//				file.append(dir);
//				std::stringstream ss;
//				ss << "v" << v << "_d" << d << "%_nr" << i << ".txt";
//				file.append(ss.str());
//				gen.saveToFile(file);
//				std::cout<<"Utworzono plik testowy: graf_" << "v" << v << "_d" << d << "%_nr" << i << ".txt\n";
//			}
//			std::cout << std::endl;
//		}
//	}
//	return 0;
//}