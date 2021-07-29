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

extern char buff_in[1024];//从client输入到server的
extern char buff_out[1024];//从server输出到client的

using namespace std;
extern SOCKET serverSocket;
extern SOCKET clientSocket;
extern SOCKET clientSocket2;

class server
{
public:
	//构造函数，创建socket
	void creat();
	//构造函数，连接socket
	void _connect();
	//检查是否登录，返回1/2代表登录的是商家还是消费者，0代表未登录
	static int check_sign_in();
	//检查一个消费者是否有订单未支付，返回1代表有订单未支付，0表示没有
	static int check_order_wait(string cart_owner);
	//检查一个商品是否真的存在，存在的话返回商品的指针，否则返回NULL
	static goods* check_goods_exist(int goods_type, string goods_name, string goods_owner);
	//检查一个消费者的购物车是否已经存在某一个商品，存在的话返回购物车内这个内容的指针，否则返回NULL
	static cart* check_cart_exist(int goods_type, string goods_name, string goods_owner, string cart_owner);
	//生成订单时，检查某一个消费者购物车内的购买数量是否超过了商家目前的剩余量，一旦有超过就返回0，否则返回1
	static int check_over_quantity(string cart_owner);
	//界面跳转，接收客户端的序号，返回跳转到哪个界面
	static int screen_jump();

	static void send_ACK();
	static void reve_ACK();

};


#endif // !SERVER_H