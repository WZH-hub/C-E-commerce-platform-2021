#include <iostream>
#include "cart.h"
#include "goods.h"
#include "client.h"
#include "user.h"
#include "cart_func.h"
#include "goods_func.h"
#include "screen_jump.h"
#include "user_func.h"

using namespace std;
/*vector<goods*> v_goods;
vector<user*> v_user;
vector<goods*> business_goods; //������ŵ�¼�̼����ڵ�������Ʒ
vector<cart*> v_cart;          //���е��˵Ĺ��ﳵ��Ϣ*/

//ȫ�ֱ��������û���½�����������¸�ֵ
user_Business all_business(0, "#", "#", 0.0);
user_Consumer all_consumer(0, "#", "#", 0.0);
//user_Consumer all_consumer(2, "ljr", "asd", 1000.0);
//����Ա����Ϣд��
user_Business admin(3, "admin", "commerce", 0.0);

//һ�����ڵ���Ʒ����
#define ALL 3
double all_discount[ALL] = { 1.0 }; //�������Ϣ

SOCKET clientSocket;
SOCKET serverSocket2;
SOCKET clientSocket2;

char buff_in[1024];//��server���뵽client��
char buff_out[1024];//��client�����server��




int main()
{
	client CLIENT;
	CLIENT.creat();
	int i, id = 0;
	stringstream sstream;
	string ss;
	//user_func::get_int(id);
	//sstream << id;
	//cout << sstream.str();
	//ss = sstream.str();
	//strcpy(buff_out, (sstream.str()).c_str());
	//cout << "buff" << buff_out << endl;
	//send(clientSocket, buff_out, strlen(buff_out), NULL);
	//m = user_func::sign_in();
	//client::send_ACK();
	//cart_func::generate_order();
	//goods_func::goods_name_interface();
	/*
	while (1) {
		cout << "�����㷢�͵���Ϣ:";
		//cin >> buff_out;
		fflush(stdin);
		fgets(buff_out, 1024, stdin);
		send(clientSocket, buff_out, strlen(buff_out), NULL);

		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "���Է���������Ϣ:" << buff_in << endl;
		}


	}
	*/
	id = client::screen_jump();

	while (id)
	{
		switch (id)
		{
		case 0://�˳�
			system("CLS");
			cout << "quit" << endl;
			//system("pause");
			break;
		case 1://չʾ������Ʒ
			system("CLS");
			//system("pause");
			goods_func::goods_init_interface();
			id = client::screen_jump();
			break;
		case 2://�û���¼
			system("CLS");
			//system("pause");
			i = user_func::sign_in();
			id = client::screen_jump();
			//server::reve_ACK();
			break;
		case 3://����ĳһ����ɸѡ��Ʒ
			system("CLS");
			//system("pause");
			i = goods_func::goods_name_interface();
			id = client::screen_jump();
			break;
		case 4://��ӹ��ﳵ
			system("CLS");
			//system("pause");
			i = cart_func::add_cart();
			id = client::screen_jump();
			break;
		case 5://�޸Ĺ��ﳵ
			system("CLS");
			//system("pause");
			i = cart_func::change_cart();
			id = client::screen_jump();
			break;
		case 6://���ɶ���
			system("CLS");
			//system("pause");
			i = cart_func::generate_order();
			id = client::screen_jump();
			break;
		case 7://֧������
			system("CLS");
			//system("pause");
			i = cart_func::pay_or_cancel_order();
			id = client::screen_jump();
			break;
		case 8://չʾ�û���Ϣ
			system("CLS");
			i = user_func::show_consumer();
			id = client::screen_jump();
			break;
		default:
			break;
		}
	}


	return 0;
}