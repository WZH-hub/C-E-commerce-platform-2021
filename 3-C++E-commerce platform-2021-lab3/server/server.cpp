#include "server.h"

void server::creat()
{
	//1.确定协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2) {
		cout << "确定版本协议失败: " << GetLastError() << endl;
		return;
	}
	cout << "确定版本协议成功！" << endl;

	//2.创建socket
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		cout << "创建server-socket失败: " << GetLastError() << endl;
		return;
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
		return;
	}
	cout << "绑定8888成功！" << endl;

	//5.监听
	r = listen(serverSocket, 10);
	if (r == -1) {
		cout << "监听8888失败: " << GetLastError() << endl;
		WSACleanup();
		return;
	}
	cout << "监听8888成功！" << endl;

	/*
	//6. 接受连接
	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
	if (clientSocket == SOCKET_ERROR) {
		cout << "客户端8888连接失败:" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	cout << "客户端8888连接成功" << endl;


	//2.创建socket
	clientSocket2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket2 == SOCKET_ERROR) {
		cout << "创建client-socket失败: " << GetLastError() << endl;
		return;
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
		return;
	}
	cout << "服务器6168连接成功！" << endl;
	*/

	// 7. 通信
	//char buff_in[1024];
	//char buff_out[1024];
	/*while (1) {
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
		}
	*/
}

void server::_connect()
{
	//6. 接受连接
	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
	if (clientSocket == SOCKET_ERROR) {
		cout << "客户端8888连接失败:" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	cout << "客户端8888连接成功" << endl;


	//2.创建socket
	clientSocket2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket2 == SOCKET_ERROR) {
		cout << "创建client-socket失败: " << GetLastError() << endl;
		return;
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
		return;
	}
	cout << "服务器6168连接成功！" << endl;
}

int server::check_sign_in()
{
	if (all_business.get_user_type() == 1)
		return 1;
	else if (all_consumer.get_user_type() == 2)
		return 2;
	else
		return 0;
}

int server::check_order_wait(string cart_owner)
{
	for (cart* m : v_cart)
	{
		if (m->cart_status == 1 && m->get_cart_owner() == cart_owner)
		{
			return 1;
		}
	}
	return 0;
}

goods* server::check_goods_exist(int goods_type, string goods_name, string goods_owner)
{
	for (goods* tmp : v_goods)
	{
		if (tmp->get_goods_type() == goods_type && tmp->get_goods_name() == goods_name && tmp->get_goods_owner() == goods_owner)
			return tmp;
	}
	return NULL;
}

cart* server::check_cart_exist(int goods_type, string goods_name, string goods_owner, string cart_owner)
{
	for (cart* tmp : v_cart)
	{
		if (tmp->get_cart_goods_name() == goods_name && tmp->get_cart_goods_owner() == goods_owner && tmp->get_cart_goods_type() == goods_type && tmp->get_cart_owner() == cart_owner)
		{
			return tmp;
		}
	}
	return NULL;
}

int server::check_over_quantity(string cart_owner)
{
	int flag = 1;
	for (cart* tmp : v_cart)
	{
		if (tmp->get_cart_owner() == cart_owner && tmp->get_cart_status() == 0)
		{
			int all = server::check_goods_exist(tmp->get_cart_goods_type(), tmp->get_cart_goods_name(), tmp->get_cart_goods_owner())->get_goods_surplus();
			if (tmp->get_cart_quantity() > all)
				return 0;
		}
	}
	return 1;
}

int server::screen_jump()
{
	int id = 0;
	stringstream sstream;
	string ss;
	int r;
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "来自客户端的消息:" << buff_in << endl;
		ss = buff_in;
		sstream.str("");
		sstream.clear();
		sstream << ss;
		sstream >> id;
	}
	return id;
}


void server::send_ACK()
{
	stringstream sstream;
	sstream << '#';
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
}

void server::reve_ACK()
{
	stringstream sstream;
	int r;
	r = recv(clientSocket, buff_in, 1023, NULL);
}