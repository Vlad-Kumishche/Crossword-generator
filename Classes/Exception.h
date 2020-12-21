#ifndef EXCEPTION_H
#define EXCEPTION_H
#include "../Headers/DataTypes.h"

void Terminate();
void Unexpected();

class Exception
{
public:
	Exception();
	Exception(std::string error);
	std::string GetError();
private:
	std::string message_;
};
#endif
