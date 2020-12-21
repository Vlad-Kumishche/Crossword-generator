#ifndef SLOT_H
#define SLOT_H
#include "Grid.h"

struct Slot
{
	Slot(const Span& s, const std::string& p);
	friend std::ostream& operator << (std::ostream& os, const Slot& slot);

	Span span;
	std::string pattern;
};
typedef std::vector<Slot> Slots;
#endif