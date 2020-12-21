#include "StringSet.h"

bool StringSet::ExistsInSet(const std::string str)
{
	auto it = set.find(str);
	return (it != set.end());
}
void StringSet::AddToSet(const std::string str)
{
	try
	{
		if (ExistsInSet(str))
		{
			throw Exception("AddToSet: String is alredy exists in set");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	set.insert(str);
}