#include "user_func.h"

int user_func::sign_in()
{
	stringstream sstream;
	string ss;
	string user_name;
	string user_password;
	//接收来自客户端的账号和密码
	int r;
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "来自客户端的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> user_name;
		sstream >> user_password;
		cout << user_name << endl;
		cout << user_password << endl;
	}
	sstream.str("");
	sstream.clear();
	int flag = 0;
	double user_balance;
	for (user* tmp : v_user)
	{
		if (tmp->get_user_name() == user_name && tmp->get_user_password() == user_password)
		{
			flag = tmp->get_user_type();
			user_balance = tmp->get_user_balance();
			if (flag == 1)
			{
				//all_business.set_user_balance(user_balance);
				//all_business.set_user_name(user_name);
				//all_business.set_user_password(user_password);
				//all_business.user_type = 1;
				//同时将all_consumer的标志位type置0，表示退出
				all_consumer.user_type = 0;
				cout << "flag == 1" << endl;
			}
			if (flag == 2)
			{
				all_consumer.set_user_balance(user_balance);
				all_consumer.set_user_name(user_name);
				all_consumer.set_user_password(user_password);
				all_consumer.user_type = 2;
				//同时将all_business的标志位type置0，表示退出
				all_business.user_type = 0;
				cout << "flag == 2" << endl;
			}
			//发送用户type和用户的余额
			sstream.str("");
			sstream.clear();
			//sstream << 55;
			//stringstream sss;
			if (flag == 1)
				sstream << flag;
			else if (flag == 2)
				sstream << flag << " " << user_balance;
			string s = sstream.str();
			cout << s << endl;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			//如果是消费者，展示购物车信息

			if (flag == 2)
				cart_func::show_cart(user_name);
			break;
		}
	}
	if (flag == 0)
	{
		sstream.str("");
		sstream.clear();
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}
	return flag;
}

int user_func::show_consumer()
{
	if (all_consumer.get_user_type() != 2)
	{
		cout << "Sorry, you haven't sign in, please sign in first." << endl;
		return -1;
	}
	cart_func::show_cart(all_consumer.get_user_name());
	return 0;
}