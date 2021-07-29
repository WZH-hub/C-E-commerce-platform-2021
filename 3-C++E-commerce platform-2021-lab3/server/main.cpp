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
vector<goods*> business_goods; //用来存放登录商家现在的所有商品
vector<cart*> v_cart;          //所有的人的购物车信息

//全局变量，当用户登陆后对其进行重新赋值
user_Business all_business(0, "#", "#", 0.0);
user_Consumer all_consumer(0, "#", "#", 0.0);
//user_Consumer all_consumer(2, "ljr", "asd", 1000.0);
//管理员，信息写死
user_Business admin(3, "admin", "commerce", 0.0);

//一共存在的商品种类
#define ALL 3
double all_discount[ALL] = { 1.0 }; //存打折信息

SOCKET serverSocket;
SOCKET clientSocket;
SOCKET clientSocket2;

char buff_in[1024];//从client输入到server的
char buff_out[1024];//从server输出到client的

int main()
{
	server SERVER;
	//打开文件
	in_out file;
	//从文件中将信息读入内存
	file.read_in_user(v_user);
	file.read_in_goods(v_goods);
	file.read_in_cart(v_cart);
	//读入管理员
	user_Business* _admin = new user_Business(3, "admin", "commerce", 0.0);
	v_user.push_back(_admin);
	//用来进行命令跳转
	int id = 1;
	string owner;
	//用来检测返回值
	int i;
	SERVER.creat();
	SERVER._connect();
	int r;
	//首先要接收一次初始命令，也就是登陆后的初始界面，应该是一个数字
	//r = recv(clientSocket, buff_in, 1023, NULL);
	//if (r > 0) {
	//	buff_in[r] = 0;
	//	cout << "来自客户端的消息:" << buff_in << endl;
	//}
	//目前了解的，貌似需要先转为string，再stringstream
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
		case 0://退出
			cout << "quit" << endl;
			file.read_out_user(v_user);
			file.read_out_goods(v_goods);
			file.read_out_cart(v_cart);
			SERVER._connect();
			id = server::screen_jump();
			break;
		case 1://展示所有商品
			//system("pause");
			goods_func::goods_init_interface();
			id = server::screen_jump();
			break;
		case 2://用户登录
			//system("pause");
			i = user_func::sign_in();
			id = server::screen_jump();
			//server::reve_ACK();
			break;
		case 3://根据某一名称筛选商品
			//system("pause");
			i = goods_func::goods_name_interface();
			id = server::screen_jump();
			break;
		case 4://添加购物车
			//system("pause");
			i = cart_func::add_cart();
			id = server::screen_jump();
			break;
		case 5://修改购物车
			//system("pause");
			i = cart_func::change_cart();
			id = server::screen_jump();
			break;
		case 6://生成订单
			//system("pause");
			i = cart_func::generate_order();
			id = server::screen_jump();
			break;
		case 7://支付订单
			//system("pause");
			i = cart_func::pay_or_cancel_order();
			id = server::screen_jump();
			break;
		case 8://展示用户信息
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
			cout << "来自客户端的消息:" << buff_in << endl;
		}

		cout << "输入你发送的消息:";
		//cin >> buff_out;
		fflush(stdin);
		fgets(buff_out, 1024, stdin);
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}*/

	//退出
	file.read_out_user(v_user);
	file.read_out_goods(v_goods);
	file.read_out_cart(v_cart);
	//释放内存
	file.delete_user(v_user);
	file.delete_goods(v_goods);
	file.delete_cart(v_cart);
	file.delete_goods(business_goods);
	return 0;
}