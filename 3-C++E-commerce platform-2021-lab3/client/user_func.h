#ifndef USER_FUNC_H
#define USER_FUNC_H

#include "user.h"
#include "goods.h"
#include "goods_func.h"
#include "client.h"
#include "cart_func.h"
#include <vector>

extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern SOCKET clientSocket;
extern SOCKET serverSocket2;
extern SOCKET clientSocket2;

extern char buff_in[1024];//��server���뵽client��
extern char buff_out[1024];//��client�����server��
using namespace std;

class user_func
{
public:
	//���������˺���������¼�������ݴӷ�����������Ϣ�޸�ȫ�ֱ���all_consumer������Ϊ0��ʾ��¼ʧ��
	static int sign_in();
	//int���͵�������
	static void get_int(int& n);
	//double���͵�������
	static void get_double(double& n);
	//string���͵������⣬�ܾ��ո�
	static void get_string(string& n);
	//չʾ�����ߵ���Ϣ
	static int show_consumer();
};





#endif // !USER_FUNC_H
