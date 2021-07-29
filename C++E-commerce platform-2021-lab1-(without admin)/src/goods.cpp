#include "goods.h"
#include <iostream>

double goods_Food::discount = 1.0;
double goods_Clothes::discount = 1.0;
double goods_Book::discount = 1.0;

/***********goods��***********/
void goods::set_goods_name(string name = "goods_name")
{
    // cout << "Please input the name of goods(replace ' ' with '_'): ";
    // // cin >> goods_name;
    // getline(cin, goods_name);
    goods_name = name;
}
string goods::get_goods_name() const
{
    return goods_name;
}

void goods::set_goods_description(string description = "goods_description")
{
    // cout << "Please input the description of goods(replace ' ' with '_'): ";
    // //cin >> goods_description;
    // getline(cin, goods_description);
    goods_description = description;
}
string goods::get_goods_description() const
{
    return goods_description;
}

void goods::set_goods_initprice(double initprice = 0.0)
{
    // cout << "Please input the initial price of goods: ";
    // cin >> goods_initprice;
    goods_initprice = initprice;
}
double goods::get_goods_initprice() const
{
    return goods_initprice;
}

void goods::set_goods_price(double price = 0.0)
{
    // cout << "Please input the present price of goods: ";
    // cin >> goods_price;
    goods_price = price;
}
double goods::get_goods_price() const
{
    return goods_price;
}

void goods::set_goods_surplus(int surplus = 0)
{
    // cout << "Please input the surplus of goods: ";
    // cin >> goods_surplus;
    goods_surplus = surplus;
}
int goods::get_goods_surplus() const
{
    return goods_surplus;
}

void goods::set_goods_type(int type = -1)
{
    // cout << "Please input the type of goods(0 for food,1 for clothes,2 for book ): ";
    // cin >> goods_type;
    goods_type = type;
}
int goods::get_goods_type() const
{
    return goods_type;
}

void goods::set_goods_owner(string temp = "goods_owner") //ע�⣺��Ϊ���̼ҵ�½��ſ������룬���Բ��ôӼ�������
{
    // cout << "Please input the owner of goods: ";
    // getline(cin, goods_owner);
    goods_owner = temp;
}
string goods::get_goods_owner() const
{
    return goods_owner;
}

/***********food��***********/
goods_Food::goods_Food(
    int type,
    string name,
    string description,
    double initprice,
    double price,
    int surplus,
    string owner)
{
    set_goods_type(type);
    set_goods_name(name);
    set_goods_description(description);
    set_goods_initprice(initprice);
    set_goods_price(price);
    set_goods_surplus(surplus);
    set_goods_owner(owner);
}
double goods_Food::get_goods_price_change() 
{
    double temp = get_goods_price();
    return temp * discount;
}

/***********clothes��***********/
goods_Clothes::goods_Clothes(
    int type,
    string name,
    string description,
    double initprice,
    double price,
    int surplus,
    string owner)
{
    set_goods_type(type);
    set_goods_name(name);
    set_goods_description(description);
    set_goods_initprice(initprice);
    set_goods_price(price);
    set_goods_surplus(surplus);
    set_goods_owner(owner);
}
double goods_Clothes::get_goods_price_change() 
{
    double temp = get_goods_price();
    return temp * discount;
}

/***********Book��***********/
goods_Book::goods_Book(
    int type,
    string name,
    string description,
    double initprice,
    double price,
    int surplus,
    string owner)
{
    set_goods_type(type);
    set_goods_name(name);
    set_goods_description(description);
    set_goods_initprice(initprice);
    set_goods_price(price);
    set_goods_surplus(surplus);
    set_goods_owner(owner);
}
double goods_Book::get_goods_price_change() 
{
    double temp = get_goods_price();
    return temp * discount;
}