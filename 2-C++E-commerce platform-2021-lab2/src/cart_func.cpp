#include "cart_func.h"
#include <iostream>

int cart_func::add_cart()
{
    user_func user_use;
    //检查消费者是否登录
    if (all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return -1;
    }
    //如果已经登录
    string cart_owner = all_consumer.get_user_name();
    //展示所有的商品
    goods_func goods_use;
    goods_use.goods_init_interface();
    show_cart(cart_owner);
    for (cart *m : v_cart)
    {
        if (m->cart_status == 1 && m->get_cart_owner() == cart_owner)
        {
            cout << "Sorry, you have a order wait for paying. Please pay for it first." << endl;
            return 2;
        }
    }
    //供消费者选择商品类别
    cout
        << "****************************************" << endl;
    cout << "Now begin to add goods to your cart." << endl;
    cout << "****************************************" << endl;

    string goods_kind;
    int goods_type;
    //输入想要购买的商品类型
    cout << "Please input the type of goods you want to buy:" << endl;
    cout << "'food','clothes','book'" << endl;
    cin.sync(); //清除缓冲区的数据流
    user_use.get_string(goods_kind);
    while ((goods_kind != "food" && goods_kind != "clothes" && goods_kind != "book") || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong kind, please input 'food' or 'clothes' or 'book', or '#' to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        user_use.get_string(goods_kind);
        if (goods_kind == "#")
        {
            cout << "quit" << endl;
            return 0;
        }
    }
    if (goods_kind == "food")
        goods_type = 0;
    else if (goods_kind == "clothes")
        goods_type = 1;
    else if (goods_kind == "book")
        goods_type = 2;
    //打印这类的所有商品
    goods_use.goods_type_interface(goods_type);
    //将这类商品的指针存入一个新的容器，便于后续的添加和查找
    vector<goods *> goods_temp;
    for (goods *tmp : v_goods)
    {
        if (tmp->get_goods_type() == goods_type)
            goods_temp.push_back(tmp);
    }
    //下面用户选择商品的名称和所有者，来定位想要购买的商品，但要求是这一类的商品
    string goods_name;
    string goods_owner;
    int goods_quantity;
    int status = 0;
    int flag = 1;
    cout << "Which goods do you want to buy? Please input the goods's name:" << endl;
    cin.sync();
    getline(cin, goods_name);
    cout << "Please input the owner of this goods:" << endl;
    cin.sync();
    user_use.get_string(goods_owner);
    while (flag)
    {
        for (goods *tmp : goods_temp)
        {
            //如果找到了
            if (tmp->get_goods_name() == goods_name && tmp->get_goods_owner() == goods_owner)
            {
                cout << "Please input the quantity you want to buy:" << endl;
                cin.sync();
                user_use.get_int(goods_quantity);
                while (goods_quantity <= 0)
                {
                    cout << "Sorry, please input a positive interger number:" << endl;
                    cin.sync();
                    user_use.get_int(goods_quantity);
                }

                cout << "Sure to add to your cart?" << endl;
                cout << "'yes' or 'no':" << endl;
                string answer;
                cin.sync();
                user_use.get_string(answer);
                while (answer != "yes" && answer != "no")
                {
                    cout << "Please input 'yes' or 'no':" << endl;
                    cin.sync();
                    user_use.get_string(answer);
                }
                if (answer == "no")
                {
                    cout << "Cancel successfully." << endl;
                    return 0;
                }
                else if (answer == "yes")
                {
                    for (cart *exist : v_cart)
                    { //检查这个用户的购物车是否已经有了这个商品
                        if (exist->get_cart_owner() == cart_owner && exist->get_cart_want() == tmp)
                        {
                            cout << "The goods has existed, now add the quantity." << endl;
                            exist->set_cart_quantity(exist->get_cart_quantity() + goods_quantity);
                            return 1;
                        }
                    }
                    cart *p_temp = new cart(status, cart_owner, tmp, goods_quantity, goods_type, goods_name, goods_owner);

                    v_cart.push_back(p_temp);

                    cout << "Add successfully!" << endl;
                    return 1;
                }
                flag = 0;
            }
        }
        if (flag == 1)
        {
            cout << "Not find, please check your input of goods's name and owner, or 'quit' to quit:" << endl;
            cout << "'check' or 'quit':" << endl;
            string temp;
            cin.sync(); //清除缓冲区的数据流
            user_use.get_string(temp);
            while (temp != "quit" && temp != "check")
            {
                cout << "'check' or 'quit':" << endl;
                cin.sync(); //清除缓冲区的数据流
                user_use.get_string(temp);
            }
            if (temp == "quit")
                return 0;
            else if (temp == "check")
            {
                cout << "Which goods do you want to buy? Please input the goods's name:" << endl;
                cin.sync();
                getline(cin, goods_name);
                cout << "Please input the owner of this goods:" << endl;
                cin.sync();
                user_use.get_string(goods_owner);
            }
        }
    }
    return 0;
}

