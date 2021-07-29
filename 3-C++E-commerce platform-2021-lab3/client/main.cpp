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
vector<goods*> business_goods; //用来存放登录商家现在的所有商品
vector<cart*> v_cart;          //所有的人的购物车信息*/

//全局变量，当用户登陆后对其进行重新赋值
user_Business all_business(0, "#", "#", 0.0);
user_Consumer all_consumer(0, "#", "#", 0.0);
//user_Consumer all_consumer(2, "ljr", "asd", 1000.0);
//管理员，信息写死
user_Business admin(3, "admin", "commerce", 0.0);

//一共存在的商品种类
#define ALL 3
double all_discount[ALL] = { 1.0 }; //存打折信息

SOCKET clientSocket;
SOCKET serverSocket2;
SOCKET clientSocket2;

char buff_in[1024];//从server输入到client的
char buff_out[1024];//从client输出到server的




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
		cout << "输入你发送的消息:";
		//cin >> buff_out;
		fflush(stdin);
		fgets(buff_out, 1024, stdin);
		send(clientSocket, buff_out, strlen(buff_out), NULL);

		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
		}


	}
	*/
	id = client::screen_jump();

	while (id)
	{
		switch (id)
		{
		case 0://退出
			system("CLS");
			cout << "quit" << endl;
			//system("pause");
			break;
		case 1://展示所有商品
			system("CLS");
			//system("pause");
			goods_func::goods_init_interface();
			id = client::screen_jump();
			break;
		case 2://用户登录
			system("CLS");
			//system("pause");
			i = user_func::sign_in();
			id = client::screen_jump();
			//server::reve_ACK();
			break;
		case 3://根据某一名称筛选商品
			system("CLS");
			//system("pause");
			i = goods_func::goods_name_interface();
			id = client::screen_jump();
			break;
		case 4://添加购物车
			system("CLS");
			//system("pause");
			i = cart_func::add_cart();
			id = client::screen_jump();
			break;
		case 5://修改购物车
			system("CLS");
			//system("pause");
			i = cart_func::change_cart();
			id = client::screen_jump();
			break;
		case 6://生成订单
			system("CLS");
			//system("pause");
			i = cart_func::generate_order();
			id = client::screen_jump();
			break;
		case 7://支付订单
			system("CLS");
			//system("pause");
			i = cart_func::pay_or_cancel_order();
			id = client::screen_jump();
			break;
		case 8://展示用户信息
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