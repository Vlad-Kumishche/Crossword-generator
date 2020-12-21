#include "Library.h"

Library::Library() {}

Library::~Library()
{
	Clear();
}
void Library::Clear()
{
	for (int i = 0; i < words_.size(); i++)
	{
		delete words_[i].first;
	}
	words_.clear();
	word_map_.clear();
	counts_.clear();
}
const Words* Library::FindWord(const std::string& patt) const
{
	auto it = word_map_.find(patt);
	if (it != word_map_.end())
	{
		return &it->second;
	}
	return nullptr;
}
bool Library::IsWord(std::string str) const
{
	auto it = word_map_.find(str);
	if (it == word_map_.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Library::ComputeStats()
{
	try
	{
		if (!counts_.empty())
		{
			throw Exception("ComputeStats: Counts is not empty");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}

	counts_.resize(18);
	int words_size = words_.size();
	for (int i = 0; i < words_size; i++)
	{
		int len = words_[i].first->word.length();
		if (len < 20)
		{
			counts_[len]++;
		}
	}
}
void Library::PrintStats() const
{
	std::cout << "Количество слов определённой длины:" << std::endl;
	for (int i = 1; i < counts_.size(); i++)
	{
		std::cout << "[" << i << "] " << counts_[i] << std::endl;
	}
}
std::string Library::GetWord(int i) const
{
	try
	{
		if (i < 0 || i >= words_.size())
		{
			throw Exception("GetWord: Index out of range");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	return words_[i].first->word;
}
void Library::CreatePatternHash(std::pair<Word*, std::string> record)
{
	int len = record.first->len();

	//Equivalent to pow(2, len)
	int num_patterns = 1 << len;
	for (int i = 0; i < num_patterns; i++)
	{
		std::string temp = record.first->word;
		for (int j = 0; j < len; j++)
		{
			//look through each bit and check if it's equal to one
			if ((i >> j) & 1)
			{
				//Insert a gap
				temp[j] = '-';
			}
		}
		word_map_[temp].push_back(record);
	}
}
void Library::ReadFromFile(std::string filename, const int max_span_size)
{
	std::ifstream f;
	f.open(filename);
	std::pair<std::string, std::string> word_and_def;
	std::pair<Word*, std::string> record;
	while (f.is_open() && !f.eof())
	{
		std::string line;
		getline(f, line);
		if (!line.empty())
		{
			auto pos = line.find(',');
			if (pos != std::string::npos)
			{
				word_and_def.first = line.substr(0, pos);
			}
			if (word_and_def.first.length() <= max_span_size)
			{
				if (pos != std::string::npos)
				{
					record.second = line.substr(pos + 1);
					record.first = new Word(word_and_def.first);
					words_.push_back(record);
					CreatePatternHash(record);
				}
			}
		}
	}
}
void Library::DebugBuckets() const
{
	for (int i = 0; i < word_map_.bucket_count(); i++)
	{
		std::cout << "[" << i << "] " << word_map_.bucket_size(i) << std::endl;
	}
}
