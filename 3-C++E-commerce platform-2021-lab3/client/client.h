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

extern char buff_in[1024];//��server���뵽client��
extern char buff_out[1024];//��client�����server��
class client
{
public:
	//����socket
	void creat();
	//���ͻ��˷���Ҫ��ת�Ľ�������
	static int screen_jump();

	static void send_ACK();
	static void reve_ACK();
};
#endif // !CLIENT_H