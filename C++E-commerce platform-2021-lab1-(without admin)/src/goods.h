#ifndef GOODS_H
#define GOODS_H

using namespace std;
#include <string>

class goods //商品-父类
{
private:
    int goods_type;           //商品的类别，目前为三种：食物0，服装1，图书2
    string goods_name;        //商品的名称
    string goods_description; //商品的描述
    double goods_initprice;   //商品原先的价格，即录入商品时的价格
    double goods_price;       //商品现在的价格
    int goods_surplus;        //商品的剩余量

    string goods_owner; //商品所属商家
public:
    void set_goods_name(string name); //初始化或修改商品的名称
    string get_goods_name() const;    //获取商品的名称

    void set_goods_description(string description); //初始化或修改商品的描述
    string get_goods_description() const;           //获取商品的描述

    void set_goods_initprice(double initprice); //初始化商品的价格，同时初始化商品的现价，之后不允许修改初始价格
    double get_goods_initprice() const;         //获取商品的初始价格

    void set_goods_price(double price);          //修改商品的现价，包括打折等因素
    double get_goods_price() const;              //获取商品的价格，不包括打折，单纯修改后的
    virtual double get_goods_price_change() = 0; //获取商品的现价，包括打折等因素

    void set_goods_surplus(int surplus); //初始化或修改商品的剩余量
    int get_goods_surplus() const;       //获取商品的剩余量

    void set_goods_type(int type); //初始化商品的类别
    int get_goods_type() const;    //获取商品的类别

    void set_goods_owner(string temp); //初始化商品的所属商家,商家登录后才可以输入，所以不用从键盘输入，直接将商家的账号名复制进去
    string get_goods_owner() const;    //获取商品的所属商家
    virtual ~goods() = default;
};

class goods_Food : public goods //食物类
{
public:
    static double discount; //折扣
    goods_Food(
        int goods_type,
        string goods_name,
        string goods_description,
        double goods_initprice,
        double goods_price,
        int goods_surplus,

        string goods_owner);
    // goods_Food::goods_Food(int goods_type);
    double get_goods_price_change() override; //获取打折后的价格
};

class goods_Clothes : public goods //服装类
{
public:
    static double discount; //折扣
    goods_Clothes(
        int goods_type,
        string goods_name,
        string goods_description,
        double goods_initprice,
        double goods_price,
        int goods_surplus,
        string goods_owner);
    double get_goods_price_change() override; //获取打折后的价格
};

class goods_Book : public goods //书籍类
{
public:
    static double discount; //折扣
    goods_Book(
        int goods_type,
        string goods_name,
        string goods_description,
        double goods_initprice,
        double goods_price,
        int goods_surplus,
        string goods_owner);
    double get_goods_price_change() override; //获取打折后的价格
};

#endif