#ifndef CART_FUNC_H
#define CART_FUNC_H

#include "user.h"
#include "goods.h"
#include "in_out.h"
#include "cart.h"
#include "user_func.h"
#include "goods_func.h"
#include "server.h"
#include <vector>


extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern vector<goods*> v_goods;
extern vector<goods*> business_goods;
extern vector<cart*> v_cart;

extern char buff_in[1024];//��client���뵽server��
extern char buff_out[1024];//��server�����client��

using namespace std;
extern SOCKET serverSocket;
extern SOCKET clientSocket;
extern SOCKET clientSocket2;

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
	//չʾĳ�������߹��ﳵ�ڵ�������Ʒ
	static void show_cart(string cart_owner);
};


#endif // !CART_FUNC_H
