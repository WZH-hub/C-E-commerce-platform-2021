#include "screen_jump.h"

using namespace std;

int screen_jump::screen_01()
{
    int change = 0;
    cout << "****************************************" << endl;
    cout << "What do you want to do?" << endl;
    cout << "0) quit." << endl;
    cout << "1) show all goods." << endl;
    cout << "2) show the goods of somebody." << endl;
    cout << "3) show the goods of the same kind." << endl;
    cout << "4) sign up." << endl;
    cout << "5) sign in." << endl;
    cout << "6) show the information of consumer." << endl;
    cout << "7) show the information of business(with goods)." << endl;
    cout << "****************************************" << endl;
    cout << "Please input the order in the front:" << endl;
    cin >> change;
    while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5 && change != 6 && change != 7) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Please input the order again:" << endl;
        cin.sync();
        cin >> change;
    }
    return change; //因为序号直接对应id，不需要改变
}

int screen_jump::screen_02()
{
    int change = 0;
    cout << "****************************************" << endl;
    cout << "What do you want to do?" << endl;
    cout << "0) quit." << endl;
    cout << "1) show all goods." << endl;
    cout << "2) show the goods of somebody." << endl;
    cout << "3) show the goods of the same kind." << endl;
    cout << "4) sign up." << endl;
    cout << "5) sign in." << endl;
    cout << "6) show the information of consumer." << endl;
    cout << "7) show the information of business(with goods)." << endl;
    cout << "****************************************" << endl;
    cout << "Please input the order in the front:" << endl;
    cin >> change;
    while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5 && change != 6 && change != 7) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Please input the order again:" << endl;
        cin.sync();
        cin >> change;
    }
    return change; //因为序号直接对应id，不需要改变
}

int screen_jump::screen_03()
{
    int change = 0;
    cout << "****************************************" << endl;
    cout << "What do you want to do?" << endl;
    cout << "0) quit." << endl;
    cout << "1) show all goods." << endl;
    cout << "2) show the goods of somebody." << endl;
    cout << "3) show the goods of the same kind." << endl;
    cout << "4) sign up." << endl;
    cout << "5) sign in." << endl;
    cout << "6) show the information of consumer." << endl;
    cout << "7) show the information of business(with goods)." << endl;
    cout << "****************************************" << endl;
    cout << "Please input the order in the front:" << endl;
    cin >> change;
    while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5 && change != 6 && change != 7) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Please input the order again:" << endl;
        cin.sync();
        cin >> change;
    }
    return change; //因为序号直接对应id，不需要改变
}

int screen_jump::screen_04()
{
    int change = 0;
    cout << "****************************************" << endl;
    cout << "What do you want to do?" << endl;
    cout << "0) quit." << endl;
    cout << "1) show all goods." << endl;
    cout << "2) show the goods of somebody." << endl;
    cout << "3) show the goods of the same kind." << endl;
    cout << "4) sign up." << endl;
    cout << "5) sign in." << endl;
    cout << "****************************************" << endl;
    cout << "Please input the order in the front:" << endl;
    cin >> change;
    while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Please input the order again:" << endl;
        cin.sync();
        cin >> change;
    }
    return change; //因为序号直接对应id，不需要改变
}

int screen_jump::screen_05(int change)
{
    if (change == 1) //商家
        return 7;
    else if (change == 2) //消费者
        return 6;
    else //登录失败
        return 1;
}

int screen_jump::screen_06()
{
    int change = 0;
    cout << "****************************************" << endl;
    cout << "What do you want to do?" << endl;
    cout << "0) quit." << endl;
    cout << "1) show all goods." << endl;
    cout << "2) show the goods of somebody." << endl;
    cout << "3) show the goods of the same kind." << endl;
    cout << "4) sign up." << endl;
    cout << "5) sign in." << endl;
    cout << "6) recharge." << endl;
    cout << "7) change password." << endl;
    cout << "****************************************" << endl;
    cout << "Please input the order in the front:" << endl;
    cin >> change;
    while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5 && change != 6 && change != 7) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Please input the order again:" << endl;
        cin.sync();
        cin >> change;
    }
    switch (change)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return change;
    case 6:
        return 8;
    case 7:
        return 10;
    }
    return 1;
}

int screen_jump::screen_07()
{
    int change = 0;
    cout << "****************************************" << endl;
    cout << "What do you want to do?" << endl;
    cout << "0) quit." << endl;
    cout << "1) show all goods." << endl;
    cout << "2) show the goods of somebody." << endl;
    cout << "3) show the goods of the same kind." << endl;
    cout << "5) sign up." << endl;
    cout << "5) sign in." << endl;
    cout << "6) change goods information." << endl;
    cout << "7) change password." << endl;
    cout << "8) add goods." << endl;
    cout << "****************************************" << endl;
    cout << "Please input the order in the front:" << endl;
    cin >> change;
    while ((change != 0 && change != 1 && change != 2 && change != 3 && change != 4 && change != 5 && change != 6 && change != 7 && change != 8) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Please input the order again:" << endl;
        cin.sync();
        cin >> change;
    }
    switch (change)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return change;
    case 6:
        return 9;
    case 7:
        return 10;
    case 8:
        return 11;
    }
    return 1;
}

int screen_jump::screen_08(int change)
{
    //根据反馈的情况进行跳转
    //消费者登录且充值成功，返回1；未登录，返回2；放弃充值，返回0
    if (change == 1 || change == 0)
        return 6;
    else //未登录的话跳转到登录界面
        return 5;
}

int screen_jump::screen_09()
{
    return 7;
}

int screen_jump::screen_10(int change)
{
    if (change == 1) //商家
        return 7;
    else if (change == 2) //消费者
        return 6;
    else //还没有登录
        return 5;
}

int screen_jump::screen_11()
{
    return 7;
}