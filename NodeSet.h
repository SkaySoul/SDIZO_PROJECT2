#pragma once

struct Node {
	int prev, rank;
};
class NodeSet
{
private:
	Node* Set;
public:
	NodeSet(int n);
	~NodeSet();

	void makeSet(int v);
	int findSet(int v);
	void joinSets(int v1, int v2);
};

