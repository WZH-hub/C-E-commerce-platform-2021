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

#define MAX 100;
extern vector<goods *> v_goods;
extern vector<user *> v_user;

class in_out
{
public:
    void read_in_goods(vector<goods *> &p);       //将商品文件读入内存中
    void read_in_user(vector<user *> &p);         //将用户文件读入内存中
    void read_out_goods(const vector<goods *> p); //将商品从内存读入到文件
    void read_out_user(const vector<user *> p);   //将用户从内存读入到文件
    void delete_goods(vector<goods *> &p);        //释放商品类的内存
    void delete_user(vector<user *> &p);          //释放商品类的内存
};

#endif // !IN_OUT_H