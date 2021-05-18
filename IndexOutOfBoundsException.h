#pragma once
#include<iostream>
#include <exception>
#include <typeinfo>
/*Klasa wyj¹tku.
Wyj¹tek ten jest wyrzucany, jeœli szukany indeks jest poza rozmiarem struktury.*/
class IndexOutOfBoundsException : std::runtime_error
{
public:
	IndexOutOfBoundsException(const char* msg) : std::runtime_error(msg) {

	};
	~IndexOutOfBoundsException() {};

	virtual const char* what() const throw();
};
