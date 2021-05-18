#include "ListGraph.h"
#include "MatrixGraph.h"
#include "RandGraphGen.h"
#include "Menu.h"


int main() {
	RandGraphGen gen = *(new RandGraphGen(6, 100, 5, true));
	gen.generate();
	gen.saveToFile("RANDGRAPH");

	MatrixGraph mxg = *(new MatrixGraph());
	ListGraph lsg = *(new ListGraph());

	mxg.open("RANDGRAPH");
	lsg.open("RANDGRAPH");

	Menu mainMenu = *(new Menu());
	{
	mainMenu.add("MENU GLOWNE");
	mainMenu.add("Przy uruchomieniu programu generowany jest automatycznie plik z grafem\n"
				"(\"RANDGRAPH.txt\")o 6 wierzcholkach, gestosci 100% i zakresie\n"
				"wag krawedzi od 0 do 5 .");
	mainMenu.add("***************************************************************************\n\n(r) Odswiez widok menu.");
	mainMenu.add("(w) Wczytaj graf z pliku.");
	mainMenu.add("(g) Wygeneruj nowy graf losowy.");
	mainMenu.add("(z) Zapisz bierzacy graf do pliku.");
	mainMenu.add("(p) Wydrukuj reprezentacje grafu na ekran.");
	mainMenu.add("\n***Wybierz algorytm:***");
	mainMenu.add("(1) Algorytm Prima dla reprezentacji macierzowej");
	mainMenu.add("(2) Algorytm Prima dla reprezentacji listowej");
	mainMenu.add("\n(3) Algorytm Kruskala dla reprezentacji macierzowej.");
	mainMenu.add("(4) Algorytm Kruskala dla reprezentacji listowej");
	mainMenu.add("\n(5) Algorytm Dijkstry dla reprezentacji macierzowej.");
	mainMenu.add("(6) Algorytm Dijkstry dla reprezentacji listowej");
	mainMenu.add("\n(7) Algorytm Bellmana-Forda dla reprezentacji macierzowej.");
	mainMenu.add("(8) Algorytm Bellmana-Forda dla reprezentacji listowej");
	mainMenu.add("\n(k) Zakoncz program...");}

	bool end = false;
	bool bad_command = false;
	std::cout << mainMenu;
	while (!end) {


		if (bad_command)
		{
			std::cout << "Bledny numer opcji! Twoj wybor-> ";
			bad_command = false;
		}
		else
			std::cout << "\nTwoj wybor -> ";

		std::cin.clear();
		std::cin.sync();

		char decision;
		std::cin >> decision;


		switch (decision) {
		case 'r': {
			//odswiez ekran
			system("cls");
			std::cout << mainMenu;
			break;
		}
				  //³adowanie grafu z pliku
		case 'w': {
			std::cout << "\nPodaj nazwe pliku z danymi ( w sciezce dostepu zamien \\ na \\\\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			try {
				mxg.open(nazwa);
				lsg.open(nazwa);
			}
			catch (std::runtime_error ex) {
				std::cout << "\nBLAD!" << ex.what();
				break;
			}
			std::cout << "\nPlik odczytany poprawnie\n";
			break;
		}
				  //generowanie nowego grafu losowego
		case 'g': {

			std::cout << "\n\nPodaj liczbe wierzcholkow -> ";
			int v;
			std::cin >> v;

			int d;
			std::cout << "\nPodaj gestosc grafu -> ";
			std::cin >> d;

			int r;
			std::cout << "\nPodaj maksymalna wage krawedzi -> ";
			std::cin >> r;

			gen = *(new RandGraphGen(v, d, r, true));
			gen.generate();
			gen.saveToFile("RANDGRAPH");

			mxg.open("RANDGRAPH");
			lsg.open("RANDGRAPH");
			std::cout << "\nWygenerowano graf losowy i wczytano do reprezentacji.\n";
			break;
		}
				  //zapisz graf do pliku
		case 'z': {
			std::cout << "\nKtory graf chcesz zapisac?\n(0) - reprezentacja w macierzy incydencji\n(1) - reprezentacja listowa\nTwoj wybor -> ";

			int w;
			std::cin >> w;

			if (w != 0 && w != 1) {
				std::cout << "\nBledny numer opcji!";
				break;
			}

			std::cout << "\nPodaj nazwe pliku do zapisu( w sciezce dostepu zamien \\ na \\\\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			if (w == 0)
				mxg.save(nazwa);
			else
				lsg.save(nazwa);

			std::cout << "\nChyba udalo sie zapisac, ale kto wie...\n";
			break;
		}
				  //Wydrukowanie reprezentacji grafu na ekran
		case 'p': {
			std::cout << "\nKtory graf chcesz wydrukowac?\n(0) - reprezentacja w macierzy incydencji\n(1) - reprezentacja listowa\nTwoj wybor -> ";

			int w;
			std::cin >> w;

			if (w != 0 && w != 1) {
				std::cout << "\nBledny numer opcji!";
				break;
			}
			if (w == 0)
				std::cout << mxg;
			else
				std::cout << lsg;
			break;
		}
				  //Prim macierz
		case '1': {
			
			std::cout << "\n\n***Algorytm Prima dla reprezentacji macierzowej***\n";
			MatrixGraph res = *(new MatrixGraph());
			std::cout << "Graf wyjsciowy:\n" << mxg;
			try {
				mxg.Prim(res);
				res.save("PrimMacierzWynik");
				std::cout << res << std::endl;
				std::cout << "Wynik zapisano do pliku \"PrimMacierzWynik.txt\"\n\n";
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  //Prim lista
		case '2': {
			
			std::cout << "\n\n***Algorytm Prima dla reprezentacji listowej***\n";
			ListGraph res = *(new ListGraph());
			std::cout << "Graf wyjsciowy:\n" << lsg;
			try {
				lsg.multiplyEdges();
				lsg.Prim(res);
				res.save("PrimListaWynik");
				std::cout << res << std::endl;
				std::cout << "Wynik zapisano do pliku \"PrimListaWynik.txt\"\n\n";
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}

			break;
		}
				  //Kruskal macierz
		case '3': {
			std::cout << "\n\n***Algorytm Kruskala dla reprezentacji macierzowej***\n";
			MatrixGraph res = *(new MatrixGraph());
			std::cout << "Graf wyjsciowy:\n" << mxg;
			try {
				mxg.Kruskal(res);
				std::cout << res << std::endl;
				res.save("KruskalMacierzWynik");
				std::cout << "Wynik zapisano do pliku \"KruskalMacierzWynik.txt\"\n\n";
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  //Kruskal lista
		case '4': {
			std::cout << "\n\n***Algorytm Kruskala dla reprezentacji listowej***\n";
			std::cout << "Graf wyjsciowy:\n" << lsg;
			
			ListGraph res = *(new ListGraph());
			try {
				lsg.Kruskal(res);
				std::cout << res << std::endl;
				res.save("KruskalListaWynik");
				std::cout << "Wynik zapisano do pliku \"KruskalListaWynik.txt\"\n\n";
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  //Dijkstra macierz
		case '5': {
			int beg, end;
			std::cout << "Podaj wierzcholek startowy: ";
			std::cin >> beg;
			std::cout << "\nPodaj wierzcholek koncowy: ";
			std::cin >> end;
			std::cout << "\n\n***Algorytm Dijkstry dla reprezentacji macierzowej***\n";
			std::cout << "Graf wyjsciowy:\n" << mxg;
			MatrixGraph res = *(new MatrixGraph());
			try {	
				mxg.Dijkstra(beg, end, true);
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  //Dijkstra lista
		case '6': {
			int beg, end;
			std::cout << "Podaj wierzcholek startowy: ";
			std::cin >> beg;
			std::cout << "\nPodaj wierzcholek koncowy: ";
			std::cin >> end;
			std::cout << "\n\n***Algorytm Dijkstry dla reprezentacji listowej***\n";
			std::cout << "Graf wyjsciowy:\n" << lsg;
			ListGraph res = *(new ListGraph());
			try {
				lsg.Dijkstra(beg, end, true);
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  //Bellman-Ford macierz
		case '7': {
			int beg, end;
			std::cout << "Podaj wierzcholek startowy: ";
			std::cin >> beg;
			std::cout << "\nPodaj wierzcholek koncowy: ";
			std::cin >> end;
			std::cout << "\n\n***Algorytm Bellmana-Forda dla reprezentacji macierzowej***\n";
			std::cout << "Graf wyjsciowy:\n" << lsg;
			MatrixGraph res = *(new MatrixGraph());
			try {
				mxg.BellmanFord(beg, end, true);
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  //Bellman-Forf lista
		case '8': {
			int beg, end;
			std::cout << "Podaj wierzcholek startowy: ";
			std::cin >> beg;
			std::cout << "\nPodaj wierzcholek koncowy: ";
			std::cin >> end;
			std::cout << "\n\n***Algorytm Bellmana-Forda dla reprezentacji listowej***\n";
			std::cout << "Graf wyjsciowy:\n" << lsg;
			ListGraph res = *(new ListGraph());
			try {	
				lsg.BellmanFord(beg, end, true);
			}
			catch (std::runtime_error err) {
				std::cout << "\n" << err.what() << "\n";
			}
			break;
		}
				  
				  
				  
		case 'k': {
			end = true;
			break;
		}
		default:
			bad_command = true;

		}
	}
	
	return 0;
}