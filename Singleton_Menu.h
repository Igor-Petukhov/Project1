#pragma once
#include "Users.h"
#include "Game.h"
#include "Test.h"
#include "Users.h"

class Singleton_Menu
{
private:
	Singleton_Menu() {}
	static Singleton_Menu *obj;

public:
	static Singleton_Menu* getInstance();

	string tmp_login;
	string new_admin_password;

	void Show_Menu(Base_User a)
	{
		int choise = 88;
		do
		{
			system("cls");
			switch (a.GetUserType())
			{
			case 1: //(admin mode)
				cout << "ADMINISTRATOR MODE ACTIVATED\n";
				cout << "Welcome \"" << a.GetLogin() << "\"!\n";
				cout << "------Menu------" << endl;
				/*¦ В дальнейшем пароль и логин можно изменить (но
				данную возможность имеет только админ).

				Управление пользователями — создание, удаление,
				модификация пользователей.
				? Просмотр статистики — просмотр результатов те-
				стирования в общем по категориям, по конкретным
				тестам, по конкретным пользователям. Результаты
				просмотра статистики можно вывести в файл.
				? Управление тестированием — админ имеет воз-
				можность добавлять категории,тесты, вопросы
				к тестам, задавать правильные и неправильные
				ответы, импортировать и экспортировать категории
				и тесты с вопросами из файла (и в файл).*/
				cout << "0 - Change my login\n";
				cout << "1 - Change my password\n";
				cout << "2 - Create new user\n";
				cout << "3 - Delete user\n";
				cout << "4 - Make changes in user\n";
				cout << "5 - See stats\n";//todo
				cout << "6 - Add CATEGORY for tests\n";//todo
				cout << "7 - Add test\n";//todo
				cout << "8 - Add questions with answers in test\n";//todo
				cout << "9 - Export/import of tests\n";//todo
				cout << "10 - Play game \"SPACE Uber\"\n";
				cout << "33 - EXIT\n";

				cin.clear();
				cin >> choise;
				switch (choise)
				{
				case 0: //Change my login
					cout << "Please, enter new login: ";
					cin >> tmp_login;
					if (a.ChangeAdminLogin(tmp_login))
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another login\n";
					Sleep(2000);
					break;
				case 1: //Change my password
					cout << "Please, enter new password: ";
					cin >> new_admin_password;
					if (a.ChangeAdminPswd(new_admin_password))
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another password\n";
					Sleep(2000);
					break;
				case 2: //Create new user
					cout << "Login: ";
					cin >> tmp_login;
					if (!a.user_map[tmp_login])
					{
						if (a.Add_user(tmp_login))
						{
							cout << "\nSUCCESS\n";
							Sleep(2000);
						}
					}
					else
					{
						cout << "\nTry another login\n";
						Sleep(2000);
					}
					break;
				case 3: //Delete user
					cout << "There are such users:\n";
					a.LoadUsersMap();
					for (auto iter = a.user_map.begin(); iter != a.user_map.end(); iter++)
					{
						cout << iter->first << endl;
					}
					cout << "Login: ";
					cin >> tmp_login;
					if (a.user_map[tmp_login] && (a.GetAdmLogin() != tmp_login))
					{
						if (a.user_map.erase(tmp_login))
						{
							if (a.SaveUsersMap())
								if (a.LoadUsersMap())
								{
									tmp_login = "User\\" + tmp_login + ".txt";
									if (remove(tmp_login.c_str()) != 0)
										perror("Error deleting file");
									else
										puts("File successfully deleted");
									cout << "\nSUCCESS\n";
									Sleep(2000);
								}
						}
						else
							cout << "\nSomething went wrong\n";
					}
					else
					{
						cout << "\nTry another login\n";
						Sleep(2000);
					}
					break;
				case 4: //Make changes in user
					cout << "Login: ";
					cin >> tmp_login;
					if (a.user_map[tmp_login] && (a.GetAdmLogin() != tmp_login))
					{
						a.LoadUserInfo(tmp_login);
						a.ShowUserInfo(tmp_login);
						a.SetUserInfo(tmp_login);
						if (a.SaveUserInfo(tmp_login))
							cout << "\nSUCCESS\n";
						Sleep(2000);
					}
					else
					{
						cout << "\nTry another login\n";
						Sleep(2000);
					}
					break;
				case 5: //See stats

					break;
				case 6: //Add CATEGORY for tests

					break;
				case 7: //Add test

					break;
				case 8: //Add questions with answers in test

					break;
				case 9: //Export/import of tests

					break;
				case 10: //Play game \"SPACE Uber\"
					srand(time(NULL));
					Generate_Pole();
					tmp_time = time(0);
					StartGame();
					break;
				case 33: //exit
					break;
				default:
					cout << "No such menu choise. Try again.\n";
					Sleep(1000);
					break;
				}
				break;
			case 2: //(user mode)
				cout << "USER MODE ACTIVATED\n";
				cout << "Welcome \"" << a.GetLogin() << "\"!\n";
				cout << "------Menu------" << endl;
				/*¦ После входа гость имеет возможность просмотреть
					свои предыдущие результаты тестирования, сдать
					новое тестирование.*/
				cout << "0 - Take a new test\n";//todo
				cout << "1 - Show my statistics\n";//todo
				cout << "33 - EXIT\n";//todo

				cin.clear();
				cin >> choise;
				switch (choise)
				{
				case 0:
					
					break;
				case 1:

					break;
				case 33:
					break;
				default:
					cout << "No such menu choise. Try again.\n";
					Sleep(1000);
					break;
				}


				break;
			default:
				cout << "ERROR ОCCURE: menu can't recognize user_type\n";
				break;
			}
		} while (choise != 33);
		cout << "Bye-bye!\n";
	}
};

Singleton_Menu* Singleton_Menu::obj = nullptr;
Singleton_Menu* Singleton_Menu::getInstance()
{
	if (!obj)
		obj = new Singleton_Menu();
	return obj;
}