#ifndef CART_H
#define CART_H

#include "user.h"
#include "goods.h"
#include <vector>
#include "server.h"

extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern vector<goods *> v_goods;
extern vector<goods *> business_goods;

class cart
{
private:
    string cart_owner; //购物车的所有者
    goods *cart_want;  //商品指针
    int cart_quantity; //购买数量

public:
    //构造函数
    cart(int status, string owner, goods *want, int quantity, int goods_type, string goods_name, string goods_owner);
    int cart_status = 0; //状态，0为未生成订单，1为生成订单，当订单支付后直接删除此类

    int cart_goods_type;
    string cart_goods_name;
    string cart_goods_owner;

    void set_cart_owner(string owner);
    string get_cart_owner();

    void set_cart_want(goods *want);
    goods *get_cart_want();

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