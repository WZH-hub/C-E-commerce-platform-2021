#ifndef SCREEN_JUMP_H
#define SCREEN_JUMP_H

#include <iostream>
#include "user_func.h"
using namespace std;
#define ALL 3
extern double all_discount[ALL];
/*
1����ʾ������Ʒ�Ľ��桪��1234567
2����ʾĳ���̼ҵ�������Ʒ�Ľ��桪��1234567
3����ʾĳ����Ʒ��������Ʒ�Ľ��桪��1234567
4���û�ע����桪��12345
5���û���¼���桪��6/7
6����ʾ�������Լ���Ϣ�Ľ��桪��12358-10
7����ʾ�̼��Լ�����Ϣ��������Ʒ�Ľ��桪��12359-10-11
8������¼���������ṩ��ֵ�Ľ��桪��6
9���̼��޸��Լ���Ʒ��Ϣ�Ľ��桪��7
10����¼����û��޸�����Ľ��桪��6/7
11���̼������Ʒ�Ľ��桪��7
12���˳�ϵͳquit
*/

class screen_jump
{
public:
    int screen_01();
    int screen_02();
    int screen_03();
    int screen_04();
    int screen_05(int change);
    int screen_06();
    int screen_07();
    int screen_08(int change);
    int screen_09();
    int screen_10(int change);
    int screen_11();
    int screen_14();
    int screen_00();
};

#endif // !SCREEN_H
