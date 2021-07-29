#include "server.h"

int server::check_sign_in()
{
    if (all_business.get_user_type() == 1)
        return 1;
    else if (all_consumer.get_user_type() == 2)
        return 2;
    else
        return 0;
}

int server::check_order_wait(string cart_owner)
{
    for (cart *m : v_cart)
    {
        if (m->cart_status == 1 && m->get_cart_owner() == cart_owner)
        {
            return 1;
        }
    }
    return 0;
}

int server::check_goods_exist(int goods_type, string goods_name, string goods_owner)
{
    for (goods *tmp : v_goods)
    {
        if (tmp->get_goods_type() == goods_type && tmp->get_goods_name() == goods_name && tmp->get_goods_owner() == goods_owner)
            return tmp->get_goods_surplus();
    }
    return -1;
}

int server::check_cart_exist(int goods_type, string goods_name, string goods_owner, string cart_owner)
{
    for (cart *tmp : v_cart)
    {
        if (tmp->get_cart_goods_name() == goods_name && tmp->get_cart_goods_owner() == goods_owner && tmp->get_cart_goods_type() == goods_type && tmp->get_cart_owner() == cart_owner)
        {
            return tmp->get_cart_quantity();
        }
    }
    return -1;
}

int server::check_over_quantity(string cart_owner)
{
    int flag = 1;
    for (cart *tmp : v_cart)
    {
        if (tmp->get_cart_owner() == cart_owner && tmp->get_cart_status() == 0)
        {
            int all = server::check_goods_exist(tmp->get_cart_goods_type(), tmp->get_cart_goods_name(), tmp->get_cart_goods_owner());
            if (tmp->get_cart_quantity() > all)
                return 0;
        }
    }
    return 1;
}