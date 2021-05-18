#include "FileNotFoundException.h"



const char * FileNotFoundException::what() const throw()
{
	return std::runtime_error::what();
}
