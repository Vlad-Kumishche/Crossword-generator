#include "PatternSolver.h"

void PatternSolver::Solve(const Grid& grid, Library* lib, SolvingMode mode)
{
	lib_ = lib;
	mode_ = mode;
	is_solved_ = false;
	Loop(grid, 0);
}

void PatternSolver::Loop(Grid grid, int depth)
{
	if (is_solved_)
	{
		return;
	}

	depth++;

	Slots empty_slots;
	Slots partial_slots;
	Slots full_slots;

	for (const Span& span : grid.spans)
	{
		Attr attr;
		std::string temp = grid.GetSpanString(span, attr);
		if (attr.is_empty())
		{
			empty_slots.push_back(Slot(span, temp));
		}
		else if (attr.is_partial())
		{
			partial_slots.push_back(Slot(span, temp));
		}
		else if (attr.is_full())
		{
			full_slots.push_back(Slot(span, temp));
		}
	}
	unsigned int num_empty = empty_slots.size();
	unsigned int num_partial = partial_slots.size();
	unsigned int num_full = full_slots.size();

	//Need to check that all words so far are valid
	for (const Slot& slot : full_slots)
	{
		//cout << "Checking " << slot.pattern << endl;
		if (!(*lib_).IsWord(slot.pattern))
		{
			//cout << "NOT! ABORT!" << endl;
			return;
		}
	}

	//Need to check that all words are unique! no duplicates allowed
	StringSet set;
	for (const Slot& slot : full_slots)
	{
		if (set.ExistsInSet(slot.pattern))
		{
			return;
		}
		set.AddToSet(slot.pattern);
	}

	//If a solution is found
	if (num_partial == 0 && num_empty == 0)
	{
		system("CLS");
		std::cout << "Решение найдено:" << std::endl << std::endl;
		grid.PrintGrid();

		bool first_horizontal_word = false;
		bool first_vertical_word = false;
		//Clues
		for (const Slot& slot : full_slots)
		{
			if (first_horizontal_word == false && slot.span.is_vert == false)
			{
				first_horizontal_word = true;
				std::cout << std::endl << " Слова по горизонтали:" << std::endl;
			}
			if (first_vertical_word == false && slot.span.is_vert == true)
			{
				first_vertical_word = true;
				std::cout << std::endl << " Слова по вертикали:" << std::endl;
			}
			Attr attr;
			std::string word_str = grid.GetSpanString(slot.span, attr);

			//There will only be one definition here, because the library does not contain duplicates
			const Words* words = (*lib_).FindWord(word_str);
			if (words)
			{
				Words read_list = *words;
				const std::pair<Word*, std::string> definition = read_list[0];

				//Turning to a single definition
				std::cout << "  " << definition.first->word << " - " << definition.second << std::endl;
			}
		}

		//Crossword puzzle is solved
		is_solved_ = true;
		return;
	}

	//If the grid is completely empty
	if (num_full == 0 && num_partial == 0)
	{
		CommitSlot(grid, empty_slots[0], depth);
		return;
	}

	//If the crossword puzzle is partially filled initially
	try
	{
		if (num_partial <= 0)
		{
			throw Exception("PatternSolver::Loop: number of partial slotos <= 0");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	CommitSlot(grid, partial_slots[0], depth);
	return;
}

void PatternSolver::CommitSlot(Grid& grid, const Slot& slot, int depth)
{
	if (is_solved_)
	{
		return;
	}
	const Words* words = (*lib_).FindWord(slot.pattern);
	if (words)
	{
		if (mode_ == SolvingMode::productive)
		{
			for (const std::pair<Word*, std::string> record : *words)
			{
				grid.WriteStringToSpan(slot.span, record.first->word);
				Loop(grid, depth);
				if (is_solved_)
				{
					return;
				}
			}
		}
		else if (mode_ == SolvingMode::unique_cross)
		{
			//Create an editable copy of the 'words'
			Words red_list = *words;

			srand(time(NULL));
			//Shuffle words to create a unique crossword puzzle
			std::random_shuffle(red_list.begin(), red_list.end());

			for (const std::pair<Word*, std::string> record : red_list)
			{
				grid.WriteStringToSpan(slot.span, record.first->word);

				//If a solution is found
				Loop(grid, depth);
				if (is_solved_)
				{
					return;
				}
			}
		}
		else
		{
			//Exception
		}
	}
	else
	{
		//No matches to pattern
		return;
	}
}
