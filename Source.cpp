﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include <vector>
#include <stdio.h>


#include <io.h>
#include <iomanip> 

using namespace std;

#include "Users.h"
#include "Singleton_Menu.h"
#include "Category.h"
#include "UserTakesTest.h"

int main()
{
	while (1)
	{
		Base_User a;
		a.Start();
		Singleton_Menu* singleton_menu = Singleton_Menu::getInstance();
		singleton_menu->Show_Menu(a);
		cout << "Press any key to continue\n"; _getch();
	}
}

