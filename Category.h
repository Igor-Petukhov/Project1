#pragma once

//Prototype

class Category
{
public:
	virtual Category* clone() = 0;

	//Проверяет существует ли папка
	BOOL DirectoryExists(const char* dirName)
	{
		DWORD attribs = ::GetFileAttributesA(dirName);
		if (attribs == INVALID_FILE_ATTRIBUTES)
		{
			return false;
		}
		return (attribs & FILE_ATTRIBUTE_DIRECTORY);
	}

	virtual bool AddCategory(string new_category_name) = 0;
	virtual void LoadCategoriesVector() = 0;
	virtual bool IsCategoryNew(string new_name) = 0;
	virtual void ShowCategoriesVector() = 0;
	virtual int GetLenghtCategoriesVector() = 0;
	virtual bool AddTest(string test_name, int category_number) = 0;
	virtual string AddQuestion() = 0;
	virtual string AddAnswer() = 0;
	virtual void LoadConcreteCategoryVector(int category_number) = 0;
	virtual void ShowTests(int category_number) = 0;
	virtual int GetLenghtTestsVector(int category_number) = 0;
	virtual void AddQuestionWithAnswer(int test_index, int category_index) = 0;
	virtual string GetTestName(int test_index) = 0;
};

class Test : public Category
{
	string category_name;
	string test_name;
	vector <string> categories;
	vector <string> tests;
public:

	Test() {}
	Category* clone() override
	{
		return new Test();
	}

	bool AddCategory(string new_category_name) override
	{
		if (IsCategoryNew(new_category_name))
		{
			if (!DirectoryExists("Categories"))
			{
				if (_mkdir("Categories") == -1)
				{
					cout << "Error!\nCouldn't create new directory. Check directory \"Categories\".\n";
					Sleep(5000);
					return 0;
				}
			}
			ofstream out7("Categories\\Categories.txt", ios::app);
			if (out7.is_open())
			{
				out7 << new_category_name << endl;
			}
			out7.close();
			cout << "\nCongrat! Category \"" << new_category_name << "\" is created!" << endl;
			return 1;
		}
		else
		{
			cout << "Error!\nSuch category already exists\n";
			return 0;
		}
	}

	void LoadCategoriesVector() override
	{
		categories.clear();
		string tmp_str;
		ifstream in8("Categories\\Categories.txt");
		if (in8.is_open())
		{
			while (getline(in8, tmp_str))
			{
				categories.push_back(tmp_str);
			}
			in8.close();
		}
	}

	bool IsCategoryNew(string new_name) override
	{
		LoadCategoriesVector();
		for (int i = 0; i < categories.size(); i++)
		{
			if (categories[i] == new_name)
				return 0;
		}
		return 1;
	}

	void ShowCategoriesVector() override
	{
		LoadCategoriesVector();
		for (int i = 0; i < categories.size(); i++)
		{
			cout << i << " - " << categories[i] << endl;
		}
	}

	int GetLenghtCategoriesVector() override
	{
		LoadCategoriesVector();
		return categories.size();
	}

	bool AddTest(string test_name, int category_number) override
	{
		try
		{
			if (!DirectoryExists("Tests"))
			{
				if (_mkdir("Tests") == -1)
				{
					cout << "Error!\nCouldn't create new directory. Check directory \"Tests\".\n";
					return 0;
				}
			}

			//создаём пустой файл для теста
			ofstream out2("Tests\\" + test_name + ".txt");
			out2.close();

			//в файл конкретной категории дописываем название нового теста
			ofstream out8("Categories\\" + categories[category_number] + ".txt", ios::app);
			if (out8.is_open())
				out8 << test_name << endl;
			else
				return 0;
			out8.close();
			cout << "\nCongrat! Test \"" << test_name << "\" is created!" << endl;
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}

	}

	string AddQuestion() override
	{
		cin.clear();
		cin.ignore();
		string new_question;
		system("cls");
		cout << "Please, enter question:\n";
		getline(cin, new_question);
		return new_question;
	}

	string AddAnswer() override
	{
		cin.clear();
		string new_answer;
		system("cls");
		cout << "Please, enter answer:\n";
		getline(cin, new_answer);
		return new_answer;
	}

	void LoadConcreteCategoryVector(int category_number) override
	{
		tests.clear();
		categories.clear();
		LoadCategoriesVector();
		string tmp_str;
		ifstream in9("Categories\\" + categories[category_number] + ".txt"); //Открыли файл категории. Там список тестов по етой категории.
		if (in9.is_open())
		{
			while (getline(in9, tmp_str))
			{
				tests.push_back(tmp_str);
			}
			in9.close();
		}
	}

	void ShowTests(int category_number) override
	{
		tests.clear();
		LoadConcreteCategoryVector(category_number);
		for (int i = 0; i < tests.size(); i++)
		{
			cout << i << " - " << tests[i] << endl;
		}
	}

	int GetLenghtTestsVector(int category_number) override
	{
		tests.clear();
		LoadConcreteCategoryVector(category_number);
		return tests.size();
	}

	void AddQuestionWithAnswer(int test_index, int category_index) override
	{
		int tmp = 1;
		do
		{
			//в файл конкретного теста дописываем поочереди построчно пары вопрос-ответ
			ofstream out10("Tests\\" + tests[test_index] + ".txt", ios::app);
			if (out10.is_open())
			{
				out10 << AddQuestion() << endl;
				out10 << AddAnswer() << endl;
			}
			out10.close();
			cout << "Question with answer were SUCCESSfully added!\n";
			cout << "\n0 - Back\n";
			cout << "1 - Add question with answer\n";
			cin.clear();
			cin >> tmp;
		} while (tmp);
		cin.clear();
	}

	string GetTestName(int test_index) override
	{
		return (tests[test_index]);
	}

};