#include "Slot.h"

Slot::Slot(const Span& s, const std::string& p) : span(s), pattern(p) {}
std::ostream& operator << (std::ostream& os, const Slot& slot)
{
	os << slot.span << " '" << slot.pattern << "'";
	return os;
}