#ifndef STRING_SET_H
#define STRING_SET_H
#include "../Classes/Exception.h"

struct StringSet
{
	//Return true if string 'str' exists in set alredy
	bool ExistsInSet(const std::string str);
	void AddToSet(const std::string str);

	std::unordered_set<std::string> set;
};
#endif
