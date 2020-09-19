#pragma once

class UserTakesTest
{
	int category_index, test_index;
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

	UserTakesTest() 
	{
		system("cls");
		Category* categor = new Test();
		cout << "Choose category\n"; //тест выберем пройдя по иерархии от категории к конкретному тесту
		categor->ShowCategoriesVector(); //сначала выбираем категорию, далее будет выбор теста
		cin.clear();

		cin >> category_index; //индекс категории

		if ((category_index >= categor->GetLenghtCategoriesVector()) || (category_index < 0))
		{
			cout << "\nTry another choise\n";
			Sleep(2000);
		}
		else
		{
			cout << "Choose test\n"; //выбор теста
			categor->ShowTests(category_index); //показываем на экран какие есть тесты в выбранной категории
			cin.clear();
			cin >> test_index; //индекс теста
			if ((test_index >= categor->GetLenghtTestsVector(category_index)) || (test_index < 0))
			{
				cout << "\nTry another choise\n";
				Sleep(2000);
			}
			else
			{
				test_name = categor->GetTestName(test_index);
				cout << "START TEST" << endl;
				cout << categor->GetTestName(test_index) << endl;
				cout << "if you need to SAVE print \"SAVE\"" << endl;
				cout << "--------------------------------" << endl;
				Sleep(500);
				ifstream in12("Tests\\" + categor->GetTestName(test_index) + ".txt");
				cin.ignore();
				if (in12.is_open())
				{
					questions_all = 0;
					correct_answers = 0;
					while (getline(in12, tmp_str_1) && getline(in12, tmp_str_2))
					{
						cout << "Question #" << ++questions_all << ": " << tmp_str_1 << endl;
						cout << "Your answer: ";
						tmp_str_3 = "";
						getline(cin, tmp_str_3); //считали ответ user-a в стр3


						//////////////////////////////
						//если юзер захотел сохраниться
						if (tmp_str_3 == "SAVE")
						{
							///
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
					_getch();
					cin.ignore();
				}
				in12.close();
			}
		}
	}
};