//#include "MatrixGraph.h"
//#include "ListGraph.h"
//#include "RandGraphGen.h"
//
//int ma() {
//
//	//RandGraphGen gen = *(new RandGraphGen(7, 100, 5, true));
//	//gen.generate();
//	//gen.saveToFile("testPrimKruskal");
//
//	ListGraph mxg = *(new ListGraph());
//	ListGraph mxgW1 = *(new ListGraph());
//	ListGraph mxgW2 = *(new ListGraph());
//
//	mxg.open("testPrimKruskal");
//	std::cout << mxg << std::endl;
//
//	std::cout << "Prim:\n";
//	try {
//		mxg.Prim(mxgW1);
//		std::cout << mxgW1 << std::endl;
//	}
//	catch (std::runtime_error err) {
//		std::cout << err.what() <<std::endl;
//	}
//
//
//	std::cout << "Kruskal:\n";
//	try {
//		mxg.Kruskal(mxgW2);
//		std::cout << mxgW2 << std::endl;
//	}
//	catch (std::runtime_error err) {
//		std::cout << err.what() << std::endl;
//	}
//
//
//  	std::cin.get();
//	return 0;
}