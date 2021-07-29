#include "goods_func.h"
#include <iostream>

void goods_func::goods_init_interface()
{
    cout << "****************************************" << endl;
    cout << "Here is all the goods." << endl;
    cout << "****************************************" << endl;
    string goods_type;
    int i = 1; //i为打印出来的所有商品的编号，从1开始递增。
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == 0)
        {
            goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
            goods_type = "Food";

            cout << i << ")" << goods_type << ":" << temp->get_goods_name() << endl;
            cout << "The description:         " << temp->get_goods_description() << endl;
            cout << "The original price:      " << temp->get_goods_price() << endl;
            cout << "The business discount:   " << p_1->discount << endl;
            cout << "The platform discount:   " << all_discount[0] << endl;
            cout << "The current price:       " << p_1->get_goods_price_change() << endl;
            cout << "The surplus:             " << temp->get_goods_surplus() << endl;
            cout << "The owner:               " << temp->get_goods_owner() << endl;
            cout << "****************************************" << endl;
            i++;
        }
    }
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == 1)
        {
            goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
            goods_type = "Clothes";

            cout << i << ")" << goods_type << ":" << temp->get_goods_name() << endl;
            cout << "The description:         " << temp->get_goods_description() << endl;
            cout << "The original price:      " << temp->get_goods_price() << endl;
            cout << "The business discount:   " << p_1->discount << endl;
            cout << "The platform discount:   " << all_discount[1] << endl;
            cout << "The current price:       " << p_1->get_goods_price_change() << endl;
            cout << "The surplus:             " << temp->get_goods_surplus() << endl;
            cout << "The owner:               " << temp->get_goods_owner() << endl;
            cout << "****************************************" << endl;
            i++;
        }
    }
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == 2)
        {
            goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);
            goods_type = "Book";
            cout << i << ")" << goods_type << ":" << temp->get_goods_name() << endl;
            cout << "The description:         " << temp->get_goods_description() << endl;
            cout << "The original price:      " << temp->get_goods_price() << endl;
            cout << "The business discount:   " << p_1->discount << endl;
            cout << "The platform discount:   " << all_discount[2] << endl;
            cout << "The current price:       " << p_1->get_goods_price_change() << endl;
            cout << "The surplus:             " << temp->get_goods_surplus() << endl;
            cout << "The owner:               " << temp->get_goods_owner() << endl;
            cout << "****************************************" << endl;
            i++;
        }
    }
}

void goods_func::goods_screen_interface()
{
    int i;
    cout << "****************************************" << endl;
    cout << "Please input the type of goods you want." << endl;
    cout << "0 for Food,1 for Clothes,2 for Book" << endl;
    cout << "****************************************" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> i;
    while ((i != 0 && i != 1 && i != 2) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
        }
        cout << "Wrong input, please input 0 or 1 or 2,or -1 to quit:" << endl;
        cin >> i;
    }
    string goods_type;
    if (i == 0)
    {
        // goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
        goods_type = "Food";
    }
    else if (i == 1)
    {
        // goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
        goods_type = "Clothes";
    }
    else if (i == 2)
    {
        // goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);
        goods_type = "Book";
    }
    cout << "****************************************" << endl;
    cout << "Here is all the " << goods_type << "." << endl;
    cout << "****************************************" << endl;

    int j = 1; //j为打印出来的所有商品的编号，从1开始递增。
    // for (auto temp = v_goods.begin(); temp != v_goods.end(); temp++)
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == i)
        {

            if (i == 0)
            {
                goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
                cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                cout << "The description:         " << temp->get_goods_description() << endl;
                cout << "The original price:      " << temp->get_goods_price() << endl;
                cout << "The business discount:   " << p_1->discount << endl;
                cout << "The platform discount:   " << all_discount[0] << endl;
                cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                cout << "The surplus:             " << temp->get_goods_surplus() << endl;
                cout << "The owner:               " << temp->get_goods_owner() << endl;
                cout << "****************************************" << endl;
            }
            else if (i == 1)
            {
                goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
                cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                cout << "The description:         " << temp->get_goods_description() << endl;
                cout << "The original price:      " << temp->get_goods_price() << endl;
                cout << "The business discount:   " << p_1->discount << endl;
                cout << "The platform discount:   " << all_discount[1] << endl;
                cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                cout << "The surplus:             " << temp->get_goods_surplus() << endl;
                cout << "The owner:               " << temp->get_goods_owner() << endl;
                cout << "****************************************" << endl;
            }
            else if (i == 2)
            {
                goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);

                cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                cout << "The description:         " << temp->get_goods_description() << endl;
                cout << "The original price:      " << temp->get_goods_price() << endl;
                cout << "The business discount:   " << p_1->discount << endl;
                cout << "The platform discount:   " << all_discount[2] << endl;
                cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                cout << "The surplus:             " << temp->get_goods_surplus() << endl;
                cout << "The owner:               " << temp->get_goods_owner() << endl;
                cout << "****************************************" << endl;
            }
            j++;
        }
    }
}

