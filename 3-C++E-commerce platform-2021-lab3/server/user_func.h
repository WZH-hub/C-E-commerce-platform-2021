#ifndef USER_FUNC_H
#define USER_FUNC_H

#include "user.h"
#include "goods.h"
#include "in_out.h"
#include "goods_func.h"
#include "server.h"
#include "cart_func.h"
#include <vector>
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

class user_func
{
public:
	//���������0����ʾ�˺Ż����������
	static int sign_in();
	static int show_consumer();
};




#endif // !USER_FUNC_H