int cart_func::change_cart()
{
    user_func user_use;
    //检查消费者是否登录
    if (all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return -1;
    }
    //消费者已经登录
    string cart_owner = all_consumer.get_user_name();

    cout << "****************************************" << endl;
    cout << "Now begin to change your cart information." << endl;
    cout << "****************************************" << endl;

    //展示消费者购物车的信息
    show_cart(cart_owner);

    int cart_quantity;
    string goods_name;
    int goods_type;
    string goods_owner;
    //首先将这个购物车的内容存入一个临时的容器便于寻找和修改
    vector<cart *> cart_temp;
    for (cart *tmp : v_cart)
    {
        if (tmp->get_cart_owner() == cart_owner)
        {
            cart_temp.push_back(tmp);
            if (tmp->cart_status == 1)
            {
                cout << "Sorry, you have a order wait for paying. Please pay for it first." << endl;
                return 2;
            }
        }
    }
    cout << "Please choose the goods you want to change?" << endl;

    cout << "Please input the type of goods(0 food,1 clothes,2 book):" << endl;
    cin.sync(); //清除缓冲区的数据流
    user_use.get_int(goods_type);
    cout << "Please input the name of goods:" << endl;
    cin.sync(); //清除缓冲区的数据流
    getline(cin, goods_name);
    cout << "Please input the owner of goods:" << endl;
    cin.sync();
    user_use.get_string(goods_owner);
    //判断这个商品是否存在于购物车
    int flag = 1; //提供循环操作
    int id;       //提供选择不同的功能
    while (flag)
    {
        for (cart *tmp : cart_temp)
        {
            if (tmp->get_cart_want()->get_goods_name() == goods_name && tmp->get_cart_want()->get_goods_type() == goods_type && tmp->get_cart_want()->get_goods_owner() == goods_owner) //全部同时满足
            {
                flag = 0; //表示找到
                while (1)
                {
                    cout << "What kind of operation do you want to do?" << endl;
                    cout << "1:Change quantity." << endl;
                    cout << "2:Delete this goods." << endl;
                    cout << "3:Delete some of this goods." << endl;
                    cout << "0:Quit." << endl;
                    cin.sync();
                    user_use.get_int(id);
                    while ((id != 0 && id != 1 && id != 2 && id != 3) || cin.fail())
                    {
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.sync();
                        }
                        cout << "Wrong id, please input 0 or 1 or 2:" << endl;
                        cin.sync(); //清除缓冲区的数据流
                        user_use.get_int(id);
                    }
                    if (id == 0)
                        return 1;
                    else if (id == 1)
                    {
                        cout << "Please input the quantity you want to buy:" << endl;
                        cin.sync();
                        user_use.get_int(cart_quantity);
                        while (cart_quantity <= 0)
                        {
                            cout << "Sorry, please input a positive interger number:" << endl;
                            cin.sync();
                            user_use.get_int(cart_quantity);
                        }
                    }
                    else if (id == 3)
                    {
                        cout << "Please input the quantity you want to delete:" << endl;
                        cin.sync();
                        user_use.get_int(cart_quantity);
                        while (cart_quantity <= 0 || cart_quantity > tmp->get_cart_quantity())
                        {
                            cout << "Sorry, please input a positive interger number that is less than the quantity current:" << endl;
                            cin.sync();
                            user_use.get_int(cart_quantity);
                        }
                    }
                    else //id=2
                    {
                        //删除cart_temp里面的
                        for (vector<cart *>::iterator it = cart_temp.begin(); it != cart_temp.end();)
                        {
                            if (*it == tmp)
                                it = cart_temp.erase(it);
                            else
                                ++it;
                        }
                        //删除v_cart里面的
                        for (vector<cart *>::iterator it = v_cart.begin(); it != v_cart.end();)
                        {
                            if (*it == tmp)
                                it = v_cart.erase(it);
                            else
                                ++it;
                        }
                        cout << "Delete successfully! Now quit." << endl;
                        return 0;
                    }
                    if (id == 1)
                    {
                        tmp->set_cart_quantity(cart_quantity);
                        cout << "Change quantity successfully!" << endl;
                    }
                    else if (id == 3)
                    {
                        tmp->set_cart_quantity(tmp->get_cart_quantity() - cart_quantity);
                        cout << "Change quantity successfully!" << endl;
                    }
                }
            }
        }
        if (flag == 1)
        {
            cout << "Sorry, the goods is not found, please check your input:" << endl;
            cout << "Please input the type of goods(0 food,1 clothes,2 book):" << endl;
            cin.sync(); //清除缓冲区的数据流
            user_use.get_int(goods_type);
            cout << "Please input the name of goods:" << endl;
            cin.sync(); //清除缓冲区的数据流
            getline(cin, goods_name);
            cout << "Please input the owner of goods:" << endl;
            cin.sync();
            user_use.get_string(goods_owner);
        }
    }
    return 0;
}

