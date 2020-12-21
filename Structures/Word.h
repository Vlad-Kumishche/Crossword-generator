#ifndef WORD_H
#define WORD_H
#include "Span.h"

struct Word
{
	Word();
	Word(std::string s);
	int len() const;
	std::string word;
};
typedef std::vector<std::pair<Word*, std::string>> Words;
typedef std::unordered_map<std::string, Words> WordMap;

#endif