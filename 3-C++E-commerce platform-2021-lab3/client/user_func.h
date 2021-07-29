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

extern char buff_in[1024];//从server输入到client的
extern char buff_out[1024];//从client输出到server的
using namespace std;

class user_func
{
public:
	//用来输入账号密码来登录，并依据从服务器来的信息修改全局变量all_consumer，返回为0表示登录失败
	static int sign_in();
	//int类型的输入检测
	static void get_int(int& n);
	//double类型的输入检测
	static void get_double(double& n);
	//string类型的输入检测，拒绝空格
	static void get_string(string& n);
	//展示消费者的信息
	static int show_consumer();
};





#endif // !USER_FUNC_H