void cart_func::show_cart(string cart_owner)
{
    cout << "****************************************" << endl;
    cout << "Here is cart of " << cart_owner << endl;
    cout << "****************************************" << endl;
    string goods_type;
    int i = 1; //i为打印出来的所有商品的编号，从1开始递增。
    //cout << v_cart.size() << endl;
    for (cart *tmp : v_cart)
    {
        // cout << "_____________________________" << endl;
        // cout << tmp->get_cart_owner() << endl;
        // cout << tmp->get_cart_quantity() << endl;
        // cout << tmp->get_cart_want()->get_goods_name() << endl;
        // cout << tmp->get_cart_want()->get_goods_owner() << endl;
        // cout << tmp->get_cart_want()->get_goods_type() << endl;
        // cout << tmp->cart_status << endl;
        if (tmp->get_cart_owner() == cart_owner) //如果是这个人
        {
            if (tmp->get_cart_want() != NULL)
            {
                goods *temp = tmp->get_cart_want();
                if (temp->get_goods_type() == 0 && tmp->cart_goods_type == 0)
                {
                    goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
                    goods_type = "Food";

                    cout << i << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                    cout << "The description:         " << temp->get_goods_description() << endl;
                    cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                    cout << "The owner of goods:      " << temp->get_goods_owner() << endl;
                    cout << "The quantity:            " << tmp->get_cart_quantity() << endl;
                    if (tmp->cart_status == 0)
                        cout << "No order has been generated." << endl;
                    else if (tmp->cart_status == 1)
                        cout << "The order has been generated." << endl;
                    cout << "****************************************" << endl;
                    i++;
                }
                else if (temp->get_goods_type() == 1 && tmp->cart_goods_type == 1)
                {
                    goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
                    goods_type = "Clothes";

                    cout << i << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                    cout << "The description:         " << temp->get_goods_description() << endl;
                    cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                    cout << "The owner of goods:      " << temp->get_goods_owner() << endl;
                    cout << "The quantity:            " << tmp->get_cart_quantity() << endl;
                    if (tmp->cart_status == 0)
                        cout << "No order has been generated." << endl;
                    else if (tmp->cart_status == 1)
                        cout << "The order has been generated." << endl;
                    cout << "****************************************" << endl;
                    i++;
                }
                else if (temp->get_goods_type() == 2 && tmp->cart_goods_type == 0)
                {
                    goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);
                    goods_type = "Book";
                    cout << i << ")" << goods_type << ":" << temp->get_goods_name() << endl;
                    cout << "The description:         " << temp->get_goods_description() << endl;
                    cout << "The current price:       " << p_1->get_goods_price_change() << endl;
                    cout << "The owner of goods:      " << temp->get_goods_owner() << endl;
                    cout << "The quantity:            " << tmp->get_cart_quantity() << endl;
                    if (tmp->cart_status == 0)
                        cout << "No order has been generated." << endl;
                    else if (tmp->cart_status == 1)
                        cout << "The order has been generated." << endl;
                    cout << "****************************************" << endl;
                    i++;
                }
            }
            else
            {
                if (tmp->cart_goods_type == 0)
                {

                    goods_type = "Food";
                    cout << i << ")";
                    cout << "Sorry, the " << tmp->cart_goods_name << " of " << goods_type << " form " << tmp->cart_goods_owner << " has been withdrawn." << endl;
                    cout << "****************************************" << endl;
                    i++;
                }
                else if (tmp->cart_goods_type == 1)
                {

                    goods_type = "Clothes";
                    cout << i << ")";
                    cout << "Sorry, the " << tmp->cart_goods_name << " of " << goods_type << " form " << tmp->cart_goods_owner << " has been withdrawn." << endl;
                    cout << "****************************************" << endl;
                    i++;
                }
                else if (tmp->cart_goods_type == 0)
                {

                    goods_type = "Book";
                    cout << i << ")";
                    cout << "Sorry, the " << tmp->cart_goods_name << " of " << goods_type << " form " << tmp->cart_goods_owner << " has been withdrawn." << endl;
                    cout << "****************************************" << endl;
                    i++;
                }
            }
        }
    }
}

