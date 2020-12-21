#include "Classes\Menu.h"

int main()
{
	//Setting the console color
	system("color F1");

	//Setting the encoding "Windows-1251"
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Setting a new console title
	static const TCHAR* myTitle = TEXT("Crossword generator by Vlad Kumishche");
	SetConsoleTitle(myTitle);

	//Calling the main menu
	Menu MainMenu;
	MainMenu.Call();
}