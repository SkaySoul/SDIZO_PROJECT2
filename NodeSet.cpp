#include "NodeSet.h"



NodeSet::NodeSet(int n)
{
	Set = new Node[n];
}


NodeSet::~NodeSet()
{
	delete[] Set;
}

void NodeSet::makeSet(int v)
{
	Set[v].prev = v;
	Set[v].rank = 0;
}

int NodeSet::findSet(int v)
{
	if (Set[v].prev != v)
		Set[v].prev = findSet(Set[v].prev);

	return Set[v].prev;

}

void NodeSet::joinSets(int v1, int v2)
{
	int root_v1, root_v2;

	root_v1 = findSet(v1);
	root_v2 = findSet(v2);

	/*Je�li wierzcho�ki nale�� do dw�ch r�nych zbior�w*/
	if (root_v1 != root_v2) {

		/*Je�li zbi�r z v1 wi�kszy od zioru z v2*/
		if (Set[root_v1].rank > Set[root_v2].rank) {
			
			Set[root_v2].prev = root_v1;
			Set[root_v2].rank++;
		}
		else {
			
			Set[root_v1].prev = root_v2;
			Set[root_v1].rank++;
		}
	}
}
