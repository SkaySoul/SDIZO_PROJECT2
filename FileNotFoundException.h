#pragma once
#include <iostream>
#include <exception>
#include <typeinfo>

/*Klasa wyj¹tku.
Wyj¹tek ten jest wyrzucany, jeœli nie zostanie odnaleziony plik, z którego mia³y byæ odczytane dane do struktury.*/
class FileNotFoundException : std::runtime_error
{
public:
	FileNotFoundException(const char* msg) : std::runtime_error(msg) {

	};
	~FileNotFoundException() {};

	virtual const char* what() const throw();
};

