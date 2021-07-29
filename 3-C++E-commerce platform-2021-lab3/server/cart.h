#ifndef CART_H
#define CART_H

#include "user.h"
#include "goods.h"
#include <vector>
//#include "server.h"

extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern vector<goods*> v_goods;
extern vector<goods*> business_goods;

class cart
{
private:
	string cart_owner; //���ﳵ��������
	goods* cart_want;  //��Ʒָ��
	int cart_quantity; //��������

public:
	//���캯��
	cart(int status, string owner, goods* want, int quantity, int goods_type, string goods_name, string goods_owner);
	int cart_status = 0; //״̬��0Ϊδ���ɶ�����1Ϊ���ɶ�����������֧����ֱ��ɾ������

	int cart_goods_type;
	string cart_goods_name;
	string cart_goods_owner;

	void set_cart_owner(string owner);
	string get_cart_owner();

	void set_cart_want(goods* want);
	goods* get_cart_want();

	void set_cart_quantity(int quantity);
	int get_cart_quantity();

	void set_cart_status(int status);
	int get_cart_status();

	void set_cart_goods_type(int goods_type);
	int get_cart_goods_type();

	void set_cart_goods_name(string goods_name);
	string get_cart_goods_name();

	void set_cart_goods_owner(string cart_goods_owner);
	string get_cart_goods_owner();
};

#endif // !CART_H