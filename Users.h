#pragma once

class Base_User
{
public:
	map<string, long long> user_map;
	string surname, name, fathersname, address, telephone_number, login, password;
	long long password_hash;
	int user_type; //1 - admin, 2 - user
	char x = '0';

	void LoadUsersMap()
	{
		user_map.clear();
		string login_in_file;
		long long tmp_hash;
		ifstream in1("Users.txt");
		if (in1.is_open())
		{
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
		ofstream out("Users.txt", ios::app);
		if (out.is_open())
		{
			out << login << char(9) << password_hash << endl;

		}
		out.close();
		cout << "\nCongrat! User is created! Please log in again!" << endl;
	}

	void Add_admin()
	{
		cout << "Creating Administrator\n";
		cout << "Login: ";
		cin >> login;
		EnterPassword();

		ofstream out1("Users.txt");
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

