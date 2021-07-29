#include "user_func.h"

int user_func::sign_in()
{
	stringstream sstream;
	string ss;
	string user_name;
	string user_password;
	int user_type = 0;
	double user_balance = 0.0;
	int m, r;
	sstream.str("");
	sstream.clear();
	cout << "Please input your name:" << endl;
	get_string(user_name);
	//cout << "user_name" << user_name << endl;
	cout << "Please input your password:" << endl;
	get_string(user_password);
	//���˺ź����봫��ȥ
	sstream << user_name << " " << user_password;
	//sstream >> buff_out;
	strcpy(buff_out, (sstream.str()).c_str());
	//cout << buff_out << endl;
	send(clientSocket, buff_out, strlen(buff_out), NULL);
	//Ȼ������Ǳ�������Ϣ
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		////cout << "���Է���������Ϣ:" << buff_in << endl;
		ss = buff_in;
		//cout << "ss:" << ss << endl;
		sstream << ss;
		sstream >> user_type;
		//cout << "user_type " << user_type << endl;;
		if (user_type == 0 || user_type == 1)//��ʾ�˺��������
		{
			cout << "Sign in failed, please check your name and password." << endl;
		}
		/*else if (user_type == 1)
		{
			sstream >> user_balance;
			all_business.set_user_balance(user_balance);
			all_business.set_user_name(user_name);
			all_business.set_user_password(user_password);
			all_business.user_type = 1;
			//ͬʱ��all_consumer�ı�־λtype��0����ʾ�˳�
			all_consumer.user_type = 0;
			cout << "Sign in successfully!" << endl;
		}*/
		else if (user_type == 2)
		{
			sstream >> user_balance;
			all_consumer.set_user_balance(user_balance);
			all_consumer.set_user_name(user_name);
			all_consumer.set_user_password(user_password);
			all_consumer.user_type = 2;
			//ͬʱ��all_business�ı�־λtype��0����ʾ�˳�
			all_business.user_type = 0;
			//���շ���������Ϣ��չʾһ�������ߵĹ��ﳵ
			//cart_func::show_cart(user_name);
			cout << "Sign in successfully!" << endl;
			r = show_consumer();//�����������ܷ������Ĺ��ﳵ��Ϣ

		}


	}
	return user_type;

}

void user_func::get_int(int& n)
{
	char ch;
	cin.sync();
	cin >> n;
	ch = getchar();
	while (cin.fail() || ch != '\n')
	{
		cout << "Please input a number of type int:" << endl;
		cin.clear();
		cin.sync();
		cin >> n;
		ch = getchar();
	}
}

void user_func::get_double(double& n)
{
	char ch;
	cin.sync();
	cin >> n;
	ch = getchar();
	while (cin.fail() || ch != '\n')
	{
		cout << "Please input a number of type double:" << endl;
		cin.clear();
		cin.sync();
		cin >> n;
		ch = getchar();
	}
}

void user_func::get_string(string& n)
{
	cin.sync();
	getline(cin, n);
	unsigned int i;
	for (i = 0; i < strlen(n.c_str()); i++)
	{
		if (n.c_str()[i] == ' ')
		{
			cout << "Sorry, spaces are not supported, please input again:" << endl;
			i = 0;
			getline(cin, n);
		}
	}
}

int user_func::show_consumer()
{
	//����������Ƿ��¼
	if (all_consumer.get_user_type() != 2)
	{
		cout << "Sorry, you haven't sign in, please sign in first." << endl;
		return -1;
	}
	//����������Ѿ���½�ɹ���
	cout << "****************************************" << endl;
	cout << "Now begin to show your information." << endl;
	cout << "****************************************" << endl;
	cout << "Your name is " << all_consumer.get_user_name() << "." << endl;
	cout << "Your authority is a consumer." << endl;
	cout << "Your balance is " << all_consumer.get_user_balance() << "." << endl;
	//չʾ���ﳵ
	cart_func::show_cart(all_consumer.get_user_name());
	return 0;
}
