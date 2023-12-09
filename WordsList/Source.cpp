#include "mainTask.h"
#include <windows.h>
#include <conio.h>

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

int main()
{
	mainTask n;
	setlocale(LC_ALL, "");
	std::cout << "Согласно условий задачи, исполняемый файл должен находиться в директории " << std::filesystem::current_path()
		<< "\nАдрес местоположения файла указан верно? (y/n)";
	char ans = '0';
	bool repatch = false;
	int step = 0;
	bool ret = false;
	while (!ret)
	{
		std::string pathToWL;
		COORD coord;
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		coord = GetConsoleCursorPosition(hStdout);
		coord.X -= 5;
		while (step == 0)
		{
			ans = _getch();
			SetConsoleCursorPosition(hStdout, coord);
			if (ans == 'y')
			{
				step++;
				break;
			}
			if (ans == 'n')
			{
				step++;
				repatch = true;
				break;
			}
			std::cout << "Неправильный ввод, введите y или n:";
		}
		while (repatch)
		{
			
			std::cout << "\nВведите путь к файлу WordsList.txt: ";
			coord = GetConsoleCursorPosition(hStdout);
			std::getline(std::cin, pathToWL);
			if (!n.changePath(pathToWL))
			{
				SetConsoleCursorPosition(hStdout, coord);
				std::cout << "Пустая строка недопустима, повторите ввод: ";
			}
			else repatch = false;
		}
		std::cout << "Текущий адрес файла " << n.getPath() << "\nОткрытие файла...\n";
		if (!n.read()) { std::cout << "Ошибка чтения файла " << n.getPath() << " детали операции сохранены в лог файл " << n.getLogPath() << '\n'; return 0; }
		std::cout << "Файл успешно открыт, данные сохранены. Линейного списка на основе данных файла создан. Форматирование данных...\n";
		n.countMatches();
		std::cout << "Данные успешно отформатированы. Сохранение результата в файл ResultPairs.txt\n";
		if (!n.save()) { std::cout << "Ошибка записи в файл! Детали операции сохранены в лог файл " << n.getLogPath() << '\n'; return 0; }
		std::cout << "Данные успешно сохранены. Работа программы завершена.";
		ret = true;

	}
	return 0;
}