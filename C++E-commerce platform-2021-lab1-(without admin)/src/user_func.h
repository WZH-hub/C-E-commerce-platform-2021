#ifndef USER_FUNC_H
#define USER_FUNC_H

#include "user.h"
#include "goods.h"
#include "in_out.h"
#include "goods_func.h"
#include <vector>

extern user_Business all_business;
extern user_Consumer all_consumer;
extern vector<goods *> v_goods;
extern vector<goods *> business_goods;

class user_func
{
public:
    //���û�ע��
    void sign_up();
    //�û���¼�������¼�ɹ������û�type�����򷵻�0ѡ�����µ�¼�����˳�
    int sign_in();
    //�������ߵ�½�󣬸��������ṩ��ֵ��������������ߵ�¼�ҳ�ֵ�ɹ�������1��δ��¼������2��������ֵ������0
    int recharge();
    //��ȥ�û����̼Һ������ߣ����ĺ������ɹ�������1��δ��¼������2��������ֵ������0
    int reduce_balance(const double &money);
    //���̼ҵ�½��,�������Լ��ĵ��������Ʒ,��ӳɹ�����1�����򷵻�0
    int business_add();
    //��¼����û������޸�����
    int change_password();
    //��ʾ�ѵ�¼�������ߵ���Ϣ
    void show_consumer();
    //��ʾ�ѵ�½���̼ҵ���Ϣ��������Ʒ����Ϣ
    void show_business();
    //�ѵ�¼���̼��޸��Լ�����Ʒ��Ϣ�����ۣ��޸Ľ��ܣ��۸�ɾ����Ʒ���ɹ��Ļ�����1
    int change_goods();

    //����û����Ƿ�ע���,���ע����ͷ����û����1|2�����򷵻�false
    int check_name(const string &name);
    //����û�����������Ƿ��������û���ƥ��
    int check_password(const string &name, const string &password);
    //��ȡ�û������
    double get_balance(const string &name);
};

#endif // !USER_FUNC_H