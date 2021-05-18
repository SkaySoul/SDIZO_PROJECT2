#include "MatrixGraph.h"
#include "NodeSet.h"

/*Kopiec potrzebny do algorytmów*/
MatrixGraph::Heap::Heap()
{
	size = 0;
	isEmpty = true;
	root = nullptr;
}

MatrixGraph::Heap::~Heap()
{
	delete[] root;
}

void MatrixGraph::Heap::push(Edge e)
{
	if (size == 0) {
		/*push front*/
		size++;
		root = new Edge[size];
		root[0] = e;
		isEmpty = false;
	}

	/*push back*/
	Edge* buf = new Edge[size + 1];
	memcpy(buf, root, size*sizeof(Edge));
	size++;
	delete[] root;
	root = buf;
	root[size - 1] = e;
	heap_fix_up();
	isEmpty = false;
}

MatrixGraph::Edge MatrixGraph::Heap::pop()
{
	if (size == 0)
		throw IndexOutOfBoundsException("\nKopiec jest juz pusty! Nie mozna usunac elementu!");
	
	Edge ret = root[0];
	if (size == 1) {
		size--;
		delete[] root;
		root = nullptr;
		isEmpty = true;
		return ret;
	}

	
	root[0] = root[size - 1];//ostatni liœæ na miejsce korzenia
	size--;
	Edge* buf = new Edge[size];
	memcpy(buf, root, size*sizeof(Edge));
	delete[] root;
	root = buf;
	heap_fix_down();
	return ret;
}

void MatrixGraph::Heap::heap_fix_up()
{
	int i = this->size - 1;
	int parent = (i - 1) / 2;
	while (root[parent].val > root[i].val) {
		Edge bufor = root[parent];

		root[parent] = root[i];
		root[i] = bufor;

		i = parent;
		parent = (i - 1) / 2;
	}
}

void MatrixGraph::Heap::heap_fix_down()
{

	int i = 0; // zaczynamy od korzenia
	int j = 2 * i + 1;

	while (j < size) {
		//szukam wiêkszego syna
		if (j + 1 < size && (root[j].val > root[j + 1].val))
			j += 1;

		if (root[i].val <= root[j].val)
			break;

		Edge buf = root[i];
		root[i] = root[j];
		root[j] = buf;
		i = j;
		j = 2 * i + 1;
	}

}


MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < edgeNum; i++) {
		delete[] matrixGraph[i];
	}
	
	delete[] matrixGraph;
	delete[] edgeValues;
}

MatrixGraph::MatrixGraph()
{
	edgeNum = 0;
	nodeNum = 0;

	edgeValues = nullptr;
	matrixGraph = nullptr;
}

void MatrixGraph::open(std::string fileName)
{	
	/* Sprawdzam, czy w nazwie pliku brakuje rozszerzenia ".txt", jeœli tak to je dodajê.*/
	if (fileName[fileName.length() - 1] != *"t" ||
		fileName[fileName.length() - 2] != *"x" ||
		fileName[fileName.length() - 3] != *"t" ||
		fileName[fileName.length() - 4] != *".")
		fileName.append(".txt");

	/* Tworzê strumieñ do odczytu danych z pliku.
	Otwieram go w trybie "std::ios::in", czyli do odczytu.*/
	std::fstream input;
	input.open(fileName, std::ios::in);

	/* Sprawdzam, czy powiod³o siê otwarcie pliku.*/
	if (!input.good())
		throw FileNotFoundException("\nNie ma takiego pliku!");

	std::string inputLine;

	getline(input, inputLine);

	std::istringstream* iss;
	iss = new std::istringstream(inputLine);

	/* Odczytanie linii danych zawieraj¹cej informacje
	 o liczbie krawêdzi oraz wierzcho³ków grafu*/
	try {
		*iss >> this->edgeNum; //wczytanie liczby krawêdzi
		*iss >> this->nodeNum; // oraz wierzcho³ków
	}catch (std::exception ex) {
		std::cerr << "Blad podczas wczytywania danych z pliku:\n" << ex.what();
		return;
	}
	delete iss;

	this->edgeValues = new int[edgeNum];

	this->matrixGraph = new short int*[edgeNum];

	for (int i = 0; i < edgeNum; i++) {
		this->matrixGraph[i] = new short int[nodeNum];
	}

	/* Pêtla wczytuj¹ca informacje o kolejnych krawêdziach*/
	for (int i = 0; i < edgeNum; i++) {
		
		getline(input, inputLine);
		
		iss = new std::istringstream(inputLine);
		int beg, end;
		/* Odczytanie linii danych opisuj¹cych i-t¹ krawêdŸ*/
		try {
			*iss >> beg;
			*iss >> end;
			*iss >> edgeValues[i];
		}
		catch (std::exception ex) {
			std::cerr << "Blad podczas wczytywania danych z pliku:\n" << ex.what();
			return;
		}
		
		/* Pêtla wype³niaj¹ca i-ty wiersz wed³ug wczytanych danych
		   (informajce o krawêdzi nr i) */
		for (int j = 0; j < nodeNum; j++) {
			
			if (j == beg && j == end)
				matrixGraph[i][j] = 2;
			else{
				if (j == beg)
					matrixGraph[i][j] = 1;
				else
					if (j == end)
						matrixGraph[i][j] = -1;
					else
						matrixGraph[i][j] = 0;
			}
			
		}

		delete iss;
	}

	return;
}

