#ifndef CART_FUNC_H
#define CART_FUNC_H

#include "user.h"
#include "goods.h"
#include "in_out.h"
#include "cart.h"
#include "user_func.h"
#include "goods_func.h"
#include "server.h"
#include <vector>

extern user_Business all_business;
extern user_Consumer all_consumer;

extern vector<goods *> v_goods;
extern vector<goods *> business_goods;
extern vector<cart *> v_cart;

class cart_func
{
public:
    //用户向购物车内添加商品,未登录返回-1，取消添加返回0，添加成功返回1，有订单未支付返回2
    int add_cart();
    //用户修改自己购物车内的商品的信息,未登录返回-1，取消修改/修改成功返回1，有订单未支付返回2
    int change_cart();
    //生成订单，成功生成返回1，取消生成/失败返回0,未登录返回-1
    int generate_order();
    //支付订单，支付成功返回1，取消支付/失败返回0,未登录返回-1，需要充值返回2
    int pay_or_cancel_order();
    //展示某个消费者购物车内的所有商品
    void show_cart(string cart_owner);
};

#endif // !CART_FUNC_H