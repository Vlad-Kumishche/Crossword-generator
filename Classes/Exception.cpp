#include "Exception.h"

void Terminate()
{
	std::cerr << "Abort!" << std::endl;
	abort();
}

void Unexpected()
{
	std::cerr << "\nUnexpected exception" << std::endl;
	terminate();
}
Exception::Exception() : message_("Something went wrong") {}
Exception::Exception(std::string error) : message_(error) {}
std::string Exception::GetError()
{
	return message_;
}