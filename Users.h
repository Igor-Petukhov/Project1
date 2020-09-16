#pragma once

class Base_User
{
private:
	map<string, long long> user_map; //сюда считываются логины и хеши паролей из файла
	map<string, string> id_card; //тут данные конкретного пользователя
	string login, password;
	string admin_login; //первый логин и есть логин админа
	int user_type = 0; //1-admin, 2-user
	long long password_hash;
	char x = '0';

public:
	
	string GetLogin()
	{
		return login;
	}

	bool IsAdmin()
	{
		if (user_type == 1)
			return 1;
		else
			return 0;
	}

	void LoadUsersMap()
	{
		user_map.clear();
		string login_in_file;
		long long tmp_hash;
		ifstream in1("User\\Users.txt");
		if (in1.is_open())
		{
			in1 >> admin_login;
			in1 >> tmp_hash;
			user_map[admin_login] = tmp_hash;
			while (in1 >> login_in_file)
			{
				in1 >> tmp_hash;
				user_map[login_in_file] = tmp_hash;
			}
			in1.close();
		}
		else
		{
			in1.close();
			Add_admin();
			LoadUsersMap();
		}
	}

	void Start()
	{
		LoadUsersMap();
		cout << "Login: ";
		cin >> login;
		if (!user_map[login])
		{
			Add_user();
			Start();
		}
		else
		{
			cout << "Welcome " << login << endl;
			if (IsPasswordCorrect())
			{
				cout << "\nCongrat! Access enable!" << endl; //Этот login можно запускать 
				if (login == admin_login)
				{
					cout << "ADMINISTRATOR MODE ACTIVATED\n";
					user_type = 1;
				}
				else
				{
					cout << "USER MODE ACTIVATED\n";
					user_type = 2;
				}
			}
			else
			{
				cout << "\nSorry! Access denied! Wrong password!" << endl;
				Start();
			}
		}
	}

	void Add_user()
	{
		cout << "Creating new user. Please, enter new password for login: " << login << endl;
		EnterPassword();
		ofstream out("User\\Users.txt", ios::app);
		if (out.is_open())
		{
			out << login << char(9) << password_hash << endl;
		}
		out.close();

		//заполняем данные пользователя
		id_card.clear();
		cout << "\nPlease, enter your surname: ";
		cin >> id_card["0_surname"];
		cout << "Please, enter your name: ";
		cin >> id_card["1_name"];
		cout << "Please, enter your fethersname: ";
		cin >> id_card["2_fathersname"];
		cout << "Please, enter your address: ";
		cin >> id_card["3_address"];
		cout << "Please, enter your telephone number: ";
		cin >> id_card["4_telephone"];

		//Сохраняем данные пользователя в новый файл
		ofstream out2("User\\" + login + ".txt");
		if (out2.is_open())
		{
			for (auto it = id_card.begin(); it != id_card.end(); it++)
			{
				out2 << it->first << " " << it->second << endl;
			}
		}
		out2.close();
		cout << "\nCongrat! User \"" << login << "\" is created! Please log in again!" << endl;
	}

	void Add_admin()
	{
		if (_mkdir("User") == -1)
		{
			cout << "Error!\nCouldn't create new directory. Check directory \"User\".\n";
			Sleep(5000);
			exit(0);
		}
		cout << "Creating Administrator\n";
		cout << "Login: ";
		cin >> login;
		EnterPassword();
		ofstream out1("User\\Users.txt");
		if (out1.is_open())
		{
			out1 << login << char(9) << password_hash << endl;
		}
		out1.close();
		cout << "\nCongrat! Admin is created! Please log in again!" << endl;
	}

	bool IsPasswordCorrect()
	{
		EnterPassword();
		return (user_map[login] == password_hash);
	}

	void EnterPassword()
	{
		password.clear();
		x = '0';
		cout << "Password: ";
		while (x != char(13))
		{
			x = _getch();
			if (x != char(13))
			{
				cout << "*";
				password += x;
			}
		}
		hash<string> t;
		password_hash = t(password);
	}
};

