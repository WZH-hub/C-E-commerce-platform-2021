#include "goods_func.h"
#include <iostream>

void goods_func::goods_init_interface()
{
	//按照类别，商家名称，原价，商家折扣，平台折扣，现价，剩余量
	//传回商品名称
	//传回商品描述
	//传回为-1结束
	stringstream sstream;
	for (goods* tmp : v_goods)
	{
		if (tmp->get_goods_type() == 0)
		{
			//这里发送第一份
			goods_Food* p_1 = dynamic_cast<goods_Food*>(tmp);
			sstream.str("");
			sstream.clear();
			sstream << tmp->get_goods_type() << " ";
			sstream << tmp->get_goods_owner() << " ";
			sstream << tmp->get_goods_price() << " ";
			sstream << p_1->discount << " ";
			sstream << all_discount[0] << " ";
			sstream << p_1->get_goods_price_change() << " ";
			sstream << tmp->get_goods_surplus();
			//memset(buff_out, 0, sizeof(buff_out));
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

			//这里发送第二份
			sstream << tmp->get_goods_name();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

			//这里发送第三份
			sstream << tmp->get_goods_description();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

		}
		if (tmp->get_goods_type() == 1)
		{
			//这里发送第一份
			goods_Clothes* p_1 = dynamic_cast<goods_Clothes*>(tmp);
			sstream.str("");
			sstream.clear();
			sstream << tmp->get_goods_type() << " ";
			sstream << tmp->get_goods_owner() << " ";
			sstream << tmp->get_goods_price() << " ";
			sstream << p_1->discount << " ";
			sstream << all_discount[1] << " ";
			sstream << p_1->get_goods_price_change() << " ";
			sstream << tmp->get_goods_surplus();
			//memset(buff_out, 0, sizeof(buff_out));
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

			//这里发送第二份
			sstream << tmp->get_goods_name();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

			//这里发送第三份
			sstream << tmp->get_goods_description();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

		}
		if (tmp->get_goods_type() == 2)
		{
			//这里发送第一份
			goods_Book* p_1 = dynamic_cast<goods_Book*>(tmp);
			sstream.str("");
			sstream.clear();
			sstream << tmp->get_goods_type() << " ";
			sstream << tmp->get_goods_owner() << " ";
			sstream << tmp->get_goods_price() << " ";
			sstream << p_1->discount << " ";
			sstream << all_discount[2] << " ";
			sstream << p_1->get_goods_price_change() << " ";
			sstream << tmp->get_goods_surplus();
			//memset(buff_out, 0, sizeof(buff_out));
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

			//这里发送第二份
			sstream << tmp->get_goods_name();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

			//这里发送第三份
			sstream << tmp->get_goods_description();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();

		}

	}
	//表示结束
	sstream.str("");
	sstream.clear();
	sstream << -1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
}

int goods_func::goods_name_interface()
{
	int flag = 0;
	string goods_name;
	string ss;
	stringstream sstream;
	int r;
	//server::send_ACK();
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "来自客户端的消息:" << buff_in << endl;
		goods_name = buff_in;
	}
	sstream.str("");
	sstream.clear();
	for (goods* tmp : v_goods)
	{
		if (tmp->get_goods_name() == goods_name)
		{
			flag = 1;
			if (tmp->get_goods_type() == 0)
			{
				//这里发送第一份
				goods_Food* p_1 = dynamic_cast<goods_Food*>(tmp);
				sstream.str("");
				sstream.clear();
				sstream << tmp->get_goods_type() << " ";
				sstream << tmp->get_goods_owner() << " ";
				sstream << tmp->get_goods_price() << " ";
				sstream << p_1->discount << " ";
				sstream << all_discount[0] << " ";
				sstream << p_1->get_goods_price_change() << " ";
				sstream << tmp->get_goods_surplus();
				//memset(buff_out, 0, sizeof(buff_out));
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

				//这里发送第二份
				sstream << tmp->get_goods_name();
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

				//这里发送第三份
				sstream << tmp->get_goods_description();
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

			}
			if (tmp->get_goods_type() == 1)
			{
				//这里发送第一份
				goods_Clothes* p_1 = dynamic_cast<goods_Clothes*>(tmp);
				sstream.str("");
				sstream.clear();
				sstream << tmp->get_goods_type() << " ";
				sstream << tmp->get_goods_owner() << " ";
				sstream << tmp->get_goods_price() << " ";
				sstream << p_1->discount << " ";
				sstream << all_discount[1] << " ";
				sstream << p_1->get_goods_price_change() << " ";
				sstream << tmp->get_goods_surplus();
				//memset(buff_out, 0, sizeof(buff_out));
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

				//这里发送第二份
				sstream << tmp->get_goods_name();
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

				//这里发送第三份
				sstream << tmp->get_goods_description();
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

			}
			if (tmp->get_goods_type() == 2)
			{
				//这里发送第一份
				goods_Book* p_1 = dynamic_cast<goods_Book*>(tmp);
				sstream.str("");
				sstream.clear();
				sstream << tmp->get_goods_type() << " ";
				sstream << tmp->get_goods_owner() << " ";
				sstream << tmp->get_goods_price() << " ";
				sstream << p_1->discount << " ";
				sstream << all_discount[2] << " ";
				sstream << p_1->get_goods_price_change() << " ";
				sstream << tmp->get_goods_surplus();
				//memset(buff_out, 0, sizeof(buff_out));
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

				//这里发送第二份
				sstream << tmp->get_goods_name();
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

				//这里发送第三份
				sstream << tmp->get_goods_description();
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				server::reve_ACK();

				sstream.str("");
				sstream.clear();

			}
		}
	}
	sstream.str("");
	sstream.clear();
	sstream << -1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
	//如果没有找到
	if (flag == 0)
	{
		sstream.str("");
		sstream.clear();
		sstream << -1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}
	return flag;
}