void MatrixGraph::save(std::string fileName)
{	
	if (fileName[fileName.length() - 1] != *"t" ||
		fileName[fileName.length() - 2] != *"x" ||
		fileName[fileName.length() - 3] != *"t" ||
		fileName[fileName.length() - 4] != *".")
		fileName.append(".txt");
	
	std::fstream output;
	output.open(fileName, std::ios::out);

	output << this->edgeNum << " " << this->nodeNum << std::endl;

	for (int i = 0; i < this->edgeNum; i++) {
		
		int beg = -1;
		int end = -1;
		/* Szukanie pocz¹tku i koñca ka¿dej krawêdzi*/
		for (int j = 0; j < this->nodeNum; j++) {
			if (this->matrixGraph[i][j] == 1)
				beg = j;
			if (this->matrixGraph[i][j] == -1)
				end = j;
			if (this->matrixGraph[i][j] == 2) {
				beg = j;
				end = beg;
				break;
			}
			if (end != -1 && beg != -1)
				break;
		}
		/* Sprawdzenie, czy znaleziono poprawnie oba koñce*/
		if (beg == -1 && end == -1) {
			std::cerr << "Blad zapisu grafu!\n";
			return;
		}
		
		output << beg << " " << end << " " << this->edgeValues[i]<<std::endl;
	}

	return;
}

void MatrixGraph::Prim(MatrixGraph & resultTree)
{
	resultTree.nodeNum = nodeNum;
	resultTree.edgeNum = nodeNum-1;
	resultTree.edgeValues = new int[resultTree.edgeNum];
	resultTree.matrixGraph = new short int*[resultTree.edgeNum];
	for (int i = 0; i < resultTree.edgeNum; i++) 
		resultTree.matrixGraph[i] = new short int[resultTree.nodeNum];
	

	if (edgeNum < nodeNum - 1)
		throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
	/* Tworzê now¹ pust¹ kolejkê priorytetow¹ na krawêdzie*/
	Heap edges = *(new Heap());
	/* Tworzê tablicê logiczna, zawieraj¹c¹ informacje o odwiedzonych wierzcho³kach*/
	bool* visited = new bool[nodeNum];
	for (int i = 0; i < nodeNum; i++)
		visited[i] = false;

	/* wybieram wierzcho³ek startowy i oznaczam jako odwiedzony*/
	int v = 0;
	visited[v] = true;
	int edges_added = 0;
	for (int i = 1; i < nodeNum;i++) {

		/* Umieszczamy w kolejce priorytetowej krawêdzie do nieodwiedzonych s¹siadów*/	
			for (int j = 0; j < edgeNum; j++) {
				
				/*Jeœli v nale¿y do j-tej krawêdzi, to szukamy drugiego koñca*/
				if (matrixGraph[j][v] == 1 || matrixGraph[j][v] == -1) {
					
					Edge e = { v, -1, edgeValues[j] };
					/*Sprawdzamy wierzcho³ki o ni¿szym numerze ni¿ v*/
					for (int k = v-1; k > 0; k--) 
						if (matrixGraph[j][k] == 1 || matrixGraph[j][k] == -1)
							e.end = k;
					

					/*Jeœli w poprzedniej pêtli nie znaleziono koñca krawêdzi,
					to sprawdzamy wierzcho³ki o wy¿szym numerze ni¿ v*/
					if (e.end == -1) {
						for (int k = v + 1; k < nodeNum; k++) {
							if (matrixGraph[j][k] == 1 || matrixGraph[j][k] == -1) {
								e.end = k;
								break;
							}
						}
					}
						
					if (visited[e.end] == false) {
						edges.push(e);
					}
				}
			}
				

		/* Dopóki krawêdŸ o najmniejszej wadze prowadzi do s¹siada juz odwiedzonego*/

			while (visited[edges.root[0].end] == true) {
				edges.pop();
				if (edges.isEmpty)
					throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
			}



		Edge e = edges.pop();
		/*Dodanie wartoœci do macierzy*/
		resultTree.addEdge(e, edges_added);
		edges_added++;
		visited[e.end] = true;
		v = e.end;
	}

	bool allVisited = true;
	for (int i = 0; i < nodeNum; i++) {
		if (visited[i] == false) {
			throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
		}
	}

	delete[] visited;
	
	return;
}

