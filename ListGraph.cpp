#include "ListGraph.h"

/* Metody klasy reprezentuj¹cej krawêdŸ*/
ListGraph::Edge::Edge() {
	new Edge(0, -1, -1);
}
ListGraph::Edge::Edge(int val, int begN, int endN)
{
next = nullptr;
prev = nullptr;
value = val;
end = endN;
beg = begN;
}

ListGraph::Edge::~Edge()
{
}

/* Metody klasy wewnêtrznej, reprezentuj¹cej dynamiczn¹ tablicê po³¹czeñ w grafie*/

ListGraph::NodesArray::NodesArray()
{
	NodesArray(0);
}

ListGraph::NodesArray::NodesArray(int nNodes)
{
	size = nNodes;

	nArray = new Edge*[size];

	for (int i = 0; i < size; i++)
		nArray[i] = nullptr;
}

ListGraph::NodesArray::NodesArray(NodesArray & temp)
{
	size = temp.size;
	nArray = new Edge*[size];
	for (int i = 0; i < size; i++) {
		Edge* ptr = temp.nArray[i];
		while (ptr != nullptr) {
			this->addEdge(i, ptr->end, ptr->value);
		}
	}
}

ListGraph::NodesArray::~NodesArray()
{
	for (int i = 0; i < size; i++) {
		Edge* ptr = nArray[i];
		while (ptr != nullptr) {
			
			if (ptr->next == nullptr) {
				delete ptr;
				break;
			}	
			ptr = ptr->next;
			delete ptr->prev;
		}
	}
	delete[] nArray;
}

void ListGraph::NodesArray::addEdge(int beg, int end, int val)
{
	Edge* ptr;

	ptr = nArray[beg];
	/* Jeœli pierwsza krawêdŸ dla tego wierzcho³ka*/
	if (ptr == nullptr) {
		nArray[beg] = new Edge(val, beg, end);
		return;
	}
	while (ptr->next != nullptr) {
			ptr = ptr->next;
	}
	
	ptr->next = new Edge(val, beg, end);
	ptr->next->prev = ptr;
	
	return;
}

std::string ListGraph::NodesArray::listNodeConnections(int nodeId)
{	
	if (nodeId >= this->size)
		throw IndexOutOfBoundsException("\nW tym grafie nie ma takiego wierzcholka!");
	
	std::string list = "";
	Edge* ptr = this->nArray[nodeId];
	std::ostringstream oss;
	while (ptr != nullptr) {
		list.append("(");
		oss << ptr->beg;
		list.append(oss.str());
		
		oss.str(std::string()); //czyszczenie strumienia

		list.append("-");
		oss << ptr->end;
		list.append(oss.str());

		oss.str(std::string());

		list.append(",");
		oss << ptr->value;
		list.append(oss.str());
		list.append("), ");

		oss.str(std::string()); 
		ptr = ptr->next;
	}

	return list;
}

/*Metody kopca*/
ListGraph::EdgeHeap::EdgeHeap()
{
	size = 0;
	isEmpty = true;
	root = nullptr;
}

ListGraph::EdgeHeap::~EdgeHeap()
{
	delete[] root;
}

void ListGraph::EdgeHeap::push(Edge & edge)
{
	if (size == 0) {
		/*push front*/
		size++;
		root = new Edge*[size];
		root[0] = &edge;
		isEmpty = false;
	}

	/*push back*/
	Edge** buf = new Edge*[size + 1];
	memcpy(buf, root, size*sizeof(Edge*));
	size++;
	delete[] root;
	root = buf;
	root[size - 1] = &edge;
	heap_fix_up();
	isEmpty = false;
}

ListGraph::Edge ListGraph::EdgeHeap::pop()
{
	if (size == 0)
		throw IndexOutOfBoundsException("\nKopiec jest juz pusty! Nie mozna usunac elementu!");
	Edge ret;
	ret.beg = root[0]->beg;
	ret.end = root[0]->end;
	ret.value = root[0]->value;

	if (size == 1) {
		size--;
		root = nullptr;
		isEmpty = true;
		return ret;
	}

	root[0] = root[size - 1]; //ostatni liœæ na miejsce korzenia
	size--;
	Edge** buf = new Edge*[size];
	memcpy(buf, root, size*sizeof(Edge*));
	delete[] root;
	root = buf;
	heap_fix_down();
	return ret;
}

void ListGraph::EdgeHeap::heap_fix_up()
{
	int i = this->size - 1;
	int parent = (i - 1) / 2;
	while (root[parent]->value > root[i]->value) {
		Edge* bufor = root[parent];

		root[parent] = root[i];
		root[i] = bufor;

		i = parent;
		parent = (i - 1) / 2;
	}
}

