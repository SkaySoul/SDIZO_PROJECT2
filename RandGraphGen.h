#pragma once
#include <string>
#include <fstream>
#include <time.h>

#include "IndexOutOfBoundsException.h"

class RandGraphGen
{
	int** tab;
	int n;

public:
	RandGraphGen();
	~RandGraphGen();

	int** generate(int town_num, int dist_val_range);
	std::string saveToFile(std::string file_name);
};