void MatrixGraph::Kruskal(MatrixGraph & resultTree)
{
	resultTree.nodeNum = nodeNum;
	resultTree.edgeNum = nodeNum - 1;
	resultTree.edgeValues = new int[resultTree.edgeNum];
	resultTree.matrixGraph = new short int*[resultTree.edgeNum];
	for (int i = 0; i < resultTree.edgeNum; i++)
		resultTree.matrixGraph[i] = new short int[resultTree.nodeNum];


	if (edgeNum < nodeNum - 1)
		throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
	
	/*Kopiec na krawêdzie, posortowane wg wagi*/
	Heap edges = *(new Heap());
	/*Pêtla dodaj¹ca kolejne krawêdzie do kopca*/
	for (int e = 0; e < edgeNum; e++) {
		
		Edge edge = { -1,-1, edgeValues[e] };

		for (int n = 0; n < nodeNum; n++) {
			
			int i = this->matrixGraph[e][n];
			if (i == 1)
				edge.beg = n;
			else
				if (i == -1)
					edge.end = n;
			if (edge.beg != -1 && edge.end != -1)
				break;
		}
		
		if(edge.beg != -1 && edge.end != -1)
			edges.push(edge);
	}


	NodeSet Z = *(new NodeSet(nodeNum));
	/*Pêtla, tworz¹ca kolejne zbiory roz³¹czne dla wszystkich wierzcho³ków*/
	for (int n = 0; n < nodeNum; n++)
		Z.makeSet(n);

	int edges_added = 0;

	for (int i = 1; i < nodeNum; i++) {
		
		Edge e;
		
		do{
		
			if (edges.isEmpty)
				throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
			e = edges.pop();

		
		} while (Z.findSet(e.beg) == Z.findSet(e.end));

		resultTree.addEdge(e, edges_added);
		edges_added++;
		Z.joinSets(e.beg, e.end);
	}
}

