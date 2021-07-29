#include "goods_func.h"
#include <iostream>


void goods_func::goods_init_interface()
{
	cout << "****************************************" << endl;
	cout << "Here is all the goods." << endl;
	cout << "****************************************" << endl;
	stringstream sstream;
	string ss;
	string goods_name;
	string goods_owner;
	string goods_description;
	string type;
	int goods_type = 0;
	double goods_price;
	double business_discount;
	double all_discount;
	double goods_price_change;
	int goods_surplus;
	int i = 1, r, m;
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> goods_type;
	}
	if (goods_type == -1)
	{
		cout << "No goods in the platform." << endl;
	}
	while (goods_type != -1)
	{
		sstream >> goods_owner;
		sstream >> goods_price;
		sstream >> business_discount;
		sstream >> all_discount;
		sstream >> goods_price_change;
		sstream >> goods_surplus;

		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			//ss = buff_in;
			//sstream << ss;
			//sstream >> goods_name;
			goods_name = buff_in;
		}
		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			goods_description = buff_in;
			//sstream << ss;
			//sstream >> goods_description;
		}
		if (goods_type == 0)
			type = "Food";
		else if (goods_type == 1)
			type = "Clothes";
		else if (goods_type == 2)
			type = "Book";
		cout << i << ")" << type << ":" << goods_name << endl;
		cout << "The description:         " << goods_description << endl;
		cout << "The original price:      " << goods_price << endl;
		cout << "The business discount:   " << business_discount << endl;
		cout << "The platform discount:   " << all_discount << endl;
		cout << "The current price:       " << goods_price_change << endl;
		cout << "The surplus:             " << goods_surplus << endl;
		cout << "The owner:               " << goods_owner << endl;
		cout << "****************************************" << endl;
		i++;

		//接收下一个
		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			ss = buff_in;
			sstream << ss;
			sstream >> goods_type;
		}
	}
}

int goods_func::goods_name_interface()
{
	stringstream sstream;
	string ss;
	string goods_name;
	string goods_owner;
	string goods_description;
	string type;
	int goods_type = 0;
	double goods_price;
	double business_discount;
	double all_discount;
	double goods_price_change;
	int goods_surplus;
	int i = 1, r, m, flag = 0;
	cout << "****************************************" << endl;
	cout << "Please input the goods's name:" << endl;
	getline(cin, goods_name);
	//goods_name = "shoes";
	//然后发送给服务器名称
	sstream.str("");
	sstream.clear();
	sstream << goods_name;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket, buff_out, strlen(buff_out), NULL);

	cout << "****************************************" << endl;
	cout << "Here is all the " << goods_name << "." << endl;
	cout << "****************************************" << endl;

	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> goods_type;
	}
	if (goods_type == -1)
	{
		cout << "No goods in the platform." << endl;
	}
	while (goods_type != -1)
	{
		flag = 1;
		sstream >> goods_owner;
		sstream >> goods_price;
		sstream >> business_discount;
		sstream >> all_discount;
		sstream >> goods_price_change;
		sstream >> goods_surplus;

		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			goods_name = buff_in;

		}
		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			goods_description = buff_in;
		}
		if (goods_type == 0)
			type = "Food";
		else if (goods_type == 1)
			type = "Clothes";
		else if (goods_type == 2)
			type = "Book";
		cout << i << ")" << type << ":" << goods_name << endl;
		cout << "The description:         " << goods_description << endl;
		cout << "The original price:      " << goods_price << endl;
		cout << "The business discount:   " << business_discount << endl;
		cout << "The platform discount:   " << all_discount << endl;
		cout << "The current price:       " << goods_price_change << endl;
		cout << "The surplus:             " << goods_surplus << endl;
		cout << "The owner:               " << goods_owner << endl;
		cout << "****************************************" << endl;
		i++;

		//接收下一个
		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			ss = buff_in;
			sstream << ss;
			sstream >> goods_type;
		}
	}
	return flag;
}