/*#include "Game.h"

	srand(time(NULL));
	Generate_Pole();
	tmp_time = time(0);
	StartGame();*/

#pragma once
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

char symb0 = ' ';
char symb1 = ' ';
char symb2 = 'W';
char symb3 = '.';
int pole = 30;
int x = rand() % pole;
int y_1, y_2, y_3, y1_1, y1_2, y1_3, y2_1, y2_2, y2_3, y3_1, y3_2, y3_3, y4_1, y4_2, y4_3, y5_1, y5_2, y5_3;
int temp = 0;
int input1 = 0;
int input2 = 0;
int counter = 0;
int tmp_time = 0, tmp_old_time = 0;
string new_line, line_1, line_2, line_3, line_4, line_5;

string Line()
{
	new_line.clear();
	y_1 = rand() % pole, y_2 = rand() % pole, y_3 = rand() % pole;
	if (y_1 > y_2)
	{
		y_1 = y_1 + y_2;
		y_2 = y_1 - y_2;
		y_1 = y_1 - y_2;
	}
	if (y_2 > y_3)
	{
		y_2 = y_2 + y_3;
		y_3 = y_2 - y_3;
		y_2 = y_2 - y_3;
	}
	if (y_1 > y_2)
	{
		y_1 = y_1 + y_2;
		y_2 = y_1 - y_2;
		y_1 = y_1 - y_2;
	}
	for (int i = 1; i < y_1; i++)
	{
		new_line += symb1;
	}
	new_line += symb3;
	for (int i = y_1 + 1; i < y_2; i++)
	{
		new_line += symb1;
	}
	if (y_2 != y_1)
		new_line += symb3;
	for (int i = y_2 + 1; i < y_3; i++)
	{
		new_line += symb1;
	}
	if (y_3 != y_2)
		new_line += symb3;
	for (int i = y_3 + 1; i <= pole; i++)
	{
		new_line += symb1;
	}
	return new_line;
}

void Generate_Pole()
{
	for (size_t i = 0; i < pole; i++)
	{
		line_1 += symb1;
		line_2 += symb1;
		line_3 += symb1;
		line_4 += symb1;
		line_5 += symb1;
	}
}

void Show()
{
	system("cls");
	cout << "SPACE Uber\nTry to avoid asteroids!\n";
	cout << "Score: " << time(0) - tmp_time << endl;
	cout << line_1;
	cout << endl;
	cout << line_2;
	cout << endl;
	cout << line_3;
	cout << endl;
	cout << line_4;
	cout << endl;
	cout << line_5;
	cout << endl;
	for (int i = 1; i < x; i++)
	{
		cout << symb0;
	}
	cout << symb2;
	for (int i = x + 1; i <= pole; i++)
	{
		cout << symb0;
	}
	if ((x == y5_1) || (x == y5_2))
	{
		cout << endl << "-----------GAME OVER----------" << endl;
		exit(777);
	}
}

void Pole()
{
	if (((time(0) - tmp_time) % 2 == 1) && (counter == 1))
	{
		line_2 = line_1;
		y2_1 = y1_1;
		y2_2 = y1_2;
		line_4 = line_3;
		y4_1 = y3_1;
		y4_2 = y3_2;

		Show();
		Beep(200, 30);
	}
	if (((time(0) - tmp_time) % 2 == 0) && (counter == 0))
	{
		line_1 = Line();
		y1_1 = y_1;
		y1_2 = y_2;
		line_3 = line_2;
		y3_1 = y2_1;
		y3_2 = y2_2;
		line_5 = line_4;
		y5_1 = y4_1;
		y5_2 = y4_2;

		Show();
		counter++;
		Beep(200, 30);
	}

	if (((time(0) - tmp_time) % 2 == 1) && (counter == 1))
		counter = 0;
}

void StartGame()
{
	Sleep(100);
	Pole();

	if (_kbhit())
	{
		Beep(25000, 10);
		input1 = _getch();
		input2 = _getch();

		switch (input2)
		{
		case 75: //left
			if ((x - 1) < 1)
				break;
			else
			{
				x -= 1;
				break;
			}
		case 77: //right
			if ((x + 1) > pole)
				break;
			else
			{
				x += 1;
				break;
			}
		default:
			break;
		}
		Show();
	}
	StartGame();
}