#include "Menu.h"

Menu::Menu() :
	current_grid_(0),
	current_lib_(0),
	exit(false),
	is_grid_loaded(false),
	is_lib_selected(false) {}

void Menu::Call()
{
	while (!exit)
	{
		std::cout << " ��� ������������ ��������� \"��������� �����������\"" << std::endl;

		//Displaying the current state of the library and the grid
		if (current_grid_ || current_lib_)
		{
			std::cout << std::endl;
		}
		if (current_grid_)
		{
			std::cout << "  ������� �����: ";
			switch (current_grid_)
			{
			case 1:
				std::cout << "����������� (13�10)" << std::endl;
				break;
			case 2:
				std::cout << "� ����� New York Times (7x7)" << std::endl;
				break;
			case 3:
				std::cout << "����������� (25x10)" << std::endl;
				break;
			case 4:
				std::cout << "���������� ������� (10�10)" << std::endl;
				break;
			case 5:
				std::cout << "������-���� (17�12)" << std::endl;
				break;
			default:
				std::cout << "����������� �����. �������� ����� ������." << std::endl;
				grid_.ClearGrid();
				is_grid_loaded = false;
				break;
			}
		}
		if (current_lib_)
		{
			std::cout << "  ������� �������: ";
			switch (current_lib_)
			{
			case 1:
				std::cout << "16 ���. ����" << std::endl;
				break;
			case 2:
				std::cout << "25 ���. ����" << std::endl;
				break;
			case 3:
				std::cout << "50 ���. ����" << std::endl;
				break;
			case 4:
				std::cout << "100 ���. ����" << std::endl;
				break;
			default:
				std::cout << "���������� �������. �������� ������ ������." << std::endl;
				lib_.Clear();
				is_lib_selected = false;
				break;
			}
		}
		if (current_grid_ || current_lib_)
		{
			std::cout << std::endl;
		}

		std::cout << "  ����:" << std::endl;

		if (is_grid_loaded)
		{
			std::cout << "   1. ������� ������ �����." << std::endl;
		}
		else
		{
			std::cout << "   1. ������� �����" << std::endl;
		}

		if (is_lib_selected)
		{
			std::cout << "   2. ������� ������ �������." << std::endl;
		}
		else
		{
			std::cout << "   2. ������� �������" << std::endl;
		}

		std::cout << "   3. ������������� ���������" << std::endl;
		std::cout << "   4. �������� ����������� ������������" << std::endl;
		std::cout << "   5. ����� �� ���������" << std::endl;
		std::cout << std::endl << "��� �����: ";

		int user_choice = ChoiceBetween(1, 5);

		switch (user_choice)
		{
		case 1:
			SelectGrid();
			break;
		case 2:
			SelectLib();
			break;
		case 3:
			Generate();
			break;
		case 4:
			UserGuide();
			break;
		case 5:
			exit = true;
			break;
		}
	}
}
void Menu::SelectGrid()
{
	system("CLS");
	grid_.ClearGrid();
	is_grid_loaded = false;

	std::cout << " �������� ����� �� ������������ ���� ���������:" << std::endl;
	std::cout << " (����� - ������, ���������� ����������, ����� - ������������ ������)" << std::endl << std::endl;
	std::cout << "  1. ����������� ��� ������ �������� ����� (������ 13�10), ��������������� � ������������������ � �����������:" << std::endl;
	DemoGrid("Grids/13x10.txt");

	std::cout << std::endl;
	std::cout << "  2. ����� ���������� � ����� New York Times (������ 7�7), ��� ������ ������ �������� ������������ ��� ������ ����:" << std::endl;
	DemoGrid("Grids/7x7NY.txt");

	std::cout << std::endl;
	std::cout << "  3. ����������� (��� ��������������) ����� (������ 25�10)" << std::endl;
	std::cout << "     (������������� ������� ������� ��������):" << std::endl;
	DemoGrid("Grids/25x10INF.txt");

	std::cout << std::endl;
	std::cout << "  4. �����, ���������� ������� (������ 10�10):" << std::endl;
	DemoGrid("Grids/10x10.txt");

	std::cout << std::endl;
	std::cout << "  5. ������� ����� � ���������� ����������� (������ 17�12) ������� �������� ����������." << std::endl;
	std::cout << "     ��� ������ ������������ ��������� �����. ������������� �������� ���������������� �����." << std::endl;
	DemoGrid("Grids/17x12.txt");

	std::cout << std::endl << "��� �����: ";
	int user_choice = ChoiceBetween(1, 5);

	switch (user_choice)
	{
	case 1:
		grid_.LoadFromFile("Grids/13x10.txt");
		grid_.Check();
		grid_.FillSpans();
		current_grid_ = 1;
		break;
	case 2:
		grid_.LoadFromFile("Grids/7x7NY.txt");
		grid_.Check();
		grid_.FillSpans();
		current_grid_ = 2;
		break;
	case 3:
		grid_.LoadFromFile("Grids/25x10INF.txt");
		grid_.Check();
		grid_.FillSpans();
		current_grid_ = 3;
		break;
	case 4:
		grid_.LoadFromFile("Grids/10x10.txt");
		grid_.Check();
		grid_.FillSpans();
		current_grid_ = 4;
		break;
	case 5:
		grid_.LoadFromFile("Grids/17x12.txt");
		grid_.Check();
		grid_.FillSpans();
		current_grid_ = 5;
		break;
	default:
		break;
	}
	system("CLS");
	is_grid_loaded = true;
}
void Menu::DemoGrid(std::string path)
{
	grid_.LoadFromFile(path);
	grid_.Check();
	grid_.FillSpans();
	grid_.PrintGrid();
	grid_.ClearGrid();
}
void Menu::SelectLib()
{
	system("CLS");
	if (is_grid_loaded)
	{
		is_lib_selected = false;
		system("CLS");

		std::cout << " �������� ������� �� ������������ ���� ���������:" << std::endl;
		std::cout << "  1. ����� ������� - 16 ���. ���� (������������� ��� ���������� ������������������)" << std::endl;
		std::cout << "  2. ����� ������� - 25 ���. ����" << std::endl;
		std::cout << "  3. ����� ������� - 50 ���. ����" << std::endl;
		std::cout << "  4. ����� ������� - 100 ���. ���� (�� ������ ������)" << std::endl;

		std::cout << std::endl << "��� �����: ";
		int user_choice = ChoiceBetween(1, 4);
		current_lib_ = user_choice;
		is_lib_selected = true;
	}
	else
	{
		std::cout << "������� �������� �����" << std::endl;
		system("pause");
	}
	system("CLS");
}
void Menu::Generate()
{
	system("CLS");
	if (is_grid_loaded)
	{
		if (is_lib_selected)
		{
			std::cout << " �������� ����� ���������:" << std::endl;
			std::cout << "  1. ���������� ���������. ��������� �������� ��������� ���� �� ����� �������." << std::endl;
			std::cout << "     ��� ������ �� �������� ������� ������� ������ ������� � �������� ���������� �� ���������" << std::endl;
			std::cout << "  2. ����������������. ��������� �������� ������� ����������� ������" << std::endl;

			std::cout << std::endl << "��� �����: ";
			int user_choice = ChoiceBetween(1, 2);
			system("CLS");
			std::cout << "��� ������� ���������...";
			switch (current_lib_)
			{
			case 1:
				lib_.ReadFromFile("Libraries/lib16k.txt", grid_.max_span_size);
				break;
			case 2:
				lib_.ReadFromFile("Libraries/lib25k.txt", grid_.max_span_size);
				break;
			case 3:
				lib_.ReadFromFile("Libraries/lib50k.txt", grid_.max_span_size);
				break;
			case 4:
				lib_.ReadFromFile("Libraries/lib100k.txt", grid_.max_span_size);
				break;
			}
			Solver* solver = new PatternSolver();
			if (user_choice == 1)
			{
				solver->Solve(grid_, &lib_, SolvingMode::unique_cross);
			}
			else
			{
				solver->Solve(grid_, &lib_, SolvingMode::productive);
			}
			lib_.Clear();
		}
		else
		{
			std::cout << "������� �������� �������" << std::endl;
		}
	}
	else
	{
		std::cout << "������� �������� �����" << std::endl;
	}
	std::cout << std::endl;
	system("pause");
	system("CLS");
}
void Menu::UserGuide()
{
	system("CLS");
	std::cout << " ����������� ������������ - ��� ������������� ���� ������ ��������� (��� ��������):" << std::endl << std::endl;

	std::cout << "   1. ������ � ����������� ������������� ����� ���� �������� � ����������." << std::endl;
	std::cout << "      (�� ��� �� ��� ������, ��� ������ �� ��� ��������)" << std::endl << std::endl;

	std::cout << "   2. ������ ������� ������� �����, ������� �� ������� ���������." << std::endl;
	std::cout << "      ��� ����� ������� �����, ��������������� ����� ���� \"������� �����\"." << std::endl;
	std::cout << "      ����� ����������� ������ ��������� �����. ������������ �����, ������� � ������, ���" << std::endl;
	std::cout << "      ����� - ��� ������, ���������� ����������, � ����� - ������������ ������." << std::endl;
	std::cout << "      ����� - �������� ������������� ��� �����." << std::endl;
	std::cout << "      (� ������� �������� �����, ������� �������, ����� ����� ������� ���������� ������ �������)" << std::endl << std::endl;

	std::cout << "   3. ����� �������� �������, ������ �� ����, ����� ����� �� �������." << std::endl;
	std::cout << "      ��� ����������� ������� ������ ������� � 16 ���. ����," << std::endl;
	std::cout << "      ������ ������ ����������, � ������� ��� ����� �������� �� �������� �����." << std::endl;
	std::cout << "      (�� �� ������� �������� � ������?)" << std::endl << std::endl;

	std::cout << "   4. ����� �������� ����� ���� \"������������� ���������\". ��� ����� ���������� ������� ����� ������." << std::endl;
	std::cout << "      ������ ��������� \"���������� ���������\" �� ����������� ��� �������, ����� ������������� ������� ����." << std::endl;
	std::cout << "      ���� - ��� ���������������� �����, ������� ������ �������� - ������� ��������� ��� ����� �������." << std::endl;
	std::cout << "      (�� ������������ ���������� � ���� ������ ����������)" << std::endl << std::endl;

	std::cout << "   5. � ������ ��� �� ���� ������. ��� ��� ����������� �����-�������� ��������, �� ������� ���������� ������ ����������." << std::endl;
	std::cout << "      ������ ��������� ������ �� ������� �������� ���������." << std::endl;
	std::cout << "      ��� ������ ��������� �����, ���� �� �� ������� ��������� ������������� ���������." << std::endl;
	std::cout << "      ��������� ���������� ��������� ��� ��������� ��-�������� - ������������ ������." << std::endl;
	std::cout << "      �� � ��� �� ������? �� ��� � ��� ��� ����� ������ �������. ��������� �����������!" << std::endl;

	system("pause");
	system("CLS");
}

int Menu::GetNum()
{
	//Input buffer clear 
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	bool failInput;
	std::string value;
	int return_val;
	do
	{
		failInput = false;
		getline(std::cin, value);

		if (value.find_first_not_of("0123456789") != std::string::npos || value.empty())
		{
			failInput = true;
			std::cout << "������������ ����. ������� �����: ";
		}
		if (!failInput)
		{
			try
			{
				return_val = stoi(value);
			}
			catch (...)
			{
				failInput = true;
				std::cout << "������������ ����. ������� �����: ";
			}
		}
	} while (failInput);
	return return_val;
}
int Menu::ChoiceBetween(int a, int b)
{
	bool flag;
	int answer;
	do
	{
		answer = GetNum();
		if (answer >= a && answer <= b)
			flag = true;
		else
		{
			std::cout << "����� ����� � �������� �� " << a << " �� " << b << ": ";
			flag = false;
		}

	} while (!flag);
	return answer;
}