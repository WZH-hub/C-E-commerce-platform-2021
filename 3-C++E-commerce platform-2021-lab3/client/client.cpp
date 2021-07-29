#include "client.h"
#include "user_func.h"
void client::creat()
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
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == SOCKET_ERROR) {
		cout << "创建client-socket失败: " << GetLastError() << endl;
		return;
	}
	cout << "创建client-socket成功！" << endl;


	//3.设置服务器地址簇
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888);

	//4. 连接
	int r = connect(clientSocket, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		cout << "服务器8888连接失败" << GetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return;
	}
	cout << "服务器8888连接成功！" << endl;

	//创建server-socket
	serverSocket2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket2 == SOCKET_ERROR) {
		cout << "创建server-socket失败: " << GetLastError() << endl;
		return;
	}
	cout << "创建server-socket成功！" << endl;

	//设置服务器地址簇
	SOCKADDR_IN addr2 = { 0 };
	addr2.sin_family = AF_INET;
	addr2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(6168);

	//绑定
	int m = bind(serverSocket2, (sockaddr*)&addr2, sizeof(addr2));
	if (m == -1) {
		cout << "绑定6168失败: " << GetLastError() << endl;
		WSACleanup();
		return;
	}
	cout << "绑定6168成功！" << endl;

	//监听
	m = listen(serverSocket2, 10);
	if (m == -1) {
		cout << "监听6168失败: " << GetLastError() << endl;
		WSACleanup();
		return;
	}
	cout << "监听6168成功！" << endl;

	//接受连接
	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	clientSocket2 = accept(serverSocket2, (sockaddr*)&clientAddr, &len);
	if (clientSocket2 == SOCKET_ERROR) {
		cout << "客户端6168连接失败:" << GetLastError() << endl;
		closesocket(serverSocket2);
		WSACleanup();
		return;
	}
	cout << "客户端6168连接成功" << endl;

	// 5. 通信
	//char buff_out[1024];
	//char buff_in[1024];
	/*while (1) {
		cout << "输入你发送的消息:";
		//cin >> buff_out;
		fflush(stdin);
		fgets(buff_out, 1024, stdin);
		send(clientSocket, buff_out, strlen(buff_out), NULL);

		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			cout << "来自客户端的消息:" << buff_in << endl;
		}


	}*/
}

int client::screen_jump()
{
	int change = 0;
	stringstream sstream;
	string ss;
	cout << "****************************************" << endl;
	cout << "What do you want to do?" << endl;
	cout << "0) quit." << endl;
	cout << "1) show all goods." << endl;
	cout << "2) sign in." << endl;
	cout << "3) show the goods of the same name." << endl;
	cout << "4) add the goods to your cart." << endl;
	cout << "5) change your cart." << endl;
	cout << "6) generate your order." << endl;
	cout << "7) pay or cancel your order." << endl;
	cout << "8) show your information and cart." << endl;
	cout << "****************************************" << endl;
	cout << "Please input the order in the front:" << endl;
	cin.sync(); //清除缓冲区的数据流
	user_func::get_int(change);
	while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5 && change != 6 && change != 7 && change != 8) || cin.fail())
	{
		if (cin.fail())
		{
			cin.clear();
			cin.sync();
		}
		cout << "Please input the order again:" << endl;
		cin.sync();
		user_func::get_int(change);
	}

	sstream.str("");
	sstream.clear();
	sstream << change;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket, buff_out, strlen(buff_out), NULL);



	return change; //因为序号直接对应id，不需要改变}
}
void client::send_ACK()
{
	stringstream sstream;
	sstream << '#';
	strcpy(buff_out, (sstream.str()).c_str());
	//cout << buff_out << endl;
	send(clientSocket, buff_out, strlen(buff_out), NULL);
}

void client::reve_ACK()
{
	stringstream sstream;
	int m;
	m = recv(clientSocket2, buff_in, 1023, NULL);
}