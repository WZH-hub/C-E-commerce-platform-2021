#ifndef SCREEN_JUMP_H
#define SCREEN_JUMP_H

#include <iostream>
#include "user_func.h"
using namespace std;
#define ALL 3
extern double all_discount[ALL];
extern vector<cart *> v_cart;
/*
1、显示所有商品的界面——1234567
2、显示某个商家的所有商品的界面——1234567
3、显示某类商品的所有商品的界面——1234567
4、用户注册界面——12345
5、用户登录界面——6/7
6、显示消费者自己信息的界面——12358-10
7、显示商家自己的信息和所有商品的界面——12359-10-11
8、给登录的消费者提供充值的界面——6
9、商家修改自己商品信息的界面——7
10、登录后的用户修改密码的界面——6/7
11、商家添加商品的界面——7
12、退出系统quit
14、管理员的整体打折活动
15、消费者向购物车中添加商品
16、消费者修改购物车内的内容
17、生成订单
18、支付/取消订单
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
    int screen_15();
    int screen_16();
    int screen_17();
    int screen_18();
};

#endif // !SCREEN_H
