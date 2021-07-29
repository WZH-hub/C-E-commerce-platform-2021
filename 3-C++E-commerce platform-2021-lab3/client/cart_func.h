#ifndef CART_FUNC_H
#define CART_FUNC_H

#include "user.h"
#include "goods.h"
#include "cart.h"
#include "user_func.h"
#include "goods_func.h"
#include "client.h"
#include <vector>


extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern SOCKET clientSocket;
extern SOCKET serverSocket2;
extern SOCKET clientSocket2;

extern char buff_in[1024];//��server���뵽client��
extern char buff_out[1024];//��client�����server��

using namespace std;

class cart_func
{
public:
	//�û����ﳵ�������Ʒ,δ��¼����-1��ȡ����ӷ���0����ӳɹ�����1���ж���δ֧������2
	static int add_cart();
	//�û��޸��Լ����ﳵ�ڵ���Ʒ����Ϣ,δ��¼����-1��ȡ���޸�/�޸ĳɹ�����1���ж���δ֧������2
	static int change_cart();
	//���ɶ������ɹ����ɷ���1��ȡ������/ʧ�ܷ���0,δ��¼����-1
	static int generate_order();
	//֧��������֧���ɹ�����1��ȡ��֧��/ʧ�ܷ���0,δ��¼����-1����Ҫ��ֵ����2
	static int pay_or_cancel_order();
	//�ӷ������������ݣ�����ӡ��������˹��ﳵ����Ϣ
	static void show_cart(string cart_owner);
};


#endif // !CART_FUNC_H