int cart_func::generate_order()
{
    user_func user_use;
    //检查消费者是否登录
    if (all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return -1;
    }
    int flag = 0; //用来标识是否已经生成过订单
    //消费者已经登录
    string cart_owner = all_consumer.get_user_name();
    show_cart(cart_owner); //展示购物车
    cout << "Sure to generate your order?" << endl;
    cout << "'yes' or 'no':" << endl;
    string answer;
    cin.sync();
    user_use.get_string(answer);
    while (answer != "yes" && answer != "no")
    {
        cout << "Please input 'yes' or 'no':" << endl;
        cin.sync();
        user_use.get_string(answer);
    }
    if (answer == "no")
    {
        cout << "Cancel successfully." << endl;
        return 0;
    }
    //用户选择了yes
    //检查商品是不是都还存在于平台
    if (check_cart_exist(cart_owner) == 0)
    {
        return 0;
    }
    //检查用户购物车的每一项的商品购买数量是否超过了商家目前的剩余量
    if (check_cart_over(cart_owner) == 0)
    {
        return 0;
    }

    for (cart *temp : v_cart)
    {
        if (temp->get_cart_owner() == cart_owner && temp->cart_status == 0) //找到这个商家的且未生成订单
        {
            flag = 1;
            /*if (temp->get_cart_quantity() > temp->get_cart_want()->get_goods_surplus())
            {
                cout << "The quantity you want is over the surplus of " << temp->get_cart_want()->get_goods_name() << ". We change it to the max you can buy automatically: " << temp->get_cart_want()->get_goods_surplus() << endl;
                temp->set_cart_quantity(temp->get_cart_want()->get_goods_surplus());
            }*/
            //表示这个内容已经生成了订单
            temp->cart_status = 1;
            //商品剩余量减少
            temp->get_cart_want()->set_goods_surplus(temp->get_cart_want()->get_goods_surplus() - temp->get_cart_quantity());
        }
    }
    if (flag == 1)
        return 1;
    else
    {
        cout << "All the goods has been generated." << endl;
        return 0;
    }
}

