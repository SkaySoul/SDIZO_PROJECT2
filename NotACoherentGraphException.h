#pragma once
#include <exception>
#include <typeinfo>
#include <iostream>

class NotACoherentGraphException : public std::runtime_error
{
public:
	NotACoherentGraphException(const char* msg) : std::runtime_error(msg){

	};
	~NotACoherentGraphException() {};

	virtual const char* what() const throw();
};

