#include "RandGraphGen.h"
/*Klasa do generowania liczb losowych*/



RandGraphGen::RandGraphGen()
{
	tab = nullptr;
	n = 0;
}
RandGraphGen::~RandGraphGen()
{
	if (tab != nullptr)
	{
		for (int i = 0; i < n; i++)
		{
			if(tab[i] != nullptr)
				delete[] tab[i];
		}
		delete[] tab;
	}
	
}
/*Funkcja generuje zadana ilosc liczb losowych z zadanego zakresu.
length - ilosc liczb do wygenerowania
range - zakres generowanych liczb*/
int** RandGraphGen::generate(int town_num, int dist_val_range)
{
	if (town_num < 0)
		throw new IndexOutOfBoundsException("Liczba miast nie moze byc ujemna!");
	
	if (tab != nullptr)
	{
		for (int i = 0; i < n; i++)
		{
			if (tab[i] != nullptr)
				delete[] tab[i];
		}
		delete[] tab;
	}

	n = town_num;
	tab = new int*[n];
	for (int i = 0; i < n; i++)
		tab[i] = new int[n];

	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (i == k)
			{
				tab[i][k] = 0;
				continue;
			}

			tab[i][k] = rand() % dist_val_range + 1;
		}
	}
	return tab;
}
	
/*Funkcja zapisujaca wygenerowane liczby do pliku w formacie zgodnym
z formatem akceptownym przez struktury.*/
std::string RandGraphGen::saveToFile(std::string file_name)
{
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");
	std::fstream output;
	output.open(file_name, std::ios::out);
	
	/*Zapisanie iloœci miast*/
	output << n << std::endl;

	for (int i = 0; i < n; i++) {

		for (int k = 0; k < n; k++)
			output << tab[i][k] << " ";
		output << std::endl;
	}
	output.close();
	return file_name;
}