void MatrixGraph::Dijkstra(int start, int end, bool printResult)
{
	if (start < 0 || start >= nodeNum)
		throw IndexOutOfBoundsException("\nPodany wierzcholek startowy jest poza zakresem!!");
	if (end < 0 || end >= nodeNum)
		throw IndexOutOfBoundsException("\nPodany wierzcholek koncowy jest poza zakresem!!");
	/*Utworzenie zbioru Q (kolejki priorytetowej) z wszystkim wierzcho³kami*/
	QHeap Qset = *(new QHeap(this->nodeNum, start));
	
	/*Utworzenie tablic z kosztami dojœcia do poszczególnych wierzcho³ków
	oraz z poprzednikami. Do tego tablica logiczna, mówi¹ca o tym, którego wierzcho³ka ju¿ nie ma w Q */
	vertex* pd_tab = new vertex[nodeNum];
	bool* QS = new bool[nodeNum];

	for (int i = 0; i < nodeNum; i++) {
		
		if (i == start) 
			pd_tab[i].cost = 0;
		else
			pd_tab[i].cost = INT_MAX;
		pd_tab[i].nr = -1;
		QS[i] = false;
	}

	for (int i = 0; i < nodeNum; i++) {
		
		vertex v = Qset.pop();
		QS[v.nr] = true;

		/*Sprawdzam, czy ze szczytu kopca nie zosta³ œci¹gniêty element, który nie by³ niczyim s¹siadem.
		Jeœli tak siê sta³o, to znaczy, ¿e nie da siê juz dojœæ do ¿adnych z pozosta³ych wierzcho³ków.*/
		if (pd_tab[v.nr].nr == -1 && v.nr != start)
			break;
		
		/*Tablica dynamiczna na s¹siadów. U¿ywam struktury vertex, tylko w tym wypadku pole "cost" bêdzie oznacza³o
		koszt krawêdzi miêdzy wierzcho³kiem a s¹siadem*/
		int n_adj = 0;
		vertex* adj = new vertex[n_adj];
		
		/*Sprawdzamy wszystkie krawêdzie*/
		for (int e = 0; e < edgeNum; e++) {
			
			/*Jeœli krawêdŸ zaczyna siê w tym wierzcho³ku*/
			if (this->matrixGraph[e][v.nr] == 1) {

				/*Sprawdzamy wierzcho³ki*/
				for (int nr = 0; nr < nodeNum; nr++) {

					if (v.nr == nr)
						continue;
					/*Jeœli w tym wierzcho³ku koniec krawêdzi*/
					if (matrixGraph[e][nr] == -1) {
						/*To dodajemy go do tablicy s¹siadów*/
						vertex* buf = new vertex[n_adj+1];
						memcpy(buf, adj, n_adj*sizeof(vertex));
						buf[n_adj].nr = nr;
						buf[n_adj].cost = edgeValues[e];

						delete[] adj;
						adj = buf;
						n_adj++;
						/*Wyskakujê z pêtli iteruj¹cej po wierzcho³kach i sprawdzam kolejn¹ krawêdŸ*/
						break;
					}
				}
			}
		}

		/*W tym momencie w tablicy adj mamy wszystkich s¹siadów wierzcho³ka v*/
		for (int ad = 0; ad < n_adj; ad++) {
			/*Jeœli tego s¹siada nie ma ju¿ w Q to krêcimy dalej*/
			if (QS[adj[ad].nr] == true)
				continue;
			/* jeœli d[sasiad] > d[poprzednik] + koszt_krawedzi_miedzy_nimi */
			if (pd_tab[adj[ad].nr].cost > adj[ad].cost + pd_tab[v.nr].cost) {

				pd_tab[adj[ad].nr].cost = adj[ad].cost + pd_tab[v.nr].cost;
				pd_tab[adj[ad].nr].nr = v.nr;

				Qset.changeCost(adj[ad].nr, pd_tab[adj[ad].nr].cost);
			}
		}

	}
	
	/*Drukowanie wyników*/
	/*if (printResult) {
		std::cout << "Koszty dojscia do kolejnych wierzcholkow, startujac od wierzcholka " << start << " :" << std::endl;
		for (int i = 0; i < nodeNum; i++) {

			std::cout << "Dojscie do wierzcholka " << i << " :";

			if (i == start) {
				std::cout << " wierzcholek startowy, koszt = 0\n";
				continue;
			}
			else
				if (pd_tab[i].nr == -1) {
					std::cout << "dojscie do wierzcholka niemozliwe\n";
					continue;
				}

			std::cout << i << "<-";
			int poprzednik = pd_tab[i].nr;
			while (poprzednik >= 0) {
				std::cout << poprzednik;
				poprzednik = pd_tab[poprzednik].nr;
				if (poprzednik != -1)
					std::cout << "<-";
			}
			std::cout << ", koszt = " << pd_tab[i].cost << std::endl;
		}
	}*/

	if (printResult) {
		std::cout << "Koszt dojscia do wierzcholka " << end <<" od wierzcholka " << start << " :" << std::endl;

		if (end == start) {
			std::cout << " wierzcholek startowy, koszt = 0\n";
			delete[] pd_tab;
			delete[] QS;
			return;
		}
		else
			if (pd_tab[end].nr == -1) {
				std::cout << "dojscie do wierzcholka niemozliwe\n";
				delete[] pd_tab;
				delete[] QS;
				return;
			}

		std::cout << end << "<-";
		int poprzednik = pd_tab[end].nr;
		while (poprzednik >= 0) {
			std::cout << poprzednik;
			poprzednik = pd_tab[poprzednik].nr;
			if (poprzednik != -1)
				std::cout << "<-";
		}
		std::cout << ", koszt = " << pd_tab[end].cost << std::endl;
	}
	
	
	
	delete[] pd_tab;
	delete[] QS;
	return;
}

