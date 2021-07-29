#include<iostream>
using namespace std;
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<windows.h>
#include<string>


int main() {
	//1.确定协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2) {
		cout << "确定版本协议失败: " << GetLastError() << endl;
		return -1;
	}
	cout << "确定版本协议成功！" << endl;

	//2.创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		cout << "创建server-socket失败: " << GetLastError() << endl;
		return -1;
	}
	cout << "创建server-socket成功！" << endl;


	//3.设置服务器地址簇
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888);

	//4.绑定
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		cout << "绑定8888失败: " << GetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "绑定8888成功！" << endl;

	//5.监听
	r = listen(serverSocket, 10);
	if (r == -1) {
		cout << "监听8888失败: " << GetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "监听8888成功！" << endl;

	//6. 接受连接
	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
	if (clientSocket == SOCKET_ERROR) {
		cout << "客户端8888连接失败:" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	cout << "客户端8888连接成功" << endl;


	//2.创建socket
	SOCKET clientSocket2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket2 == SOCKET_ERROR) {
		cout << "创建client-socket失败: " << GetLastError() << endl;
		return -1;
	}
	cout << "创建client-socket成功！" << endl;

	//3.设置服务器地址簇
	SOCKADDR_IN addr2 = { 0 };
	addr2.sin_family = AF_INET;
	addr2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(6168);

	//4. 连接
	int m = connect(clientSocket2, (sockaddr*)&addr2, sizeof(addr2));
	if (m == -1) {
		cout << "服务器6168连接失败" << GetLastError() << endl;
		closesocket(clientSocket2);
		WSACleanup();
		return -1;
	}
	cout << "服务器6168连接成功！" << endl;


	// 7. 通信
	char buff_in[1024];
	char buff_out[1024];
	while (1) {
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "来自客户端的消息:" << buff_in << endl;
		}

		cout << "输入你发送的消息:";
		cin >> buff_out;
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}

}