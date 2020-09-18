#pragma once
class Test
{
	int questions = 0;
	string name;
public:

	Test(string str) :name(str) {};
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

	void AddTest()
	{
		if (!DirectoryExists("Tests"))
		{
			if (_mkdir("Tests") == -1)
			{
				cout << "Error!\nCouldn't create new directory. Check directory \"Tests\".\n";
				Sleep(5000);
				exit(1);
			}
		}
		ofstream out2("Tests\\" + name + ".txt");
		if (out2.is_open())
		{
			out2 << questions << endl;
			int tmp = 1;
			do
			{


				cout << "0 - Back\n";
				cout << "1 - Add question with answer\n";
				cin >> tmp;
			} while (tmp);
		}
		out2.close();
		cout << "\nCongrat! Test \"" << name << "\" is created!" << endl;
	}

	string AddQuestion()
	{
		cin.clear();
		string new_question;
		system("cls");
		cout << "Please, enter question:\n";
		cin >> new_question;
		return new_question;
	}

	string AddAnswer()
	{
		cin.clear();
		string new_answer;
		system("cls");
		cout << "Please, enter answer:\n";
		cin >> new_answer;
		return new_answer;
	}



};
