#include "IndexOutOfBoundsException.h"


const char * IndexOutOfBoundsException::what() const throw()
{
	return std::runtime_error::what();
}
