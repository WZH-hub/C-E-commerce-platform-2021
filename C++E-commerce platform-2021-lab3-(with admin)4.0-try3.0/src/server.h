#ifndef SERVER_H
#define SERVER_H

#include "user.h"
#include "goods.h"
#include "cart.h"
#include "in_out.h"
#include "user_func.h"
#include "goods_func.h"
#include "cart_func.h"
#include "screen_jump.h"
#include <vector>

extern user_Business all_business;
extern user_Consumer all_consumer;
extern user_Business admin;

extern vector<goods *> v_goods;
extern vector<goods *> business_goods;
extern vector<cart *> v_cart;

class server
{
public:
    //检查是否登录，返回1/2代表登录的是商家还是消费者，0代表未登录
    static int check_sign_in();
    //检查一个消费者是否有订单未支付，返回1代表有订单未支付，0表示没有
    static int check_order_wait(string cart_owner);
    //检查一个商品是否真的存在，存在的话返回商品的剩余量，否则返回-1
    static int check_goods_exist(int goods_type, string goods_name, string goods_owner);
    //检查一个消费者的购物车是否已经存在某一个商品，存在的话返回购物车内商品的数量，否则返回-1
    static int check_cart_exist(int goods_type, string goods_name, string goods_owner, string cart_owner);
    //生成订单时，检查某一个消费者购物车内的购买数量是否超过了商家目前的剩余量，一旦有超过就返回0，否则返回1
    static int check_over_quantity(string cart_owner);
}

#endif // !SERVER_H