void ListGraph::EdgeHeap::heap_fix_down()
{

	int i = 0; // zaczynamy od korzenia
	int j = 2 * i + 1;

	while (j < size) {
		//szukam wiêkszego syna
		if (j + 1 < size && (root[j]->value > root[j + 1]->value))
			j += 1;

		if (root[i]->value <= root[j]->value)
			break;

		Edge* buf = root[i];
		root[i] = root[j];
		root[j] = buf;
		i = j;
		j = 2 * i + 1;
	}

}

/* Metody klasy reprezentacji listowej grafu*/
ListGraph::ListGraph(ListGraph & temp)
{
	nodeNum = temp.nodeNum;
	edgeNum = temp.edgeNum;
	listGraph = *(new NodesArray(temp.listGraph));
}

ListGraph::ListGraph()
{
	nodeNum = 0;
	edgeNum = 0;
	listGraph = *(new NodesArray());
}

ListGraph::~ListGraph()
{
}

void ListGraph::open(std::string fileName)
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
	}
	catch (std::exception ex) {
		std::cerr << "Blad podczas wczytywania danych z pliku:\n" << ex.what();
		return;
	}
	delete iss;

	this->listGraph = *(new NodesArray(this->nodeNum));

	for (int i = 0; i < edgeNum; i++) {

		getline(input, inputLine);

		iss = new std::istringstream(inputLine);
		int beg, end, val;
		/* Odczytanie linii danych opisuj¹cych i-t¹ krawêdŸ*/
		try {
			*iss >> beg;
			*iss >> end;
			*iss >> val;
		}
		catch (std::exception ex) {
			std::cerr << "Blad podczas wczytywania danych z pliku:\n" << ex.what();
			return;
		}
		/* Pêtla wype³niaj¹ca i-t¹ kolumnê wed³ug wczytanych danych
		(informajce o krawêdzi nr i) */
		this->listGraph.addEdge(beg, end, val);

		delete iss;
	}
	return;
}

void ListGraph::save(std::string fileName)
{
	if (fileName[fileName.length() - 1] != *"t" ||
		fileName[fileName.length() - 2] != *"x" ||
		fileName[fileName.length() - 3] != *"t" ||
		fileName[fileName.length() - 4] != *".")
		fileName.append(".txt");

	std::fstream output;
	output.open(fileName, std::ios::out);

	output << this->edgeNum << " " << this->nodeNum << std::endl;

	for (int i = 0; i < nodeNum; i++) {
		Edge* ptr = this->listGraph.nArray[i];
		while (ptr != nullptr) {
			output << i << " " << ptr->end << " " << ptr->value << std::endl;
			ptr = ptr->next;
		}
	}
	return;
}

void ListGraph::Prim(ListGraph &resultTree)
{
	//ListGraph resultTree = *(new ListGraph());
	resultTree.nodeNum = nodeNum;
	resultTree.edgeNum = 0;
	resultTree.listGraph = *(new NodesArray(resultTree.nodeNum));

	if (edgeNum < nodeNum - 1)
		throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
	/* Tworzê now¹ pust¹ kolejkê priorytetow¹ na krawêdzie*/
	EdgeHeap edges = *(new EdgeHeap());

	/* Tworzê tablicê logiczna, zawieraj¹c¹ informacje o odwiedzonych wierzcho³kach*/
	bool* visited = new bool[nodeNum];
	for (int i = 0; i < nodeNum; i++)
		visited[i] = false;

	/* wybieram wierzcho³ek startowy i oznaczam jako odwiedzony*/
	int v = 0;
	visited[v] = true; 
	for (int i = 1; i < nodeNum;i++) {
		
		
		Edge* ptr = listGraph.nArray[v];
		while (ptr == nullptr) {
			v++;
			if (v >= nodeNum)
				throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
			ptr = listGraph.nArray[v];
		}
		/*if (ptr == nullptr)
			throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");*/
		
		/* Umieszczamy w kolejce priorytetowej krawêdzie do nieodwiedzonych s¹siadów*/
		while (ptr != nullptr) {
			
			if (visited[ptr->end] == false)
				edges.push(*ptr);
			ptr = ptr->next;
		}

		/* Dopóki krawêdŸ o najmniejszej wadze prowadzi do s¹siada juz odwiedzonego*/
		
			while (visited[edges.root[0]->end] == true) {
				edges.pop();
				if (edges.isEmpty)
					throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
			}
		
		

		int beg = edges.root[0]->beg;
		int end = edges.root[0]->end;
		int val = edges.root[0]->value;
		resultTree.listGraph.addEdge(beg,end,val);
		resultTree.edgeNum++;
		edges.pop();
		visited[end] = true;
		v = end;
	}
	
	for (int i = 0; i < nodeNum; i++) {
		if (visited[i] == false) 
			throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
		}

	
	delete[] visited;
	return;
}