bool MatrixGraph::BellmanFord(int start, int end, bool printResult) 
{
	if (start < 0 || start >= nodeNum)
		throw IndexOutOfBoundsException("\nPodany wierzcholek startowy jest poza zakresem!!");
	if (end < 0 || end >= nodeNum)
		throw IndexOutOfBoundsException("\nPodany wierzcholek koncowy jest poza zakresem!!");

	/*Utworzenie tablic z kosztami dojœcia do poszczególnych wierzcho³ków
	oraz z poprzednikami. Do tego tablica logiczna, mówi¹ca o tym, którego wierzcho³ka ju¿ nie ma w Q */
	vertex* pd_tab = new vertex[nodeNum];
	//bool* QS = new bool[nodeNum];

	int* adjNum = new int[nodeNum];
	vertex** Adj = new vertex*[nodeNum];

	/*Utworzenie list s¹siedztwa*/
	for (int x = 0; x < nodeNum; x++) {
		adjNum[x] = 0;
		Adj[x] = new vertex[adjNum[x]];

		/*Sprawdzamy wszystkie krawêdzie*/
		for (int e = 0; e < edgeNum; e++) {

			/*Jeœli krawêdŸ zaczyna siê w tym wierzcho³ku*/
			if (this->matrixGraph[e][x] == 1) {

				/*Sprawdzamy wierzcho³ki*/
				for (int nr = 0; nr < nodeNum; nr++) {

					if (x == nr)
						continue;
					/*Jeœli w tym wierzcho³ku koniec krawêdzi*/
					if (matrixGraph[e][nr] == -1) {
						/*To dodajemy go do tablicy s¹siadów*/
						vertex* buf = new vertex[adjNum[x] + 1];
						memcpy(buf, Adj[x], adjNum[x]*sizeof(vertex));
						buf[adjNum[x]].nr = nr;
						buf[adjNum[x]].cost = edgeValues[e];

						delete[] Adj[x];
						Adj[x] = buf;
						adjNum[x]++;
						/*Wyskakujê z pêtli iteruj¹cej po wierzcho³kach i sprawdzam kolejn¹ krawêdŸ*/
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < nodeNum; i++) {

		if (i == start)
			pd_tab[i].cost = 0;
		else
			pd_tab[i].cost = INT_MAX;
		pd_tab[i].nr = -1;
	}

	
	bool test;
	bool* visited = new bool[nodeNum];
	for (int i = 0; i < nodeNum; i++)
		visited[i] = false;
	/*Relaksacja kolejnych krawêdzi w pêtli iteruj¹cej po wierzcho³kach*/
	bool startDone = false;
	int x = start;
	for (int i = 1; i < nodeNum;i++) {

		visited[x] = true;
		vertex* adx = Adj[x];
		for (int i = 0; i < adjNum[x]; i++) {
			test = true;
			if (pd_tab[adx[i].nr].cost > adx[i].cost + pd_tab[x].cost) {

				if (pd_tab[x].cost == INT_MAX)
					continue;
				test = false;
				pd_tab[adx[i].nr].cost = adx[i].cost + pd_tab[x].cost;
				pd_tab[adx[i].nr].nr = x;
			}
		}

		bool set = false;
		while (!set) {
			for (int i = 0; i < adjNum[x]; i++)
				if (visited[adx[i].nr] == false) {
					x = adx[i].nr;
					bool set = true;
					break;
				}
			if (!set)
				for (int i = 0; i < nodeNum; i++)
					if (visited[i] == false) {
						x = i;
						set = true;
						break;
					}
		}

	}
	/*Sprawdzam, czy nie ma ujemnych cykli*/
	if (!test) {
			x = start;
			for (int i = 1; i < nodeNum; i++) {
				vertex* adx = Adj[x];
				for (int i = 0; i < adjNum[x]; i++)
					if (pd_tab[adx[i].nr].cost > adx[i].cost + pd_tab[x].cost)
						return false; //ujemny cykl
				if (adjNum[x] > 0)
					x = adx[0].nr;
				else x++;
			}
		}
	
	/*if (printResult) {
		std::cout << "Koszty dojscia do kolejnych wierzcholkow, startujac od wierzcholka " << start << " :" << std::endl;
		for (int i = 0; i < nodeNum; i++) {

			std::cout << "Dojscie do wierzcholka " << i << " :";

			if (i == start) {
				std::cout << " wierzcholek startowy, koszt = 0\n";
				continue;
			}
			else
				if (pd_tab[i].nr == -1) {
					std::cout << "dojscie do wierzcholka niemozliwe\n";
					continue;
				}

			std::cout << i << "<- ";
			int poprzednik = pd_tab[i].nr;
			while (poprzednik >= 0) {
				std::cout << poprzednik;
				poprzednik = pd_tab[poprzednik].nr;
				if (poprzednik != -1)
					std::cout << "<- ";
			}
			std::cout << ", koszt = " << pd_tab[i].cost << std::endl;
		}
	}*/
	
	if (printResult) {
		std::cout << "Koszt dojscia do wierzcholka " << end << " od wierzcholka " << start << " :" << std::endl;

		if (end == start) {
			std::cout << " wierzcholek startowy, koszt = 0\n";
			delete[] Adj;
			delete[] visited;
			return true;
		}
		else
			if (pd_tab[end].nr == -1) {
				std::cout << "dojscie do wierzcholka niemozliwe\n";
				delete[] Adj;
				delete[] visited;
				return true;
			}

		std::cout << end << "<-";
		int poprzednik = pd_tab[end].nr;
		while (poprzednik >= 0) {
			std::cout << poprzednik;
			poprzednik = pd_tab[poprzednik].nr;
			if (poprzednik != -1)
				std::cout << "<-";
		}
		std::cout << ", koszt = " << pd_tab[end].cost << std::endl;
	}

	for (int i = 0; i < nodeNum; i++) 
		delete[] Adj[i];
	
	delete[] Adj;
	delete[] visited;
	return true;
}

void MatrixGraph::addEdge(Edge e, int idx)
{
	/*Dodanie do tablicy wartoœci*/

	edgeValues[idx] = e.val;

	
		
		/*Wype³nienie nowego wiersza*/
		for (int i = 0; i < nodeNum; i++) {

			if (i != e.beg && i != e.end)
				matrixGraph[idx][i] = 0; // zera dla pozosta³ych
			else {
				if (e.beg == e.end)
					matrixGraph[idx][i] = 2; // dwa dla pêtli
				else {
					if(i == e.beg)
						matrixGraph[idx][i] = 1;
					else
						matrixGraph[idx][i] = -1;
				}
			}
		}

}

std::ostream & operator<<(std::ostream & output, MatrixGraph & graph)
{
	output << "Reprezentacja macierzowa:\nKolumny -> krawedzie grafu(wagi krawedzi nad nr)\nWiersze -> wierzcholki grafu\n";
	/* Wydrukowanie macierzy wag krawêdzi*/
	output.width(4);
	output << std::endl<<"wagi" << std::right;

	for (int i = 0; i < graph.edgeNum; i++) {
		output.width(4);
		output << "*" << graph.edgeValues[i] << std::right;
	}

	output << std::endl << std::endl;

	/* Drukowanie numerów krawêdzi*/
	for (int i = 0; i < graph.edgeNum; i++) {
		
		if (i == 0) {
			output.width(4);
			output << "w\\k" << std::right;
		}
	
		output.width(4);
		output << i << ":" << std::right;

	}
	
	output << std::endl;
	
	/* Drukowanie kolejnych wierszy macierzy*/
	for (int i = 0; i < graph.nodeNum; i++) {
		
		/* Wydrukowanie numeru wierzcho³ka*/
		output.width(4);
		output << i << ":" << std::right;

		/* Drukowanie kolejnych wartoœci macierzy incydencji dla danego wierzcho³ka*/
		for (int j = 0; j < graph.edgeNum; j++) {
			
			output.width(5);
			output << graph.matrixGraph[j][i] << std::right;
			
		}

		output << std::endl;
	}

	output << std::endl;
	return output;
}
