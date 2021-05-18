#include "QHeap.h"



QHeap::QHeap(int _size, int start)
{
	this->size = _size;
	Q = new vertex[size];

	for (int i = 0; i < size; i++) {
		Q[i].nr = i;
		Q[i].cost = INT_MAX;
	}
	this->changeCost(start, 0);
}

QHeap::~QHeap()
{
	delete[] Q;
}

vertex QHeap::pop()
{
	vertex ret = Q[0];
	
	this->size--;
	
	vertex* buf = new vertex[this->size];
	memcpy(buf, Q + 1, size*sizeof(vertex));
	
	delete[] Q;

	Q = buf;

	heap_fix_down();
	return ret;
}

void QHeap::heap_fix_down()
{
	int i = 0;
	int j = 1;

	while (j < size) {
		//Szukam mniejszego syna
		if (j + 1 < this->size && Q[j].cost > Q[j + 1].cost)
			j++;

		if (Q[i].cost <= Q[j].cost)
			return;

		vertex buf = Q[j];
		Q[j] = Q[i];
		Q[i] = buf;
		i = j;
		j = 2 * i + 1;
	}
	return;
}

void QHeap::heap_fix_up(int index)
{
	int i = index;
	int parent = (i - 1) / 2;

	while (Q[parent].cost > Q[i].cost && i != 0) {

		vertex buf = Q[i];
		Q[i] = Q[parent];
		Q[parent] = buf;
		i = parent;
		parent = (i - 1) / 2;
	}
}

void QHeap::changeCost(int v_nr, int cost)
{
	int idx;
	for (int i = 0; i < this->size; i++) {
		if (Q[i].nr == v_nr) {
			idx = i;
			Q[i].cost = cost;
			break;
		}
	}
	heap_fix_up(idx);
}
