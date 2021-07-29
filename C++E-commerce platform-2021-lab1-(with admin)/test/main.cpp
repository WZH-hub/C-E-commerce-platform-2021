#include <vector>
#include <iostream>
#include "user.h"
#include "goods.h"
#include "goods_func.h"
#include "user_func.h"
#include "in_out.h"
#include "screen_jump.h"

vector<goods *> v_goods;
vector<user *> v_user;
vector<goods *> business_goods; //������ŵ�¼�̼����ڵ�������Ʒ
/*
1����ʾ������Ʒ�Ľ���
2����ʾĳ���̼ҵ�������Ʒ�Ľ���
3����ʾĳ����Ʒ��������Ʒ�Ľ���
4���û�ע�����
5���û���¼����
6����ʾ�������Լ���Ϣ�Ľ���
7����ʾ�̼��Լ�����Ϣ��������Ʒ�Ľ���
8������¼���������ṩ��ֵ�Ľ���
9���̼��޸��Լ���Ʒ��Ϣ�Ľ���
10����¼����û��޸�����Ľ���
11���̼������Ʒ�Ľ���
12���˳�ϵͳquit
*/

//ȫ�ֱ��������û���½�����������¸�ֵ
user_Business all_business(0, "#", "#", 0.0);
user_Consumer all_consumer(0, "#", "#", 0.0);
//����Ա����Ϣд��
user_Business admin(3, "admin", "commerce", 0.0);

//һ�����ڵ���Ʒ����
#define ALL 3
double all_discount[ALL] = {1.0}; //�������Ϣ

using namespace std;

int main()
{
    //���ļ�
    in_out file;
    //���ļ��н���Ϣ�����ڴ�
    file.read_in_user(v_user);
    file.read_in_goods(v_goods);
    //�������Ա
    v_user.push_back(&admin);
    //��������������ת
    int id = 1;
    string owner;
    //������ⷵ��ֵ
    int i;
    //��ʾ��¼�����̼һ���������
    int type = 0;
    //�����������������ú���
    user_func user;
    goods_func goods;
    screen_jump screen;

    while (id)
    {
        switch (id)
        {
        case 0:
            cout << "quit" << endl;
            system("pause");
            break;
        case 1:
            system("CLS"); //����
            goods.goods_init_interface();
            id = screen.screen_01();
            system("pause");
            break;
        case 2:
            system("CLS"); //����

            cout << "Please input the name of business:" << endl;
            cin.sync(); //�����������������
            cin >> owner;
            goods.goods_merchant_interface(owner);
            id = screen.screen_02();
            system("pause");
            break;
        case 3:
            system("CLS"); //����
            goods.goods_screen_interface();
            id = screen.screen_03();
            system("pause");
            break;
        case 4:
            system("CLS"); //����
            user.sign_up();
            id = screen.screen_04();
            system("pause");
            break;
        case 5:
            system("CLS"); //����
            //��¼
            type = user.sign_in();
            id = screen.screen_05(type);
            system("pause");
            break;
        case 6:
            system("CLS"); //����
            user.show_consumer();
            id = screen.screen_06();
            system("pause");
            break;
        case 7:
            system("CLS"); //����
            user.show_business();
            id = screen.screen_07();
            system("pause");
            break;
        case 8:
            system("CLS"); //����
            i = user.recharge();
            id = screen.screen_08(i);
            system("pause");
            break;
        case 9:
            system("CLS"); //����
            i = user.change_goods();
            id = screen.screen_09();
            system("pause");
            break;
        case 10:
            system("CLS"); //����
            i = user.change_password();
            id = screen.screen_10(type);
            system("pause");
            break;
        case 11:
            system("CLS"); //����
            i = user.business_add();
            id = screen.screen_11();
            system("pause");
            break;
        case 14:
            system("CLS"); //����
            i = goods.goods_discount();
            id = screen.screen_14();
            system("pause");
            break;
        default:
            id = 0;
            system("pause");
            break;
        }
    }

    //�˳�
    file.read_out_user(v_user);
    file.read_out_goods(v_goods);
    //�ͷ��ڴ�
    file.delete_user(v_user);
    file.delete_goods(v_goods);
    file.delete_goods(business_goods);
    return 0;
}