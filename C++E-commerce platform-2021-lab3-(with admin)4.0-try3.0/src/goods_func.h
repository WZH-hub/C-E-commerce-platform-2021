#ifndef GOODS_FUNC_H
#define GOODS_FUNC_H

#include "in_out.h"
#include "goods.h"
#include "server.h"

extern user_Business all_business;
extern user_Consumer all_consumer;

using namespace std;

class goods_func //涉及商品的函数
{
public:
    //初始界面展示所有商品的名称，描述，现价，折扣，剩余量和所属商家
    void goods_init_interface();
    //根据商品类别，筛选出三类商品中的一类并打印出来
    void goods_screen_interface();
    //根据商品的所有者，区别出这个所有者的所有商品并打印出来
    void goods_merchant_interface(const string &owner);
    //根据传入的编号筛选三类商品中的一类并打印出来，类似于第二个函数，服务于购物车添加商品
    void goods_type_interface(int i);
    //根据输入的商品名称筛选商品并打印，如果没有找到就返回0，找到了返回1
    int goods_name_interface(string goods_name);
};

#endif // !GOODS_FUNC_H
