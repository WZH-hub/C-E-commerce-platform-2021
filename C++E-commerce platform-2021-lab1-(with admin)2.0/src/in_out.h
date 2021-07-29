#ifndef IN_OUT_H
#define IN_OUT_H

using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>

#include "goods.h"
#include "user.h"

#define ALL 3
extern double all_discount[ALL];
extern vector<goods *> v_goods;
extern vector<user *> v_user;

class in_out
{
public:
    void read_in_goods(vector<goods *> &p);       //����Ʒ�ļ������ڴ���
    void read_in_user(vector<user *> &p);         //���û��ļ������ڴ���
    void read_out_goods(const vector<goods *> p); //����Ʒ���ڴ���뵽�ļ�
    void read_out_user(const vector<user *> p);   //���û����ڴ���뵽�ļ�
    void delete_goods(vector<goods *> &p);        //�ͷ���Ʒ����ڴ�
    void delete_user(vector<user *> &p);          //�ͷ���Ʒ����ڴ�
};

#endif // !IN_OUT_H