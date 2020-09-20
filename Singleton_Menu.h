#pragma once
#include "Users.h"
#include "Game.h"
#include "Users.h"
#include "Category.h"
#include "UserTakesTest.h"

class Singleton_Menu
{
private:
	Singleton_Menu() {}
	static Singleton_Menu *obj;

public:
	static Singleton_Menu* getInstance();

	string tmp_str;
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
				cout << "-----------ADMINISTRATOR MODE ACTIVATED----------\n";
				cout << "-------------------------------------------------\n";
				cout << "Welcome \"" << a.GetLogin() << "\"!\n";
				cout << "----------------------MENU-----------------------" << endl;
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
				cout << "5 - See stats\n";
				cout << "6 - Add CATEGORY for tests\n";
				cout << "7 - Add test\n";
				cout << "8 - Add questions with answers in test\n";
				cout << "9 - Export/import of tests\n";//todo
				cout << "10 - Play game \"SPACE Uber\"\n";
				cout << "33 - EXIT\n";

				cin.clear();
				cin >> choise;
				switch (choise)
				{
				case 0: //Change my login
					cout << "Please, enter new login: ";
					getline(cin, tmp_login);
					if (a.ChangeAdminLogin(tmp_login))
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another login\n";
					cout << "Press any key to continue\n";_getch();
					break;
				case 1: //Change my password
					cout << "Please, enter new password: ";
					getline(cin, new_admin_password);
					if (a.ChangeAdminPswd(new_admin_password))
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another password\n";
					cout << "Press any key to continue\n"; _getch();
					break;
				case 2: //Create new user
					cout << "Login: ";
					getline(cin, tmp_login);
					if (!a.user_map[tmp_login])
					{
						if (a.Add_user(tmp_login))
						{
							cout << "\nSUCCESS\n";
							cout << "Press any key to continue\n"; _getch();
						}
					}
					else
					{
						cout << "\nTry another login\n";
						cout << "Press any key to continue\n"; _getch();
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
					getline(cin, tmp_login);
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
									cout << "Press any key to continue\n"; _getch();
								}
						}
						else
							cout << "\nSomething went wrong\n";
					}
					else
					{
						cout << "\nTry another login\n";
						cout << "Press any key to continue\n"; _getch();
					}
					break;
				case 4: //Make changes in user
					cout << "There are such users:\n";
					a.LoadUsersMap();
					for (auto iter = a.user_map.begin(); iter != a.user_map.end(); iter++)
					{
						cout << iter->first << endl;
					}
					cout << "Login: ";
					getline(cin, tmp_login);
					if (a.user_map[tmp_login] && (a.GetAdmLogin() != tmp_login))
					{
						a.LoadUserInfo(tmp_login);
						a.ShowUserInfo(tmp_login);
						a.SetUserInfo(tmp_login);
						if (a.SaveUserInfo(tmp_login))
							cout << "\nSUCCESS\n";
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						cout << "\nTry another login\n";
						cout << "Press any key to continue\n"; _getch();
					}
					break;
				case 5: //See stats
					cout << "There are such users:\n";
					a.LoadUsersMap();
					for (auto iter = a.user_map.begin(); iter != a.user_map.end(); iter++)
					{
						cout << iter->first << endl;
					}
					cout << "Login: ";
					getline(cin, tmp_login);
					if (a.user_map[tmp_login] && (a.GetAdmLogin() != tmp_login))
					{
						a.LoadUserInfo(tmp_login);
						system("cls");
						cout << "--------------USER \"" << tmp_login <<"\" STAT--------------\n";
						a.ShowUserInfo(tmp_login);
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						cout << "\nTry another login\n";
						cout << "Press any key to continue\n"; _getch();
					}
					break;
				case 6: //Add CATEGORY for tests
				{
					cout << "New category name: ";
					getline(cin, tmp_str);
					Category* categor = new Test();
					if (categor->AddCategory(tmp_str))
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another category name\n";
					cout << "Press any key to continue\n"; _getch();
					break;
				}
				case 7: //Add test
				{
					Category* categor = new Test();
					cout << "Choose category\n"; //выбираем в какую категорию добавить тест
					categor->ShowCategoriesVector();
					cin.clear();
					cin >> choise;
					if ((choise >= categor->GetLenghtCategoriesVector()) || (choise < 0))
					{
						cout << "\nTry another choise\n";
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						cout << "New test name: "; //просим имя нового теста и добавляем его
						cin.clear();
						getline(cin, tmp_str);
						if (categor->AddTest(tmp_str, choise))
							cout << "\nSUCCESS\n";
						else
							cout << "\nTry another test name\n";
						cout << "Press any key to continue\n"; _getch();
					}
					break;
				}
				case 8: //Add questions with answers in test
				{
					Category* categor = new Test();
					cout << "Choose category\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
					categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
					cin.clear();
					cin >> choise; //некоторое время хранит индекс категории
					if ((choise >= categor->GetLenghtCategoriesVector()) || (choise < 0))
					{
						cout << "\nTry another choise\n";
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						cout << "Choose test\n"; //выбор теста
						categor->ShowTests(choise); //показываем на экран какие есть тесты в выбранной категории
						cin.clear();
						int tmp;
						cin >> tmp; //индекс теста
						if ((tmp >= categor->GetLenghtTestsVector(choise)) || (tmp < 0))
						{
							cout << "\nTry another choise\n";
							cout << "Press any key to continue\n"; _getch();
						}
						else
						{
							categor->AddQuestionWithAnswer(tmp, choise);
						}
					}
					break;
				}
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
					cout << "Press any key to continue\n"; _getch();
					break;
				}
				break;
			case 2: //(user mode)
				cout << "----------------USER MODE ACTIVATED--------------\n";
				cout << "-------------------------------------------------\n";
				cout << "Welcome \"" << a.GetLogin() << "\"!\n";
				cout << "----------------------MENU-----------------------" << endl;
					/*¦ После входа гость имеет возможность просмотреть
					свои предыдущие результаты тестирования, сдать
					новое тестирование.*/
				cout << "0 - Take a new test\n";
				cout << "1 - Show my statistics\n"; 
				cout << "2 - LOAD previous session\n";
				cout << "33 - EXIT\n";

				cin.clear();
				cin >> choise;
				switch (choise)
				{
				case 0: //Take a new test
				{
					Sleep(300);
					ifstream in_tmp_test_2("User\\" + a.GetLogin() + "-SAVE" + ".bin");
					if (in_tmp_test_2.is_open())
					{
						cout << "\nYou can not take tests, while you have saved one!\n";
						cout << "Press any key to continue\n"; _getch();
						break;
					}
					UserTakesTest* b = new UserTakesTest(a); //Попытался понять ООП :)
					cout << "Press any key to continue\n"; _getch();
					delete b;
					break;
				}
				case 1: //Show my statistics
					a.LoadUserInfo(a.GetLogin());
					system("cls");
					cout << "---------------------MY STAT---------------------\n";
					a.ShowUserInfo(a.GetLogin());
					cout << "Press any key to continue\n"; _getch();
					break;
				case 2: //LOAD previous session
				{
					string tmp_str;
					int category_index, test_index;
					int questions_all, correct_answers, mark_A = 12;
					int mark, percentage;
					string tmp_str_1, tmp_str_2;
					string test_name;

					ifstream in16("User\\" + a.GetLogin() + "-SAVE" + ".bin");
					if (in16.is_open())
					{
						getline(in16, tmp_str);
						category_index = stoi(tmp_str);

						getline(in16, tmp_str);
						test_index = stoi(tmp_str);

						getline(in16, tmp_str);
						questions_all = stoi(tmp_str);

						getline(in16, tmp_str);
						correct_answers = stoi(tmp_str);

						getline(in16, tmp_str);
						mark_A = stoi(tmp_str);

						getline(in16, tmp_str);
						mark = stoi(tmp_str);

						getline(in16, tmp_str);
						percentage = stoi(tmp_str);

						getline(in16, tmp_str_1);

						getline(in16, tmp_str_2);

						getline(in16, test_name);

						in16.close();

						UserTakesTest* c = new UserTakesTest(a, category_index, test_index,
							--questions_all, correct_answers, mark_A,
							mark, percentage, tmp_str_1, tmp_str_2,
							test_name);
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						cout << "You don't have saved work\n";
						cout << "Press any key to continue\n"; _getch();
					}
					break;
				}
				case 33:
					break;
				default:
					cout << "No such menu choise. Try again.\n";
					cout << "Press any key to continue\n"; _getch();
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