#pragma once

class UserTakesTest
{
	int category_index, test_index;
	int questions_all, correct_answers, mark_A = 12;
	int mark, percentage;
	string tmp_str_1, tmp_str_2, tmp_str_3;
	string test_name;
public:
	string GetTestName()
	{
		return test_name;
	}

	string GetQuestionsAll()
	{
		return to_string(questions_all);
	}

	string GetCorrectAnswers()
	{
		return to_string(correct_answers);
	}

	string GetPercentage()
	{
		return to_string(percentage);
	}

	string GetMark()
	{
		return to_string(mark);
	}

	UserTakesTest(Base_User base_user_in, int in_category_index = -1, int in_test_index = -1,
		int in_questions_all = 0, int in_correct_answers = 0, int in_mark_A = 12,
		int in_mark = 0, int in_percentage = 0, string in_tmp_str_1 = "", string in_tmp_str_2 = "",	string in_test_name = "")
	{
		system("cls");
		Category* categor = new Test();
		category_index = in_category_index;

		//если юзер загрузил прошлый сеанс, то файл надо удалить. Так как наличие файла - признак того, что юзер сохранялся
		if (category_index != -1) //признак загрузки прошлого сеанса (переданы считаные состояния переменных)
		{
			string tmp5 = "User\\" + base_user_in.GetLogin() + "-SAVE" + ".bin";
			remove(tmp5.c_str());
		}
		
		test_index = in_test_index;
		questions_all = in_questions_all;
		correct_answers = in_correct_answers;
		mark_A = in_mark_A;
		mark = in_mark;
		percentage = in_percentage;
		tmp_str_1 = in_tmp_str_1;
		tmp_str_2 = in_tmp_str_2;
		test_name = in_test_name;

		
		if (category_index == -1) //если индекс категории не передан, то это НЕ ЗАГРУЗКА а тест с самого начала и етот индекс надо выбрать
		{
			system("cls");
			cout << "Take test -> Choose category:\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
			cout << "-------------------------------------------------\n";
			categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
			cin.clear();

			cin >> category_index; //индекс категории
		}
		if ((category_index >= categor->GetLenghtCategoriesVector()) || (category_index < 0))
		{
			cout << "\nTry another choise\n";
		}
		else
		{
			if (test_index == -1) //если индекс теста не передан, то это НЕ ЗАГРУЗКА а тест с самого начала и етот индекс теста надо выбрать
			{
				system("cls");
				cout << "Take test -> Choose category -> Choose test:\n"; //выбор теста
				cout << "-------------------------------------------------\n";
				categor->ShowTests(category_index); //показываем на экран какие есть тесты в выбранной категории
				cin.clear();
				cin >> test_index; //индекс теста
			}
			if ((test_index >= categor->GetLenghtTestsVector(category_index)) || (test_index < 0))
			{
				cout << "\nTry another choise\n";
			}
			else
			{
				if (in_test_name == "") //если имя теста не передано, то это НЕ ЗАГРУЗКА и имя теста надо выбрать
				{
					test_name = categor->GetTestName(test_index);
				}
				else
				{
					test_name = in_test_name;
				}
				system("cls");
				cout << "--------------------START TEST-------------------" << endl;
				cout << "Test name: " << categor->GetTestName(test_index) << endl;
				cout << "if you need to SAVE print \"SAVE\"" << endl;
				cout << "-------------------------------------------------\n";
				Sleep(300);
				ifstream in12("Tests\\" + test_name + ".txt");
				cin.ignore();
				if (in12.is_open())
				{
					bool marker = 0; //если маркер станет 1 - то значит юзер выбрал сохраниться
					int tmp = 0;
					while (getline(in12, tmp_str_1) && getline(in12, tmp_str_2))
					{
						tmp++;
						if (tmp <= (questions_all))
							continue;
						cout << "\n-------------------QUESTION #" << ++questions_all << "-------------------" << endl;
						cout << "Question: " << tmp_str_1 << endl << endl;
						cout << "Your answer: ";
						tmp_str_3 = "";
						getline(cin, tmp_str_3); //считали ответ user-a в стр3


						///////////////////////////////////////////////////////////////
						//если юзер захотел сохраниться
						if (tmp_str_3 == "SAVE")
						{
							marker = 1; //признак того, что было выбрано сохраниться
							
							ofstream out15("User\\" + base_user_in.GetLogin() + "-SAVE" + ".bin");
							if (out15.is_open())
							{
								out15 << category_index << endl;
								out15 << test_index << endl;
								out15 << questions_all << endl;
								out15 << correct_answers << endl;
								out15 << mark_A << endl;
								out15 << mark << endl;
								out15 << percentage << endl;
								out15 << tmp_str_1 << endl;
								out15 << tmp_str_2 << endl;
								out15 << test_name << endl;
								cout << "\nSAVE DONE" << endl;
								break;
							}
							out15.close();
						}
						///////////////////////////////////////////////////////////////

						if (!marker)
						{
							//правильный ответ уже в стр2
							if (!strcmp(tmp_str_2.c_str(), tmp_str_3.c_str()))
							{
								cout << "                             correct\n";
								correct_answers++;
							}
							else
							{
								cout << "                              wrong\n";
								cout << "correct answer is: " << tmp_str_2 << endl;
							}
						}
					}
					if (!marker)
					{
						cout << "=================================================" << endl;
						mark = ((float)mark_A / questions_all) * correct_answers;
						percentage = (100 / questions_all) * correct_answers;
						cout << "Your results:\ncorrect_answers: " << correct_answers << "\tpercents: " << percentage << "%\t mark: " << mark << endl;
						if (mark == 12)
							cout << "CONGRATULATIONS!!!" << endl;
						cout << "Press any key to continue\n"; _getch();


						//saving results

						//заносим результат в карточку абонента
						base_user_in.LoadUserInfo(base_user_in.GetLogin());
						/////////////////////////////
						///загнать текущее время в строку
						time_t rawtime;
						time(&rawtime);
						char buffer[80];
						strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S <----------------", localtime(&rawtime));
						string tmp_time(buffer);
						/////////////////////////////

						base_user_in.id_card.push_back(make_pair("test time:", tmp_time));
						base_user_in.id_card.push_back(make_pair("test name:", GetTestName()));
						base_user_in.id_card.push_back(make_pair("questions all:", GetQuestionsAll()));
						base_user_in.id_card.push_back(make_pair("correct answers:", GetCorrectAnswers()));
						base_user_in.id_card.push_back(make_pair("percentage:", GetPercentage()));
						base_user_in.id_card.push_back(make_pair("mark:", GetMark()));
						base_user_in.SaveUserInfo(base_user_in.GetLogin());
						base_user_in.LoadUserInfo(base_user_in.GetLogin());
						system("cls");
						cout << "---------------------MY STAT---------------------\n";
						base_user_in.ShowUserInfo(base_user_in.GetLogin());
					}
					marker = 0;
				}
				in12.close();
			}
		}
	}
};