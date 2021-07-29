#ifndef GOODS_FUNC_H
#define GOODS_FUNC_H

#include "in_out.h"
#include "goods.h"
#include "server.h"

extern user_Business all_business;
extern user_Consumer all_consumer;
extern SOCKET serverSocket;
extern SOCKET clientSocket;
extern SOCKET clientSocket2;
extern char buff_in[1024];//��client���뵽server��
extern char buff_out[1024];//��server�����client��

using namespace std;

class goods_func //�漰��Ʒ�ĺ���
{
public:
	//��ʼ����չʾ������Ʒ�����ƣ��������ּۣ��ۿۣ�ʣ�����������̼�
	static void goods_init_interface();
	//������Ʒ���ɸѡ��������Ʒ�е�һ�ಢ��ӡ����
	static void goods_screen_interface();
	//������Ʒ�������ߣ��������������ߵ�������Ʒ����ӡ����
	static void goods_merchant_interface(const string& owner);
	//���ݴ���ı��ɸѡ������Ʒ�е�һ�ಢ��ӡ�����������ڵڶ��������������ڹ��ﳵ�����Ʒ
	static void goods_type_interface(int i);
	//�����������Ʒ����ɸѡ��Ʒ����ӡ�����û���ҵ��ͷ���0���ҵ��˷���1
	static int goods_name_interface();
};

#endif // !GOODS_FUNC_H
