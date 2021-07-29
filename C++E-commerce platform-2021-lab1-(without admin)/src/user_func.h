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
    //新用户注册
    void sign_up();
    //用户登录，如果登录成功返回用户type，否则返回0选择重新登录或者退出
    int sign_in();
    //当消费者登陆后，给消费者提供充值操作，如果消费者登录且充值成功，返回1；未登录，返回2；放弃充值，返回0
    int recharge();
    //减去用户（商家和消费者）余额的函数。成功，返回1；未登录，返回2；放弃充值，返回0
    int reduce_balance(const double &money);
    //当商家登陆后,可以向自己的店铺添加商品,添加成功返回1，否则返回0
    int business_add();
    //登录后的用户可以修改密码
    int change_password();
    //显示已登录的消费者的信息
    void show_consumer();
    //显示已登陆的商家的信息和它的商品的信息
    void show_business();
    //已登录的商家修改自己的商品信息（打折，修改介绍，价格，删除商品，成功的话返回1
    int change_goods();

    //检查用户名是否注册过,如果注册过就返回用户类别1|2，否则返回false
    int check_name(const string &name);
    //检查用户输入的密码是否跟输入的用户名匹配
    int check_password(const string &name, const string &password);
    //获取用户的余额
    double get_balance(const string &name);
};

#endif // !USER_FUNC_H