void ListGraph::Kruskal(ListGraph & resultTree)
{
	resultTree.nodeNum = nodeNum;
	resultTree.edgeNum = 0;
	resultTree.listGraph = *(new NodesArray(resultTree.nodeNum));

	if (edgeNum < nodeNum - 1)
		throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");

	/*Kopiec na krawêdzie, posortowane wg wagi*/
	EdgeHeap edges = *(new EdgeHeap());
	/*Pêtla dodaj¹ca kolejne krawêdzie do kopca*/
	for (int i = 0; i < nodeNum; i++) {

		Edge* ptr = listGraph.nArray[i];

		while (ptr != nullptr) {
			edges.push(*ptr);
			ptr = ptr->next;
		}

	}


	NodeSet Z = *(new NodeSet(nodeNum));
	/*Pêtla, tworz¹ca kolejne zbiory roz³¹czne dla wszystkich wierzcho³ków*/
	for (int n = 0; n < nodeNum; n++)
		Z.makeSet(n);

	for (int i = 1; i < nodeNum; i++) {

		Edge e;

		do {

			if (edges.isEmpty)
				throw NotACoherentGraphException("Graf nie jest spojny! Nie mozna wykonac algorytmu.");
			e = edges.pop();


		} while (Z.findSet(e.beg) == Z.findSet(e.end));

		resultTree.listGraph.addEdge(e.beg, e.end, e.value);
	
		Z.joinSets(e.beg, e.end);
	}
}

void ListGraph::Dijkstra(int start, int end, bool printResult)
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

		Edge* ptr = listGraph.nArray[v.nr];
		
		while (ptr != nullptr) {
			vertex* buf = new vertex[n_adj + 1];
			memcpy(buf, adj, n_adj*sizeof(vertex));
			buf[n_adj].nr = ptr->end;
			buf[n_adj].cost = ptr->value;

			delete[] adj;
			adj = buf;
			n_adj++;
			
			ptr = ptr->next;
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
		std::cout << "Koszt dojscia do wierzcholka " << end << " od wierzcholka " << start << " :" << std::endl;

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

bool ListGraph::BellmanFord(int start, int end, bool printResult)
{
	if (start < 0 || start >= nodeNum)
		throw IndexOutOfBoundsException("\nPodany wierzcholek startowy jest poza zakresem!!");
	if (end < 0 || end >= nodeNum)
		throw IndexOutOfBoundsException("\nPodany wierzcholek koncowy jest poza zakresem!!");
	/*Utworzenie tablic z kosztami dojœcia do poszczególnych wierzcho³ków
	oraz z poprzednikami. Do tego tablica logiczna, mówi¹ca o tym, którego wierzcho³ka ju¿ nie ma w Q */
	vertex* pd_tab = new vertex[nodeNum];

	int* adjNum = new int[nodeNum];
	vertex** Adj = new vertex*[nodeNum];

	/*Utworzenie list s¹siedztwa*/
	for (int x = 0; x < nodeNum; x++) {

		adjNum[x] = 0;
		Adj[x] = new vertex[adjNum[x]];

		/*Przechodzimy kolejne wierzcho³ki*/
		for (Edge* ptr = listGraph.nArray[x]; ptr != nullptr; ptr = ptr->next) {

			if (ptr->end != x) //sprawdzam, czy to nie pêtla
			{
				/*Dodajemy do tablicy s¹siadów*/
				vertex* buf = new vertex[adjNum[x] + 1];
				memcpy(buf, Adj[x], adjNum[x] * sizeof(vertex));
				buf[adjNum[x]].nr = ptr->end;
				buf[adjNum[x]].cost = ptr->value;

				delete[] Adj[x];
				Adj[x] = buf;
				adjNum[x]++;
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

void ListGraph::multiplyEdges()
{
	/* Skopiowanie krawêdzi, tak aby mieæ graf nieskierowany*/
	for (int i = 0; i < nodeNum; i++) {
		Edge* ptr = listGraph.nArray[i];
		while (ptr != nullptr) {
			Edge* ptr2 = listGraph.nArray[ptr->end];
			bool alreadyThere = false;
			while (ptr2 != nullptr) {
				if (ptr2->end == ptr->beg)
					alreadyThere = true;
				ptr2 = ptr2->next;
			}
			if (!alreadyThere)
				listGraph.addEdge(ptr->end, ptr->beg, ptr->value);
			ptr = ptr->next;
		}
	}
}

std::ostream & operator<<(std::ostream & output, ListGraph & graph)
{
	output << "Reprezentacja listowa grafu:\nW kolejnych wierszach opisane polaczenia kolejnych wierzcholkow.";
	output << "\nW nawiasach informacje o polaczeniu -> (poczatek-koniec, waga krawedzi).\n\n";

	/* Iteracja po kolejnych wierzcho³kach grafu*/
	int size = graph.nodeNum;
	for (int i = 0; i < size; i++) {
		output << i << ": ";
		output << graph.listGraph.listNodeConnections(i) << std::endl;
	}
	return output;
}