int cart_func::pay_or_cancel_order()
{
    user_func user_use;
    goods_func goods_use;
    //检查消费者是否登录
    if (all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return -1;
    }
    //消费者已经登录
    string cart_owner = all_consumer.get_user_name();
    int flag = 0;
    for (cart *temp : v_cart)
    {
        if (temp->get_cart_owner() == cart_owner) //找到
        {
            flag = 1;
            if (temp->cart_status == 0) //尚未生成订单
            {
                cout << "Sorry, you haven't generate an order." << endl;
                return 0;
            }
        }
    }
    if (flag == 0) //没有找到这个用户的购物车
    {
        cout << "Sorry, you haven't add anything to your cart." << endl;
        return 0;
    }
    //询问是否取消订单
    cout << "Do you want to cancel this order?" << endl;
    cout << "Please input 'yes' or 'no':" << endl;
    string confirm;
    cin.sync(); //清除缓冲区的数据流
    user_use.get_string(confirm);
    while (confirm != "yes" && confirm != "no")
    {
        cout << "Please input 'yes' or 'no':" << endl;
        cin.sync(); //清除缓冲区的数据流
        user_use.get_string(confirm);
    }
    if (confirm == "yes")
    {
        //取消订单，内容返回给购物车，商家商品剩余量回归
        for (cart *temp : v_cart)
        {
            if (temp->get_cart_owner() == cart_owner)
            {
                temp->cart_status = 0;
                temp->get_cart_want()->set_goods_surplus(temp->get_cart_want()->get_goods_surplus() + temp->get_cart_quantity());
            }
        }
        cout << "Cancel succeddfully!" << endl;
        return 0;
    }

    double all_money = 0.0;
    for (cart *temp : v_cart)
    {
        //获取总共的价格
        if (temp->get_cart_owner() == cart_owner)
        {
            all_money = all_money + temp->get_cart_want()->get_goods_price_change() * temp->get_cart_quantity(); //注意！！！不能保证正确，等待测试
        }
    }
    //如果超过了用户的余额
    if (all_money > all_consumer.get_user_balance())
    {
        cout << "Sorry, your balance is not enough. Please recharge." << endl;
        return 2;
    }
    //余额足够的话就支付订单
    //完成操作，商家增钱，消费者扣钱，购物车清空
    string business_owner;
    for (cart *temp : v_cart)
    {
        if (temp->get_cart_owner() == cart_owner) //找到购物车
        {
            business_owner = temp->get_cart_want()->get_goods_owner();
            for (user *tmp : v_user) //找到商家
            {
                if (tmp->get_user_name() == business_owner)
                {
                    double temp_money = temp->get_cart_want()->get_goods_price_change() * temp->get_cart_quantity();

                    tmp->set_user_balance(tmp->get_user_balance() + temp_money); //商家增钱
                }
            }
        }
    }
    //删除购物车
    for (vector<cart *>::iterator it = v_cart.begin(); it != v_cart.end();)
    {
        if ((*it)->get_cart_owner() == cart_owner)
            it = v_cart.erase(it);
        else
            ++it;
    }
    //扣钱要扣两个地方，all_consumer和v_user
    all_consumer.set_user_balance(all_consumer.get_user_balance() - all_money);
    for (user *temp : v_user)
    {
        if (temp->get_user_name() == all_consumer.get_user_name())
        {
            temp->set_user_balance(temp->get_user_balance() - all_money);
        }
    }
    cout << "Pay successfully!" << endl;
    return 1;
}

int cart_func::check_goods_exist(int goods_type, string goods_name, string goods_owner)
{
    for (goods *temp : v_goods)
    {
        if (temp->get_goods_name() == goods_name && temp->get_goods_type() == goods_type && temp->get_goods_owner() == goods_owner)
        {
            return 1;
        }
    }
    return 0;
}

int cart_func::check_cart_exist(string cart_owner)
{
    int goods_type;
    string goods_name;
    string goods_owner;
    int flag = 1;
    for (cart *temp : v_cart)
    {
        if (temp->get_cart_owner() == cart_owner)
        {
            goods_type = temp->cart_goods_type;
            goods_name = temp->cart_goods_name;
            goods_owner = temp->cart_goods_owner;
            if (check_goods_exist(goods_type, goods_name, goods_owner) == 0)
            {
                cout << "****************************************" << endl;
                cout << "Sorry, the " << goods_name << " of " << goods_owner << " has been withdrawn, please delete it from your cart." << endl;
                cout << "****************************************" << endl;
                flag = 0;
            }
        }
    }
    return flag;
}

int cart_func::check_cart_over(string cart_owner)
{
    int goods_type;
    string goods_name;
    string goods_owner;
    int flag = 1;
    for (cart *temp : v_cart)
    {
        if (temp->get_cart_owner() == cart_owner)
        {
            goods_type = temp->cart_goods_type;
            goods_name = temp->cart_goods_name;
            goods_owner = temp->cart_goods_owner;
            if (temp->get_cart_quantity() > temp->get_cart_want()->get_goods_surplus())
            {
                cout << "****************************************" << endl;
                cout << "Sorry, the quantity of " << goods_name << " from " << goods_owner << " is over surplus(" << temp->get_cart_want()->get_goods_surplus() << "), please check it in your cart." << endl;
                cout << "****************************************" << endl;
                flag = 0;
            }
        }
    }
    return flag;
}
