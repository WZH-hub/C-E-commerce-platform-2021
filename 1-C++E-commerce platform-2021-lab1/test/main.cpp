#include <vector>
#include <iostream>
#include "user.h"
#include "goods.h"
#include "goods_func.h"
#include "user_func.h"
#include "in_out.h"
#include "screen_jump.h"

vector<goods *> v_goods;
vector<user *> v_user;
vector<goods *> business_goods; //用来存放登录商家现在的所有商品
/*
1、显示所有商品的界面
2、显示某个商家的所有商品的界面
3、显示某类商品的所有商品的界面
4、用户注册界面
5、用户登录界面
6、显示消费者自己信息的界面
7、显示商家自己的信息和所有商品的界面
8、给登录的消费者提供充值的界面
9、商家修改自己商品信息的界面
10、登录后的用户修改密码的界面
11、商家添加商品的界面
12、退出系统quit
*/

//全局变量，当用户登陆后对其进行重新赋值
user_Business all_business(0, "#", "#", 0.0);
user_Consumer all_consumer(0, "#", "#", 0.0);
//管理员，信息写死
user_Business admin(3, "admin", "commerce", 0.0);

//一共存在的商品种类
#define ALL 3
double all_discount[ALL] = {1.0}; //存打折信息

using namespace std;

int main()
{
    //打开文件
    in_out file;
    //从文件中将信息读入内存
    file.read_in_user(v_user);
    file.read_in_goods(v_goods);
    //读入管理员
    user_Business *_admin = new user_Business(3, "admin", "commerce", 0.0);
    v_user.push_back(_admin);
    //v_user.push_back(&admin);
    //用来进行命令跳转
    int id = 1;
    string owner;
    //用来检测返回值
    int i;
    //表示登录的是商家还是消费者
    int type = 0;
    //定义三个类用来调用函数
    user_func user;
    goods_func goods;
    screen_jump screen;

    while (id)
    {
        switch (id)
        {
        case 0:
            cout << "quit" << endl;
            system("pause");
            break;
        case 1:
            system("CLS"); //清屏
            goods.goods_init_interface();
            id = screen.screen_01();
            system("pause");
            break;
        case 2:
            system("CLS"); //清屏

            cout << "Please input the name of business:" << endl;
            cin.sync(); //清除缓冲区的数据流
            cin >> owner;
            goods.goods_merchant_interface(owner);
            id = screen.screen_02();
            system("pause");
            break;
        case 3:
            system("CLS"); //清屏
            goods.goods_screen_interface();
            id = screen.screen_03();
            system("pause");
            break;
        case 4:
            system("CLS"); //清屏
            user.sign_up();
            id = screen.screen_04();
            system("pause");
            break;
        case 5:
            system("CLS"); //清屏
            //登录
            type = user.sign_in();
            id = screen.screen_05(type);
            system("pause");
            break;
        case 6:
            system("CLS"); //清屏
            user.show_consumer();
            id = screen.screen_06();
            system("pause");
            break;
        case 7:
            system("CLS"); //清屏
            user.show_business();
            id = screen.screen_07();
            system("pause");
            break;
        case 8:
            system("CLS"); //清屏
            i = user.recharge();
            id = screen.screen_08(i);
            system("pause");
            break;
        case 9:
            system("CLS"); //清屏
            i = user.change_goods();
            id = screen.screen_09();
            system("pause");
            break;
        case 10:
            system("CLS"); //清屏
            i = user.change_password();
            id = screen.screen_10(type);
            system("pause");
            break;
        case 11:
            system("CLS"); //清屏
            i = user.business_add();
            id = screen.screen_11();
            system("pause");
            break;
        case 14:
            system("CLS"); //清屏
            i = user.goods_discount();
            id = screen.screen_14();
            system("pause");
            break;
        default:
            id = 0;
            system("pause");
            break;
        }
    }

    //退出
    file.read_out_user(v_user);
    file.read_out_goods(v_goods);
    //释放内存
    file.delete_user(v_user);
    file.delete_goods(v_goods);
    file.delete_goods(business_goods);
    return 0;
}