#include "mainTask.h"
#include <windows.h>
#include <conio.h>
#include <time.h>

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
	std::cout << "�������� ������� ������, ����������� ���� ������ ���������� � ���������� " << std::filesystem::current_path()
		<< "\n����� �������������� ����� ������ �����? (y/n)";
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
			std::cout << "������������ ����, ������� y ��� n:   ";
		}
		while (repatch)
		{
			
			std::cout << "\n������� ���� � ����� WordsList.txt: ";
			coord = GetConsoleCursorPosition(hStdout);
			std::getline(std::cin, pathToWL);
			if (!n.changePath(pathToWL))
			{
				SetConsoleCursorPosition(hStdout, coord);
				std::cout << "������ ������ �����������, ��������� ����: ";
			}
			else repatch = false;
		}
		std::cout << "������� ����� ����� " << n.getPath() << "\n";

		std::cout << "�������� ����� ������ ������:\n1 - �� ��������� ������� (����� �� ���������)\n"
			<< "2 - �������� ����� ���������� �� �������� �����\n"
			<< "3 - �������� ����� ���������� � ��������� �����\n"
			<< "4 - �������� ����� ������� ������� �� ��������� ����\n"
			<< "5 - �������� ����� ������� ������� �� �������� ����\n��������� �������:";

		coord = GetConsoleCursorPosition(hStdout);
		SetConsoleCursorPosition(hStdout, coord);
		bool reader;
		int remode = 0;
			
		while (remode == 0)
		{
			ans = _getch();
			SetConsoleCursorPosition(hStdout, coord);
			if (ans=='\n') { n.setMode(0); reader = n.read();  remode++; break; }
			if (ans == '1' || ans == '2' || ans == '3' || ans == '4'|| ans == '5' )
			{
				remode++;
				n.setMode(ans-'0'-1);
				break;
			}
			std::cout << "������������ ����, ������� ����� �� 1 �� 5:\n";
		}
			
		std::cout<<"\n�������� ����� � ������ � "<<n.getMode()+1<<'\n';
		if (!n.read()) { std::cout << "������ ������ ����� " << n.getPath() << " ������ �������� ��������� � ��� ���� " << n.getLogPath() << '\n'; return 0; }
		std::cout << "���� ������� ������, ������ ���������. �������� ������ �� ������ ������ ����� ������. �������������� ������...\n";
		n.countMatches();
		std::cout << "������ ������� ���������������. ���������� ���������� � ���� ResultPairs.txt\n";
		if (!n.save()) { std::cout << "���������� �� �������! ������ ������ � ����! ������ �������� ��������� � ��� ���� " << n.getLogPath() << '\n'; return 0; }
		std::cout << "������ ������� ���������. ������ ��������� ���������.";
		ret = true;
	}
	return 0;
}