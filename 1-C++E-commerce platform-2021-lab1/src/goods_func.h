#ifndef GOODS_FUNC_H
#define GOODS_FUNC_H

#include "in_out.h"
#include "goods.h"

extern user_Business all_business;
extern user_Consumer all_consumer;

using namespace std;

class goods_func //�漰��Ʒ�ĺ���
{
public:
    //��ʼ����չʾ������Ʒ�����ƣ��������ּۣ��ۿۣ�ʣ�����������̼�
    void goods_init_interface();
    //������Ʒ���ɸѡ��������Ʒ�е�һ�ಢ��ӡ����
    void goods_screen_interface();
    //������Ʒ�������ߣ��������������ߵ�������Ʒ����ӡ����
    void goods_merchant_interface(const string &owner);
    
};

#endif // !GOODS_FUNC_H
