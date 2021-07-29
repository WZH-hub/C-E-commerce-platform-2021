#include<iostream>
using namespace std;
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<windows.h>
#include<string>


int main() {
	//1.ȷ��Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2) {
		cout << "ȷ���汾Э��ʧ��: " << GetLastError() << endl;
		return -1;
	}
	cout << "ȷ���汾Э��ɹ���" << endl;

	//2.����socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		cout << "����server-socketʧ��: " << GetLastError() << endl;
		return -1;
	}
	cout << "����server-socket�ɹ���" << endl;


	//3.���÷�������ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888);

	//4.��
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		cout << "��8888ʧ��: " << GetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "��8888�ɹ���" << endl;

	//5.����
	r = listen(serverSocket, 10);
	if (r == -1) {
		cout << "����8888ʧ��: " << GetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "����8888�ɹ���" << endl;

	//6. ��������
	SOCKADDR_IN clientAddr = { 0 };
	int len = sizeof(clientAddr);
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
	if (clientSocket == SOCKET_ERROR) {
		cout << "�ͻ���8888����ʧ��:" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	cout << "�ͻ���8888���ӳɹ�" << endl;


	//2.����socket
	SOCKET clientSocket2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket2 == SOCKET_ERROR) {
		cout << "����client-socketʧ��: " << GetLastError() << endl;
		return -1;
	}
	cout << "����client-socket�ɹ���" << endl;

	//3.���÷�������ַ��
	SOCKADDR_IN addr2 = { 0 };
	addr2.sin_family = AF_INET;
	addr2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr2.sin_port = htons(6168);

	//4. ����
	int m = connect(clientSocket2, (sockaddr*)&addr2, sizeof(addr2));
	if (m == -1) {
		cout << "������6168����ʧ��" << GetLastError() << endl;
		closesocket(clientSocket2);
		WSACleanup();
		return -1;
	}
	cout << "������6168���ӳɹ���" << endl;


	// 7. ͨ��
	char buff_in[1024];
	char buff_out[1024];
	while (1) {
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
		}

		cout << "�����㷢�͵���Ϣ:";
		cin >> buff_out;
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}

}