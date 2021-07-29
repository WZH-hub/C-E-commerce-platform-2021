#ifndef SERVER_H
#define SERVER_H


#include <iostream>
#include <sstream>
#include <vector>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<windows.h>
#include<string>


#include "cart.h"
#include "goods.h"
#include "user.h"

extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern vector<goods*> v_goods;
extern vector<goods*> business_goods;
extern vector<cart*> v_cart;

extern char buff_in[1024];//��client���뵽server��
extern char buff_out[1024];//��server�����client��

using namespace std;
extern SOCKET serverSocket;
extern SOCKET clientSocket;
extern SOCKET clientSocket2;

class server
{
public:
	//���캯��������socket
	void creat();
	//���캯��������socket
	void _connect();
	//����Ƿ��¼������1/2�����¼�����̼һ��������ߣ�0����δ��¼
	static int check_sign_in();
	//���һ���������Ƿ��ж���δ֧��������1�����ж���δ֧����0��ʾû��
	static int check_order_wait(string cart_owner);
	//���һ����Ʒ�Ƿ���Ĵ��ڣ����ڵĻ�������Ʒ��ָ�룬���򷵻�NULL
	static goods* check_goods_exist(int goods_type, string goods_name, string goods_owner);
	//���һ�������ߵĹ��ﳵ�Ƿ��Ѿ�����ĳһ����Ʒ�����ڵĻ����ع��ﳵ��������ݵ�ָ�룬���򷵻�NULL
	static cart* check_cart_exist(int goods_type, string goods_name, string goods_owner, string cart_owner);
	//���ɶ���ʱ�����ĳһ�������߹��ﳵ�ڵĹ��������Ƿ񳬹����̼�Ŀǰ��ʣ������һ���г����ͷ���0�����򷵻�1
	static int check_over_quantity(string cart_owner);
	//������ת�����տͻ��˵���ţ�������ת���ĸ�����
	static int screen_jump();

	static void send_ACK();
	static void reve_ACK();

};


#endif // !SERVER_H