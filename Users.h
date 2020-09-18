#pragma once

class Base_User
{
private:
	map<string, string> id_card; //тут данные конкретного пользователя
	string login, password;
	string admin_login; //первый логин и есть логин админа
	int user_type = 0; //1-admin, 2-user
	long long password_hash, new_password_hash;
	char x = '0';

public:
	map<string, long long> user_map; //сюда считываются логины и хеши паролей из файла
	
	string GetAdmLogin()
	{
		return admin_login;
	}

	string GetLogin()
	{
		return login;
	}

	int GetUserType()
	{
		return user_type;
	}

	bool IsAdmin()
	{
		if (user_type == 1)
			return 1;
		else
			return 0;
	}

	bool LoadUsersMap()
	{
		try
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
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	bool SaveUsersMap()
	{
		try
		{
			ofstream out4("User\\Users.txt");
			if (out4.is_open())
			{
				for (auto it = user_map.begin(); it != user_map.end(); it++)
				{
					out4 << it->first << char(9) << it->second << endl;
				}
			}
			out4.close();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	void Start()
	{
		LoadUsersMap();
		cout << "Login: ";
		cin >> login;
		if (!user_map[login])
		{
			Add_user(login);
			cout << "Please log in again!" << endl;
			Start();
		}
		else
		{
			cout << "Welcome " << login << endl;
			if (IsPasswordCorrect())
			{
				cout << "\nCongrat! Access enable!" << endl; //Этот login можно запускать 
				Sleep(500);
				if (login == admin_login)
				{
					//admin mode - в системе админ
					user_type = 1;
				}
				else
				{
					//user mode - в системе юзер
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

	bool Add_user(string login)
	{
		try
		{
			cout << "Creating new user. Please, enter new password for login \"" << login << "\"" << endl;
			EnterPassword();
			ofstream out("User\\Users.txt", ios::app);
			if (out.is_open())
			{
				out << login << char(9) << password_hash << endl;
			}
			out.close();

			//заполняем данные пользователя
			id_card.clear();
			cout << "\nPlease, enter surname: ";
			cin >> id_card["0_surname"];
			cout << "Please, enter name: ";
			cin >> id_card["1_name"];
			cout << "Please, enter fathersname: ";
			cin >> id_card["2_fathersname"];
			cout << "Please, enter address: ";
			cin >> id_card["3_address"];
			cout << "Please, enter telephone number: ";
			cin >> id_card["4_telephone"];

			//Сохраняем данные пользователя в новый файл
			ofstream out2("User\\" + login + ".txt");
			if (out2.is_open())
			{
				for (auto it = id_card.begin(); it != id_card.end(); it++)
				{
					out2 << it->first << char(9) << it->second << endl;
				}
			}
			out2.close();
			cout << "\nCongrat! User \"" << login << "\" is created!" << endl;
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
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

	bool ChangeAdminLogin(string new_login)
	{
		if (user_map[new_login])
			return 0;
		else
		{
			LoadUsersMap();
			user_map.erase(admin_login);
			ofstream out3("User\\Users.txt");
			if (out3.is_open())
			{
				out3 << new_login << char(9) << password_hash << endl;
				for (auto it = user_map.begin(); it != user_map.end(); it++)
				{
					out3 << it->first << char(9) << it->second << endl;
				}
			}
			out3.close();
			LoadUsersMap();
			return 1;
		}
	}

	bool ChangeAdminPswd(string new_adm_pswd)
	{
		hash<string> t;
		new_password_hash = t(new_adm_pswd);
		try
		{
			LoadUsersMap();
			user_map.erase(admin_login);
			ofstream out3("User\\Users.txt");
			if (out3.is_open())
			{
				out3 << admin_login << char(9) << new_password_hash << endl;
				for (auto it = user_map.begin(); it != user_map.end(); it++)
				{
					out3 << it->first << char(9) << it->second << endl;
				}
			}
			out3.close();
			LoadUsersMap();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	void LoadUserInfo(string login)
	{
		id_card.clear();
		ifstream in5("User\\" + login + ".txt");
			if (in5.is_open())
			{
				string tmp_str_1, tmp_str_2;
				while (in5 >> tmp_str_1)
				{
					in5 >> tmp_str_2;
					id_card[tmp_str_1] = tmp_str_2;
				}
			}
			in5.close();
	}

	void ShowUserInfo(string login)
	{
		for (auto i = id_card.begin(); i != id_card.end(); i++)
		{
			cout << i->first << " " << i->second << endl;
		}
	}

	void SetUserInfo(string login)
	{
		id_card.clear();
		ofstream out5("User\\" + login + ".txt");
		if (out5.is_open())
		{
			cout << "Type \"exit\" to stop setting user \"" << login << "\"" << endl;
			string tmp_str_1, tmp_str_2;
			while (true)
			{
				cin >> tmp_str_1;
				if (tmp_str_1 == "exit")
					break;
				cin >> tmp_str_2;
				if (tmp_str_2 == "exit")
					break;
				id_card[tmp_str_1] = tmp_str_2;
			}
			out5.close();
		}
	}

	bool SaveUserInfo(string login)
	{
		try
		{
			ofstream out7("User\\" + login + ".txt");
			if (out7.is_open())
			{
				for (auto it = id_card.begin(); it != id_card.end(); it++)
				{
					out7 << it->first << char(9) << it->second << endl;
				}
			}
			out7.close();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}




};




