#ifndef MENU_H
#define MENU_H
#include "PatternSolver.h"

class Menu
{
public:
	Menu();
	void Call();
private:
	void SelectGrid();
	void DemoGrid(std::string path);
	void SelectLib();
	void Generate();
	void UserGuide();

	//Allows you to get a number entered from the keyboard
	int GetNum();
	//Allows you to enter a value in the range between A and B
	int ChoiceBetween(int a, int b);

	Grid grid_;
	Library lib_;

	unsigned int current_grid_;
	unsigned int current_lib_;

	bool exit;
	bool is_grid_loaded;
	bool is_lib_selected;
};

#endif