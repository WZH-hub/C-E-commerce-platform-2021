#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <sstream>
#include <vector>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<windows.h>
#include<string>
using namespace std;

extern SOCKET clientSocket;
extern SOCKET serverSocket2;
extern SOCKET clientSocket2;

extern char buff_in[1024];//从server输入到client的
extern char buff_out[1024];//从client输出到server的
class client
{
public:
	//创建socket
	void creat();
	//给客户端发送要跳转的界面的序号
	static int screen_jump();

	static void send_ACK();
	static void reve_ACK();
};
#endif // !CLIENT_H