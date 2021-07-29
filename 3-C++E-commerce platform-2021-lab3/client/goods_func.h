#ifndef GOODS_FUNC_H
#define GOODS_FUNC_H

#include "user.h"
#include "goods.h"
#include "client.h"
#include "cart.h"
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


class goods_func
{
public:
	//���շ��������������ݲ���ӡ������Ʒ
	static void goods_init_interface();
	//���շ����������ݲ���ӡһ�����Ƶ���Ʒ
	static int goods_name_interface();
};





#endif // !GOODS_FUNC_H
