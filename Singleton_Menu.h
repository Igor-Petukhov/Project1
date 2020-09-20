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

	void Show_Menu(Base_User a)
	{
		Category* categor = new Test();
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
				cout << "33 - LOG OUT\n";

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
					cout << "Press any key to continue\n";_getch();
					break;
				case 1: //Change my password
					cout << "Please, enter new password.\n";
					if (a.ChangeAdminPswd())
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another password\n";
					cout << "Press any key to continue\n"; _getch();
					break;
				case 2: //Create new user
					cout << "Login: ";
					cin >> tmp_login;
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
					cin >> tmp_login;
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
					cin >> tmp_login;
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
					cin.ignore();
					cout << "New category name: ";
					getline(cin, tmp_str);
					//Category* categor = new Test();
					if (categor->AddCategory(tmp_str))
						cout << "\nSUCCESS\n";
					else
						cout << "\nTry another category name\n";
					cout << "Press any key to continue\n"; _getch();
					break;
				}
				case 7: //Add test
				{
					//Category* categor = new Test();
					cout << "Choose category\n"; //выбираем в какую категорию добавить тест
					categor->ShowCategoriesVector();
					cin >> choise;
					if ((choise >= categor->GetLenghtCategoriesVector()) || (choise < 0))
					{
						cout << "\nTry another choise\n";
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						cout << "New test name: "; //просим имя нового теста и добавляем его
						cin.ignore();
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
					//Category* categor = new Test();
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
				{
					system("cls");
					cout << "-----------ADMINISTRATOR MODE ACTIVATED----------\n";
					cout << "-------------------------------------------------\n";
					cout << "0 - Export test\n";
					cout << "1 - Import test\n";
					cin >> choise;
					switch (choise)
					{
					case 0: //Export
						//выбрать тест
						system("cls");
						cout << "Export test -> Choose category:\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
						cout << "-------------------------------------------------\n";
						categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
						int category_index;
						cin >> category_index; //индекс категории
						if ((category_index >= categor->GetLenghtCategoriesVector()) || (category_index < 0))
						{
							cout << "\nTry another choise\n";
							cout << "Press any key to continue\n"; _getch();
						}
						else
						{
							//выберем тест
							system("cls");
							cout << "Export test -> Choose category -> Choose test:\n"; //выбор теста
							cout << "-------------------------------------------------\n";
							categor->ShowTests(category_index); //показываем на экран какие есть тесты в выбранной категории
							int test_index;
							cin >> test_index; //индекс теста
							if ((test_index >= categor->GetLenghtTestsVector(category_index)) || (test_index < 0)) //проверим валидность индекса теста
							{
								cout << "\nTry another choise\n";
								cout << "Press any key to continue\n"; _getch();
							}
							else
							{
								string test_name;
								test_name = categor->GetTestName(test_index);
								/// <summary>
								/// ////Тут у нас есть имя теста. Дальше надо выбрать куда экспортируем.
								/// </summary>
								//ввести имя нового тхт файла и экспортировать
								cout << "\nEnter name of new file: ";
								string tmp_new_name_export;
								cin.ignore();
								getline(cin, tmp_new_name_export);
								ifstream in17("Tests\\" + test_name + ".my_ext");
								if (in17.is_open())
								{
									//открыли исходный файл
									//начинаем с него читать
									string tmp_str_1;
									string tmp_str_2;
									if (!categor->DirectoryExists("EXPORTED"))
									{
										if (_mkdir("EXPORTED") == -1)
										{
											cout << "\nProblem with creating directory \"EXPORTED\"\n";
											cout << "Press any key to continue\n"; _getch();
										}
									}
									ofstream out19("EXPORTED\\" + tmp_new_name_export + ".txt");//------новый файл
									if (out19.is_open())
									{
										while (getline(in17, tmp_str_1) && getline(in17, tmp_str_2))
										{
											//пока читается - как считали так и загоняем в новый файл
											out19 << tmp_str_1 << endl;//вопрос
											out19 << tmp_str_2 << endl;//ответ
										}
										out19.close();//закрываем новый и старый файлы
										in17.close();
										cout << "\nExport done! Check \"EXPORTED\" directory";
										cout << "\nSUCCESS\n";
										cout << "Press any key to continue\n"; _getch();
									}
									else
									{
										//а если новый файл експорта почему-то не создался, уведомляем об етом
										in17.close();
										cout << "\nTry another name of export file!\n";
										cout << "Press any key to continue\n"; _getch();
									}

								}
							}
						}
						break;
					case 1: //Import
					{
						system("cls");
						cout << "Import test:\n";
						cout << "-------------------------------------------------\n";
						if (!categor->DirectoryExists("IMPORT"))
						{
							if (_mkdir("IMPORT") == -1)
							{
								cout << "\nProblem with creating directory \"IMPORT\"\n";
								cout << "Press any key to continue\n"; _getch();
							}
						}
						cout << "Put new file in \"IMPORT\" folder.\n";
						Sleep(100);
						cout << "Press any key when done\n"; _getch();

						
						vector <string> filenames;
						filenames.clear();
						////////////////////////Просто вывод на экран содержимого папки готовое но доработанное вектором решение
						char Name[7] = "IMPORT";
						//Показ содержимого текущей директории
						_finddata_t find;
						char pathfind[MAX_PATH];
						strcpy(pathfind, Name);
						strcat(pathfind, "\\*.*");
						char info[MAX_PATH];
						//Начало Поиска
						int result = _findfirst(pathfind, &find);
						//Очистка экрана
						system("cls");
						cout << "Import test -> Choose your file:\n";
						cout << "-------------------------------------------------\n";
						int flag = result;
						int counter = -1;
						if (flag == -1)
						{
							strcpy(info, "No such directory");
							cout << info << endl;
						}
						while (flag != -1)
						{
							if (strcmp(find.name, ".") && strcmp(find.name, ".."))
							{
								
								//Проверяем Директория или Нет
								if (!(find.attrib & _A_SUBDIR))
								{
									counter++;
									cout << " " << counter << " - " << find.name << endl;
									//загоняем в вектор полное название файла
									filenames.push_back(find.name);
								}
								
							}
							//Продолжаем Поиск
							flag = _findnext(result, &find);
						}
						_findclose(result);
						cout << "\n-------------------------------------------------\n";
						///////////////////////////////////////////////////////////////////////////
						cin >> counter;
						cout << "You choosed: " << filenames[counter] << endl;
						cout << "Press any key to continue\n"; _getch();

						//После того как нашли имя файла - найдём тест, в который мы хотим загрузить вопросы
						//имя файла - filenames[counter]
						

						//выбрать тест
						system("cls");
						cout << "Import test -> Choose your file -> Choose category:\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
						cout << "-------------------------------------------------\n";
						categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
						int category_index;
						cin >> category_index; //индекс категории
						if ((category_index >= categor->GetLenghtCategoriesVector()) || (category_index < 0))
						{
							cout << "\nTry another choise\n";
							cout << "Press any key to continue\n"; _getch();
						}
						else
						{
							//выберем тест
							system("cls");
							cout << "Import test -> Choose your file -> Choose category -> Choose test:\n"; //выбор теста
							cout << "-------------------------------------------------\n";
							categor->ShowTests(category_index); //показываем на экран какие есть тесты в выбранной категории
							int test_index;
							cin >> test_index; //индекс теста
							if ((test_index >= categor->GetLenghtTestsVector(category_index)) || (test_index < 0)) //проверим валидность индекса теста
							{
								cout << "\nTry another choise\n";
								cout << "Press any key to continue\n"; _getch();
							}
							else
							{
								string test_name;
								test_name = categor->GetTestName(test_index);
								/// 
								/// ////Тут у нас есть имя теста который перепишем. 
								/// 
								//тут начинаем импорт

								ifstream in20("IMPORT\\" + filenames[counter]);
								if (in20.is_open())
								{
									//открыли исходный файл
									//начинаем с него читать
									string tmp_str_1;
									string tmp_str_2;
									ofstream out21("Tests\\" + test_name + ".my_ext");//------тест который заменим
									if (out21.is_open())
									{
										while (getline(in20, tmp_str_1) && getline(in20, tmp_str_2))
										{
											//пока читается - как считали так и загоняем в новый файл
											out21 << tmp_str_1 << endl;//вопрос
											out21 << tmp_str_2 << endl;//ответ
										}
										out21.close();//закрываем новый и старый файлы
										in20.close();
										cout << "\nImport done!";
										cout << "\nSUCCESS\n";
										cout << "Press any key to continue\n"; _getch();
									}
									else
									{
										//а если старый файл теста почему-то не открылся, уведомляем об етом
										in20.close();
										cout << "\nProblems with modifing file: " << "Tests\\" << test_name << ".my_ext\n";
										cout << "Press any key to continue\n"; _getch();
									}

								}
							}
						}


						break;
					}
					default:
						cout << "No such menu choise. Try again.\n";
						cout << "Press any key to continue\n"; _getch();
						break;
					}
					break;
				}
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
				cout << "33 - LOG OUT\n";

				cin.clear();
				cin >> choise;
				switch (choise)
				{
				case 0: //Take a new test
				{
					Sleep(300);
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

					//Category* categor = new Test();
					system("cls");
					cout << "Load test -> Choose category:\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
					cout << "-------------------------------------------------\n";
					categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
					cin.clear();
					cin >> category_index; //индекс категории
					if ((category_index >= categor->GetLenghtCategoriesVector()) || (category_index < 0))
					{
						cout << "\nTry another choise\n";
						cout << "Press any key to continue\n"; _getch();
					}
					else
					{
						//выберем тест
						system("cls");
						cout << "Load test -> Choose category -> Choose test:\n"; //выбор теста
						cout << "-------------------------------------------------\n";
						categor->ShowTests(category_index); //показываем на экран какие есть тесты в выбранной категории
						cin.clear();
						cin >> test_index; //индекс теста
						if ((test_index >= categor->GetLenghtTestsVector(category_index)) || (test_index < 0)) //проверим валидность индекса теста
						{
							cout << "\nTry another choise\n";
							cout << "Press any key to continue\n"; _getch();
						}
						else
						{
							test_name = categor->GetTestName(test_index);

							ifstream in16("User\\" + a.GetLogin() + "-SAVE-" + test_name + ".bin");
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
								cout << "You don't have this save!\n";
								cout << "Press any key to continue\n"; _getch();
							}
						}
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