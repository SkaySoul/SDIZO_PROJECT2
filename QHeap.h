#pragma once
#include <iostream>
struct vertex {
	int nr;
	int cost;
};

class QHeap
{

public:
	int size;
	vertex* Q;

	QHeap(int _size, int start);
	~QHeap();

	vertex pop();
	void heap_fix_down();
	void heap_fix_up(int index);
	void changeCost(int v_nr, int cost);
};

