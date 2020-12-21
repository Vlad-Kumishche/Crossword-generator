#ifndef LIBRARY_H
#define LIBRARY_H

#include "../Structures/Word.h"

class Library
{
public:
	Library();
	~Library();
	void Clear();

	//s - search pattern
	const Words* FindWord(const std::string& patt) const;
	bool IsWord(std::string str) const;
	void ComputeStats();
	void PrintStats() const;
	std::string GetWord(int i) const;

	//Get and write all possible patterns from the word into the hash table (unordered_map)
	void CreatePatternHash(std::pair<Word*, std::string> record);
	void ReadFromFile(std::string filename, const int max_span_size);
	void DebugBuckets() const;
private:
	//Master list of words
	Words words_;

	//Pattern Hash
	WordMap word_map_;

	//Сколько слов имеют определенную длину. Это как гистограмма
	std::vector<int> counts_;
};
#endif