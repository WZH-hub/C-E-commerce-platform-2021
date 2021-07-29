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

extern char buff_in[1024];//从server输入到client的
extern char buff_out[1024];//从client输出到server的
using namespace std;


class goods_func
{
public:
	//接收服务器传来的数据并打印所有商品
	static void goods_init_interface();
	//接收服务器的数据并打印一个名称的商品
	static int goods_name_interface();
};





#endif // !GOODS_FUNC_H
