#include "NotACoherentGraphException.h"

const char * NotACoherentGraphException::what() const throw()
{
	return std::runtime_error::what();
}
