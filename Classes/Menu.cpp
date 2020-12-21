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
		std::cout << " Вас приветствует программа \"Генератор Кроссвордов\"" << std::endl;

		//Displaying the current state of the library and the grid
		if (current_grid_ || current_lib_)
		{
			std::cout << std::endl;
		}
		if (current_grid_)
		{
			std::cout << "  Текущая сетка: ";
			switch (current_grid_)
			{
			case 1:
				std::cout << "Оптимальная (13х10)" << std::endl;
				break;
			case 2:
				std::cout << "В стиле New York Times (7x7)" << std::endl;
				break;
			case 3:
				std::cout << "философская (25x10)" << std::endl;
				break;
			case 4:
				std::cout << "Обрамлённая словами (10х10)" << std::endl;
				break;
			case 5:
				std::cout << "Стресс-тест (17х12)" << std::endl;
				break;
			default:
				std::cout << "Неизвестная сетка. Выберите сетку заново." << std::endl;
				grid_.ClearGrid();
				is_grid_loaded = false;
				break;
			}
		}
		if (current_lib_)
		{
			std::cout << "  Текущий словарь: ";
			switch (current_lib_)
			{
			case 1:
				std::cout << "16 тыс. слов" << std::endl;
				break;
			case 2:
				std::cout << "25 тыс. слов" << std::endl;
				break;
			case 3:
				std::cout << "50 тыс. слов" << std::endl;
				break;
			case 4:
				std::cout << "100 тыс. слов" << std::endl;
				break;
			default:
				std::cout << "Неизвестый словарь. Выберите словрь заново." << std::endl;
				lib_.Clear();
				is_lib_selected = false;
				break;
			}
		}
		if (current_grid_ || current_lib_)
		{
			std::cout << std::endl;
		}

		std::cout << "  Меню:" << std::endl;

		if (is_grid_loaded)
		{
			std::cout << "   1. Выбрать другую сетку." << std::endl;
		}
		else
		{
			std::cout << "   1. Выбрать сетку" << std::endl;
		}

		if (is_lib_selected)
		{
			std::cout << "   2. Выбрать другой словарь." << std::endl;
		}
		else
		{
			std::cout << "   2. Выбрать словарь" << std::endl;
		}

		std::cout << "   3. Сгенерировать кроссворд" << std::endl;
		std::cout << "   4. Прочесть руководство пользователя" << std::endl;
		std::cout << "   5. Выйти из программы" << std::endl;
		std::cout << std::endl << "Ваш выбор: ";

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

	std::cout << " Выбирите сетку из предложенных ниже вариантов:" << std::endl;
	std::cout << " (дефис - ячейка, подлежащая заполнению, точка - незаполяемая ячейка)" << std::endl << std::endl;
	std::cout << "  1. Оптимальная для данной програмы сетка (размер 13х10), демонстрирующая её производительность и возможности:" << std::endl;
	DemoGrid("Grids/13x10.txt");

	std::cout << std::endl;
	std::cout << "  2. Сетка кроссворда в стиле New York Times (размер 7х7), где каждая ячейка является перекрестием для других слов:" << std::endl;
	DemoGrid("Grids/7x7NY.txt");

	std::cout << std::endl;
	std::cout << "  3. философская (или математическая) сетка (размер 25х10)" << std::endl;
	std::cout << "     (рекомендуется выбрать словарь побольше):" << std::endl;
	DemoGrid("Grids/25x10INF.txt");

	std::cout << std::endl;
	std::cout << "  4. Сетка, обрамлённая словами (размер 10х10):" << std::endl;
	DemoGrid("Grids/10x10.txt");

	std::cout << std::endl;
	std::cout << "  5. Сложная сетка с множеством перекрестий (размер 17х12) неплохо нагрузит приложение." << std::endl;
	std::cout << "     Для сборки понадобиться несколько минут. Рекомендуется включить производительный режим." << std::endl;
	DemoGrid("Grids/17x12.txt");

	std::cout << std::endl << "Ваш выбор: ";
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

		std::cout << " Выбирите словарь из предложенных ниже вариантов:" << std::endl;
		std::cout << "  1. Обьём словаря - 16 тыс. слов (рекомендуется для повышенной производительности)" << std::endl;
		std::cout << "  2. Обьём словаря - 25 тыс. слов" << std::endl;
		std::cout << "  3. Обьём словаря - 50 тыс. слов" << std::endl;
		std::cout << "  4. Обьём словаря - 100 тыс. слов (на всякий случай)" << std::endl;

		std::cout << std::endl << "Ваш выбор: ";
		int user_choice = ChoiceBetween(1, 4);
		current_lib_ = user_choice;
		is_lib_selected = true;
	}
	else
	{
		std::cout << "Сначала выберите сетку" << std::endl;
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
			std::cout << " Выбирите режим генерации:" << std::endl;
			std::cout << "  1. Уникальный кроссворд. Позволяет получать непохожие друг на друга решения." << std::endl;
			std::cout << "     При работе со сложными сетками требует больше времени и ресурсов компьютера на генерацию" << std::endl;
			std::cout << "  2. Производительный. Позволяет получить решение максимально быстро" << std::endl;

			std::cout << std::endl << "Ваш выбор: ";
			int user_choice = ChoiceBetween(1, 2);
			system("CLS");
			std::cout << "Идёт процесс генерации...";
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
			std::cout << "Сначала выберите словарь" << std::endl;
		}
	}
	else
	{
		std::cout << "Сначала выберите сетку" << std::endl;
	}
	std::cout << std::endl;
	system("pause");
	system("CLS");
}
void Menu::UserGuide()
{
	system("CLS");
	std::cout << " Руководство пользователя - как сгенерировать свой первый кроссворд (для чайников):" << std::endl << std::endl;

	std::cout << "   1. Работа с приложением осуществяется через ввод символов с клавиатуры." << std::endl;
	std::cout << "      (но это вы уже поняли, раз попали на эту страницу)" << std::endl << std::endl;

	std::cout << "   2. Сперва следует выбрать сетку, которую вы желаете заполнить." << std::endl;
	std::cout << "      Для этого введите цифру, соответствующую пунку меню \"Выбрать сетку\"." << std::endl;
	std::cout << "      Далее отобразится список доступных сеток. Просматривая сетку, держите в голове, что" << std::endl;
	std::cout << "      дефис - это ячейка, подлежащая заполнению, а точка - незаполяемая ячейка." << std::endl;
	std::cout << "      Далее - выберите понравившуюся Вам сетку." << std::endl;
	std::cout << "      (и читайте описание сетки, которую выбрали, чтобы потом выбрать подходящий размер словаря)" << std::endl << std::endl;

	std::cout << "   3. Далее выберите словарь, исходя из того, какую сетку вы выбрали." << std::endl;
	std::cout << "      Для большинства случаев хватит словоря в 16 тыс. слов," << std::endl;
	std::cout << "      однако бывают исключения, о которых вам будет изветсто из описания сетки." << std::endl;
	std::cout << "      (вы же читаете описание к сеткам?)" << std::endl << std::endl;

	std::cout << "   4. Далее выберите пункт меню \"Сгенерировать кроссворд\". Вам будет предложено выбрать режим работы." << std::endl;
	std::cout << "      Всегда выбирайте \"Уникальный кроссворд\" за исключением тех случаев, когда рекомендуется выбрать иное." << std::endl;
	std::cout << "      Иное - это производительный режим, главная задача которого - собрать кроссворд как можно быстрее." << std::endl;
	std::cout << "      (но уникальность кроссворда в этом случае пострадает)" << std::endl << std::endl;

	std::cout << "   5. А дальше уже не ваша забота. Обо всём позаботился умный-преумный алгоритм, на котором базируется данное приложение." << std::endl;
	std::cout << "      Спустя несколько секунд вы увидите резульат генерации." << std::endl;
	std::cout << "      Или спустя несколько минут, если вы не желаете следовать рекомендациям программы." << std::endl;
	std::cout << "      Сохронять получанный результат вам предстоит по-старинке - переписывать руками." << std::endl;
	std::cout << "      Ну а что вы хотели? За вас и так уже много работы сделали. Приятного пользования!" << std::endl;

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
			std::cout << "Некорректный ввод. Введите снова: ";
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
				std::cout << "Некорректный ввод. Введите снова: ";
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
			std::cout << "Дайте ответ в пределах от " << a << " до " << b << ": ";
			flag = false;
		}

	} while (!flag);
	return answer;
}