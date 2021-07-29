#include <iostream>
#include "cart.h"
#include "goods.h"
#include "in_out.h"
#include "server.h"
#include "user.h"
#include "goods_func.h"
#include "cart_func.h"
#include "user_func.h"

using namespace std;

vector<goods*> v_goods;
vector<user*> v_user;
vector<goods*> business_goods; //������ŵ�¼�̼����ڵ�������Ʒ
vector<cart*> v_cart;          //���е��˵Ĺ��ﳵ��Ϣ

//ȫ�ֱ��������û���½�����������¸�ֵ
user_Business all_business(0, "#", "#", 0.0);
user_Consumer all_consumer(0, "#", "#", 0.0);
//user_Consumer all_consumer(2, "ljr", "asd", 1000.0);
//����Ա����Ϣд��
user_Business admin(3, "admin", "commerce", 0.0);

//һ�����ڵ���Ʒ����
#define ALL 3
double all_discount[ALL] = { 1.0 }; //�������Ϣ

SOCKET serverSocket;
SOCKET clientSocket;
SOCKET clientSocket2;

char buff_in[1024];//��client���뵽server��
char buff_out[1024];//��server�����client��

int main()
{
	server SERVER;
	//���ļ�
	in_out file;
	//���ļ��н���Ϣ�����ڴ�
	file.read_in_user(v_user);
	file.read_in_goods(v_goods);
	file.read_in_cart(v_cart);
	//�������Ա
	user_Business* _admin = new user_Business(3, "admin", "commerce", 0.0);
	v_user.push_back(_admin);
	//��������������ת
	int id = 1;
	string owner;
	//������ⷵ��ֵ
	int i;
	SERVER.creat();
	SERVER._connect();
	int r;
	//����Ҫ����һ�γ�ʼ���Ҳ���ǵ�½��ĳ�ʼ���棬Ӧ����һ������
	//r = recv(clientSocket, buff_in, 1023, NULL);
	//if (r > 0) {
	//	buff_in[r] = 0;
	//	cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
	//}
	//Ŀǰ�˽�ģ�ò����Ҫ��תΪstring����stringstream
	//string ss;
	//stringstream sstream;
	//ss = buff_in;
	//sstream << ss;
	//sstream >> id;
	//cout << "id:" << id << endl;
	//cout << id << endl;
	id = server::screen_jump();

	while (1)
	{
		switch (id)
		{
		case 0://�˳�
			cout << "quit" << endl;
			file.read_out_user(v_user);
			file.read_out_goods(v_goods);
			file.read_out_cart(v_cart);
			SERVER._connect();
			id = server::screen_jump();
			break;
		case 1://չʾ������Ʒ
			//system("pause");
			goods_func::goods_init_interface();
			id = server::screen_jump();
			break;
		case 2://�û���¼
			//system("pause");
			i = user_func::sign_in();
			id = server::screen_jump();
			//server::reve_ACK();
			break;
		case 3://����ĳһ����ɸѡ��Ʒ
			//system("pause");
			i = goods_func::goods_name_interface();
			id = server::screen_jump();
			break;
		case 4://��ӹ��ﳵ
			//system("pause");
			i = cart_func::add_cart();
			id = server::screen_jump();
			break;
		case 5://�޸Ĺ��ﳵ
			//system("pause");
			i = cart_func::change_cart();
			id = server::screen_jump();
			break;
		case 6://���ɶ���
			//system("pause");
			i = cart_func::generate_order();
			id = server::screen_jump();
			break;
		case 7://֧������
			//system("pause");
			i = cart_func::pay_or_cancel_order();
			id = server::screen_jump();
			break;
		case 8://չʾ�û���Ϣ
			i = user_func::show_consumer();
			id = server::screen_jump();
			break;

		default:
			break;
		}
	}
	/*
	while (1) {
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
		}

		cout << "�����㷢�͵���Ϣ:";
		//cin >> buff_out;
		fflush(stdin);
		fgets(buff_out, 1024, stdin);
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}*/

	//�˳�
	file.read_out_user(v_user);
	file.read_out_goods(v_goods);
	file.read_out_cart(v_cart);
	//�ͷ��ڴ�
	file.delete_user(v_user);
	file.delete_goods(v_goods);
	file.delete_cart(v_cart);
	file.delete_goods(business_goods);
	return 0;
}