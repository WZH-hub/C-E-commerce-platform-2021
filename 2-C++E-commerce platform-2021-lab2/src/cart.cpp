#include "cart.h"
#include <iostream>

void cart::set_cart_owner(string owner)
{
    cart_owner = owner;
}
string cart::get_cart_owner()
{
    return cart_owner;
}

void cart::set_cart_want(goods *want)
{
    cart_want = want;
}
goods *cart::get_cart_want()
{
    return cart_want;
}

void cart::set_cart_quantity(int quantity)
{
    cart_quantity = quantity;
}
int cart::get_cart_quantity()
{
    return cart_quantity;
}

cart::cart(int status, string owner, goods *want, int quantity, int goods_type, string goods_name, string goods_owner)
{
    cart_status = status;
    cart_owner = owner;
    cart_want = want;
    cart_quantity = quantity;

    cart_goods_type = goods_type;
    cart_goods_name = goods_name;
    cart_goods_owner = goods_owner;
}