void goods_func::goods_merchant_interface(const string &owner)
{
    //检查这个owner是否真的存在
    int flag = 1;
    for (goods *tmp : v_goods)
    {
        if (tmp->get_goods_owner() == owner)
            flag = 0;
    }
    if (flag == 1)
    {
        cout << "****************************************" << endl;
        cout << "This business is not exist, please check your input." << endl;
        cout << "****************************************" << endl;
        return;
    }
    cout << "****************************************" << endl;
    cout << "Here is all the goods of " << owner << "." << endl;
    cout << "****************************************" << endl;

    int j = 1; //j为打印出来的所有商品的编号，从1开始递增。
    string goods_type;
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == 0 && temp->get_goods_owner() == owner)
        {
            goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
            goods_type = "Food";

            cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
            cout << "The description:         " << temp->get_goods_description() << endl;
            cout << "The original price:      " << temp->get_goods_price() << endl;
            cout << "The business discount:   " << p_1->discount << endl;
            cout << "The platform discount:   " << all_discount[0] << endl;
            cout << "The current price:       " << p_1->get_goods_price_change() << endl;
            cout << "The surplus:             " << temp->get_goods_surplus() << endl;
            cout << "The owner:               " << temp->get_goods_owner() << endl;
            cout << "****************************************" << endl;
            j++;
        }
    }
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == 1 && temp->get_goods_owner() == owner)
        {
            goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
            goods_type = "Clothes";

            cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
            cout << "The description:         " << temp->get_goods_description() << endl;
            cout << "The original price:      " << temp->get_goods_price() << endl;
            cout << "The business discount:   " << p_1->discount << endl;
            cout << "The platform discount:   " << all_discount[1] << endl;
            cout << "The current price:       " << p_1->get_goods_price_change() << endl;
            cout << "The surplus:             " << temp->get_goods_surplus() << endl;
            cout << "The owner:               " << temp->get_goods_owner() << endl;
            cout << "****************************************" << endl;
            j++;
        }
    }
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == 2 && temp->get_goods_owner() == owner)
        {
            goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);
            goods_type = "Book";
            cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
            cout << "The description:         " << temp->get_goods_description() << endl;
            cout << "The original price:      " << temp->get_goods_price() << endl;
            cout << "The business discount:   " << p_1->discount << endl;
            cout << "The platform discount:   " << all_discount[2] << endl;
            cout << "The current price:       " << p_1->get_goods_price_change() << endl;
            cout << "The surplus:             " << temp->get_goods_surplus() << endl;
            cout << "The owner:               " << temp->get_goods_owner() << endl;
            cout << "****************************************" << endl;
            j++;
        }
    }
}

void goods_func::goods_type_interface(int i)
{
    string goods_type;
    if (i == 0)
    {
        // goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
        goods_type = "Food";
    }
    else if (i == 1)
    {
        // goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
        goods_type = "Clothes";
    }
    else if (i == 2)
    {
        // goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);
        goods_type = "Book";
    }
    cout << "****************************************" << endl;
    cout << "Here is all the " << goods_type << "." << endl;
    cout << "****************************************" << endl;

    int j = 1; //j为打印出来的所有商品的编号，从1开始递增。
    // for (auto temp = v_goods.begin(); temp != v_goods.end(); temp++)
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_type() == i)
        {

            if (i == 0)
            {
                goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
                cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                cout << "The description:         " << temp->get_goods_description() << endl;
                cout << "The original price:      " << temp->get_goods_price() << endl;
                cout << "The business discount:   " << p_1->discount << endl;
                cout << "The platform discount:   " << all_discount[0] << endl;
                cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                cout << "The surplus:             " << temp->get_goods_surplus() << endl;
                cout << "The owner:               " << temp->get_goods_owner() << endl;
                cout << "****************************************" << endl;
            }
            else if (i == 1)
            {
                goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
                cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                cout << "The description:         " << temp->get_goods_description() << endl;
                cout << "The original price:      " << temp->get_goods_price() << endl;
                cout << "The business discount:   " << p_1->discount << endl;
                cout << "The platform discount:   " << all_discount[1] << endl;
                cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                cout << "The surplus:             " << temp->get_goods_surplus() << endl;
                cout << "The owner:               " << temp->get_goods_owner() << endl;
                cout << "****************************************" << endl;
            }
            else if (i == 2)
            {
                goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);

                cout << j << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                cout << "The description:         " << temp->get_goods_description() << endl;
                cout << "The original price:      " << temp->get_goods_price() << endl;
                cout << "The business discount:   " << p_1->discount << endl;
                cout << "The platform discount:   " << all_discount[2] << endl;
                cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                cout << "The surplus:             " << temp->get_goods_surplus() << endl;
                cout << "The owner:               " << temp->get_goods_owner() << endl;
                cout << "****************************************" << endl;
            }
            j++;
        }
    }
}
