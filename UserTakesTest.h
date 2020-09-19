#pragma once

class UserTakesTest
{
	int category_index = 0, test_index = 0;
	int questions_all, correct_answers, mark_A = 12;
	float mark, percentage;
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

	UserTakesTest(Base_User base_user_in, int category_index = 0, int test_index = 0,
		int questions_all = 0, int correct_answers = 0, int mark_A = 12,
		float mark = 0, float percentage = 0, string tmp_str_1 = "", string tmp_str_2 = "", string tmp_str_3 = "",
		string test_name = "")
	{
		system("cls");
		Category* categor = new Test();
		if (category_index == 0)
		{
			cout << "Choose category\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
			categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
			cin.clear();

			cin >> category_index; //индекс категории
		}
		if ((category_index >= categor->GetLenghtCategoriesVector()) || (category_index < 0))
		{
			cout << "\nTry another choise\n";
			Sleep(2000);
		}
		else
		{
			if (test_index == 0)
			{
				cout << "Choose test\n"; //выбор теста
				categor->ShowTests(category_index); //показываем на экран какие есть тесты в выбранной категории
				cin.clear();
				cin >> test_index; //индекс теста
			}
			if ((test_index >= categor->GetLenghtTestsVector(category_index)) || (test_index < 0))
			{
				cout << "\nTry another choise\n";
				Sleep(2000);
			}
			else
			{
				if (test_name == "")
				{
					test_name = categor->GetTestName(test_index);
				}
				cout << "START TEST" << endl;
				cout << categor->GetTestName(test_index) << endl;
				cout << "if you need to SAVE print \"SAVE\"" << endl;
				cout << "--------------------------------" << endl;
				Sleep(500);
				ifstream in12("Tests\\" + test_name + ".txt");
				cin.ignore();
				if (in12.is_open())
				{
					int tmp = 0;
					while (getline(in12, tmp_str_1) && getline(in12, tmp_str_2))
					{
						tmp++;
						if (tmp != (questions_all - 1))
							continue;
						cout << "Question #" << ++questions_all << ": " << tmp_str_1 << endl;
						cout << "Your answer: ";
						tmp_str_3 = "";
						getline(cin, tmp_str_3); //считали ответ user-a в стр3


						//////////////////////////////
						//если юзер захотел сохраниться
						if (tmp_str_3 == "SAVE")
						{
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
								cout << "Press any key to continue\n"; _getch();
								break;
							}
							out15.close();
						}
						///////////////////////////////


						//правильный ответ уже в стр2
						cout << "===correct:" << tmp_str_2 << "===users:" << tmp_str_3 << "===" << endl;
						if (!strcmp(tmp_str_2.c_str(), tmp_str_3.c_str()))
						{
							cout << "CORRECT\n";
							correct_answers++;
						}
						else
						{
							cout << "WRONG\n";
						}
					}
					cout << "--------------------------------" << endl;
					mark = ((float)mark_A / questions_all) * correct_answers;
					percentage = (100. / questions_all) * correct_answers;
					cout << "Your results:\ncorrect_answers: " << correct_answers << "\tpercents: " << percentage << "%\t mark: " << mark << endl;
					if (mark == 12)
						cout << "CONGRATULATIONS!!!" << endl;
					cout << "Press any key to continue\n"; _getch();
					cin.ignore();
				}
				in12.close();
			}
		}
	}
};