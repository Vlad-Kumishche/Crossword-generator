#include "Word.h"
Word::Word() {}
Word::Word(std::string s) : word(s) {}
int Word::len() const
{
	return word.length();
}