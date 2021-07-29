#include "user_func.h"

void user_func::sign_up()
{

    int user_type = 0;
    string user_name;
    string user_password;
    double user_balance;

    cout << "****************************************" << endl;
    cout << "Now begin to sign up." << endl;
    cout << "****************************************" << endl;
    cout << "Please input your type(business or consumer):" << endl;
    string ch_type; //用户输入的类别
    cin.sync();     //清除缓冲区的数据流
    cin >> ch_type;
    while (1) //对输入进行检验
    {
        if (ch_type == "business")
        {
            user_type = 1;
            break;
        }
        else if (ch_type == "consumer")
        {
            user_type = 2;
            break;
        }
        else
        {
            cout << "Error! Please input 'business' or 'consumer':" << endl;
            cin.sync();
            cin >> ch_type;
        }
    }
    cout << "Please input your name(no spaces):" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> user_name;
    while (check_name(user_name) || user_name == "admin")
    {
        cout << "Sorry, this name has been signed up, please input another name:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> user_name;
    }
    cout << "Please input your password(no spaces):" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> user_password;
    // cout << "Please input your balance:" << endl;
    // cin.sync(); //清除缓冲区的数据流
    // cin >> user_balance;
    user_balance = 0.0;
    if (user_type == 1)
    {
        user_Business *p_temp = new user_Business(user_type, user_name, user_password, user_balance);
        v_user.push_back(p_temp);
        cout << "Sign up successfully!" << endl;
    }
    else if (user_type == 2)
    {
        user_Consumer *p_temp = new user_Consumer(user_type, user_name, user_password, user_balance);
        v_user.push_back(p_temp);
        cout << "Sign up successfully!" << endl;
    }
}

int user_func::sign_in()
{
    // int user_type = 0;
    string user_name;
    string user_password;
    double user_balance;

    cout << "****************************************" << endl;
    cout << "Now begin to sign in." << endl;
    cout << "****************************************" << endl;
    cout << "Please input your name:" << endl;
    cin.sync();
    cin >> user_name;
    string temp;
    while (!check_name(user_name))
    {
        cout << "Sorry,you haven't sign up, please quit to sign up or check your input." << endl;
        cout << "'quit' or 'check'?" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> temp;
        if (temp == "quit")
            return 0;
        else if (temp == "check")
        {
            cout << "Please input your name:" << endl;
            cin.sync(); //清除缓冲区的数据流
            cin >> user_name;
        }
    }
    cout << "Please input your password:" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> user_password;
    int i = 5; //用来记录次数，最多输入5次
    while (!check_password(user_name, user_password) && i)
    {
        cout << "Wrong password, now you have " << i << " chance to retry." << endl;
        cout << "'quit' or 'retry'?" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> temp;
        while (temp != "quit" && temp != "retry")
        {
            cout << "'quit' or 'retry'?" << endl;
            cin.sync(); //清除缓冲区的数据流
            cin >> temp;
        }
        if (temp == "quit")
            return 0;
        else if (temp == "retry")
        {
            cout << "Please input your password:" << endl;
            cin.sync(); //清除缓冲区的数据流
            cin >> user_password;
            i--;
        }
    }
    if (check_password(user_name, user_password))
    {
        cout << "Sign in successfully!" << endl;
        user_balance = get_balance(user_name);
        //直接修改全局变量，表示此用户已经登录
        // cout << "user_balance:" << user_balance << endl;
        if (check_password(user_name, user_password) == 2)
        {
            all_consumer.set_user_balance(user_balance);
            all_consumer.set_user_name(user_name);
            all_consumer.set_user_password(user_password);
            all_consumer.user_type = 2;
            //同时将all_business的标志位type置0，表示退出
            all_business.user_type = 0;
        }

        if (check_password(user_name, user_password) == 1)
        {
            all_business.set_user_balance(user_balance);
            all_business.set_user_name(user_name);
            all_business.set_user_password(user_password);
            all_business.user_type = 1;
            //同时将all_consumer的标志位type置0，表示退出
            all_consumer.user_type = 0;
            //商家登陆后，将它已经放在店铺里的商品存入business_goods

            business_goods.clear(); //先给清空，也就是清空上一个登录的商家的内容

            for (goods *tmp : v_goods)
            {
                if (tmp->get_goods_owner() == user_name)
                {
                    business_goods.push_back(tmp);
                }
            }
        }
        //登录成功返回用户type
        return check_password(user_name, user_password);
    }
    return 0;
}

int user_func::check_name(const string &name)
{
    for (user *temp : v_user)
    {
        if (temp->get_user_name() == name)
            return temp->get_user_type();
    }
    return 0;
}

int user_func::check_password(const string &name, const string &password)
{
    for (user *temp : v_user)
    {
        if (temp->get_user_name() == name && temp->get_user_password() == password)
        {
            // return temp->user_type;
            return temp->get_user_type();
        }
    }
    return 0;
}

double user_func::get_balance(const string &name)
{
    for (user *temp : v_user)
    {
        if (temp->get_user_name() == name)
            return temp->get_user_balance();
    }
    return 0.0;
}

int user_func::recharge()
{
    if (all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return 2;
    }
    cout << "****************************************" << endl;
    cout << "Now begin to recharge." << endl;
    cout << "****************************************" << endl;
    double money;
    cout << "Please input the money you want to recharge:" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> money;
    while (money < 0.0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong number, please input a positive number or 0.0 to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> money;
        if (money == 0.0)
            return 0;
    }
    all_consumer.set_user_balance(all_consumer.get_user_balance() + money); //先对全局进行修改

    for (user *temp : v_user) //再修改容器里面的
    {
        if (temp->get_user_name() == all_consumer.get_user_name())
        {
            temp->set_user_balance(all_consumer.get_user_balance());
            cout << "Recharge successfully!" << endl;
            return 1;
        }
    }
    return 0;
}

int user_func::reduce_balance(const double &money)
{ //首先检查是否登录
    if (all_business.get_user_type() != 1 && all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return 2;
    }
    if (all_business.get_user_type() == 1) //如果登录的是商家，就是提现功能
    {
        all_business.set_user_balance(all_business.get_user_balance() - money); //先对全局进行修改
        for (user *temp : v_user)                                               //再修改容器里面的
        {
            if (temp->get_user_name() == all_business.get_user_name())
            {
                temp->set_user_balance(all_business.get_user_balance() - money);
                return 1;
            }
        }
    }
    else if (all_consumer.get_user_type() == 2) //如果登录的是消费者，就是购物扣钱功能
    {
        all_consumer.set_user_balance(all_consumer.get_user_balance() - money); //先对全局进行修改
        for (user *temp : v_user)                                               //再修改容器里面的
        {
            if (temp->get_user_name() == all_consumer.get_user_name())
            {
                temp->set_user_balance(all_consumer.get_user_balance() - money);
                return 1;
            }
        }
    }
    return 0;
}

int user_func::business_add()
{
    //首先检查商家是否登录
    if (all_business.get_user_type() != 1)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return 0;
    }
    cout << "****************************************" << endl;
    cout << "Now begin to add your goods." << endl;
    cout << "****************************************" << endl;

    int goods_type;
    string goods_name;
    string goods_description;
    double goods_initprice;
    double goods_price;
    int goods_surplus;
    string goods_owner;
    double discount = 1.0;

    cout << "Please input the type of goods(0 food,1 clothes,2 book):" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> goods_type;
    while ((goods_type != 0 && goods_type != 1 && goods_type != 2) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong number, please input 0 or 1 or 2, or -1 to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> goods_type;
        if (goods_type == -1)
            return 0;
    }
    cout << "Please input the name of goods(no spaces):" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> goods_name;
    //检查是否已经添加过这个名字的商品，如果添加过了，重新输入商品名称
    int curr1 = 1, curr2 = 1;
    while (curr1)
    {
        for (goods *p : business_goods)
        { //同时匹配商品的类型和商品的名称
            curr2 = 1;
            if (p->get_goods_type() == goods_type && p->get_goods_name() == goods_name)
            {
                cout << "Sorry, you have added this goods before, please input another name(no spaces):" << endl;
                cin.sync();        //清除缓冲区的数据流
                cin >> goods_name; //重新输入
                curr2 = 0;
                break;
            }
        }
        if (curr2 == 1) //如果没有匹配到同样的名字，就可以跳出
            curr1 = 0;
    }

    cout << "Please input the description of goods:" << endl;
    // cin >> goods_description;
    cin.sync(); //清除缓冲区的数据流
    getchar();
    getline(cin, goods_description);
    // cout << goods_description;
    cout << "Please input the price of goods:" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> goods_initprice;
    while (goods_initprice < 0.0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong number, please input a number>=0, or -1 to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> goods_initprice;
        if (goods_initprice == -1)
            return 0;
    }
    goods_price = goods_initprice;
    cout << "Please input the surplus of goods:" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> goods_surplus;
    while (goods_surplus < 1 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong number, please input a positive integer, or 0 to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> goods_surplus;
        if (goods_surplus == 0)
            return 0;
    }
    goods_owner = all_business.get_user_name(); //直接赋予名字
    cout << "Please input the discount (0.0,1.0]:" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> discount;
    while (discount <= 0.0 || discount > 1.0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong number, please input a number belongs to (0.0,1.0], or 0.0 to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> discount;
        if (discount == 0.0)
            return 0;
    }
    //确认商家是否添加商品
    string confirm;
    cout << "Sure to add the goods?(yes or no):" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> confirm;
    if (confirm == "no")
    {
        cout << "quit" << endl;
        return 0;
    }
    while (confirm != "yes" && confirm != "no")
    {
        cout << "Please input 'yes' or 'no':" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> confirm;
        if (confirm == "no")
        {
            cout << "quit" << endl;
            return 0;
        }
    }
    //添加到类的容器里面
    if (goods_type == 0)
    {
        goods *p_temp = new goods_Food(
            goods_type, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);

        goods_Food *p_1 = dynamic_cast<goods_Food *>(p_temp);

        p_1->discount = discount;
        v_goods.push_back(p_temp);        //放入所有商品的容器中
        business_goods.push_back(p_temp); //放入此商家的容器中
        cout << "Add in successfully!" << endl;
        return 1;
    }
    else if (goods_type == 1)
    {
        goods *p_temp = new goods_Clothes(
            goods_type, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);

        goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(p_temp);

        p_1->discount = discount;
        v_goods.push_back(p_temp);        //放入所有商品的容器中
        business_goods.push_back(p_temp); //放入此商家的容器中
        cout << "Add in successfully!" << endl;
        return 1;
    }
    else if (goods_type == 2)
    {
        goods *p_temp = new goods_Book(
            goods_type, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);

        goods_Book *p_1 = dynamic_cast<goods_Book *>(p_temp);

        p_1->discount = discount;
        v_goods.push_back(p_temp);        //放入所有商品的容器中
        business_goods.push_back(p_temp); //放入此商家的容器中
        cout << "Add in successfully!" << endl;
        return 1;
    }
    return 0;
}

int user_func::change_password()
{
    string user_name;
    int user_type;
    //如果目前登录的是商家
    if (all_business.get_user_type() == 1)
    {
        user_type = 1;
        user_name = all_business.get_user_name();
    }
    //如果目前登录的是消费者
    else if (all_consumer.get_user_type() == 2)
    {
        user_type = 2;
        user_name = all_consumer.get_user_name();
    }
    //如果都没登录
    else
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return 0;
    }

    cout << "****************************************" << endl;
    cout << "Now begin to change your password." << endl;
    cout << "****************************************" << endl;
    cout << "Please input your old password:" << endl;

    string old_password;
    string new_password;
    cin.sync(); //清除缓冲区的数据流
    cin >> old_password;
    int i = 4; //共有5次输入旧密码的机会
    while (i > 0 && (user_type == 1 || user_type == 2))
    {
        if (user_type == 1)
        {
            if (old_password == all_business.get_user_password())
            {
                cout << "Please input your new password(no spaces):" << endl;
                cin.sync(); //清除缓冲区的数据流
                cin >> new_password;
                //需要修改两个地方
                all_business.set_user_password(new_password);
                for (user *temp : v_user)
                {
                    if (temp->get_user_name() == user_name)
                    {
                        temp->set_user_password(new_password);
                        cout << "Change successfully!" << endl;
                        return 1;
                    }
                }
            }
            else
            {
                string tmp;
                cout << "Wrong password, now you have " << i - 1 << " chance to retry." << endl;
                cout << "'quit' or 'retry'?" << endl;
                cin.sync(); //清除缓冲区的数据流
                cin >> tmp;
                while (tmp != "quit" && tmp != "retry")
                {
                    cout << "'quit' or 'retry'?" << endl;
                    cin.sync(); //清除缓冲区的数据流
                    cin >> tmp;
                }
                if (tmp == "quit")
                    return 0;
                else if (tmp == "retry")
                {
                    cout << "Please input your password:" << endl;
                    cin.sync(); //清除缓冲区的数据流
                    cin >> old_password;
                    i--;
                }
            }
        }
        else
        {
            if (old_password == all_consumer.get_user_password())
            {
                cout << "Please input your new password(no spaces):" << endl;
                cin.sync(); //清除缓冲区的数据流
                cin >> new_password;
                //需要修改两个地方
                all_consumer.set_user_password(new_password);
                for (user *temp : v_user)
                {
                    if (temp->get_user_name() == user_name)
                    {
                        temp->set_user_password(new_password);
                        cout << "Change successfully!" << endl;
                        return 1;
                    }
                }
            }
            else
            {
                string tmp;
                cout << "Wrong password, now you have " << i << " chance to retry." << endl;
                cout << "'quit' or 'retry'?" << endl;
                cin.sync(); //清除缓冲区的数据流
                cin >> tmp;
                while (tmp != "quit" && tmp != "retry")
                {
                    cout << "'quit' or 'retry'?" << endl;
                    cin.sync(); //清除缓冲区的数据流
                    cin >> tmp;
                }
                if (tmp == "quit")
                    return 0;
                else if (tmp == "retry")
                {
                    cout << "Please input your password:" << endl;
                    cin.sync(); //清除缓冲区的数据流
                    cin >> old_password;
                    i--;
                }
            }
        }
    }
    return 0;
}

void user_func::show_consumer()
{
    //检查消费者是否登录
    if (all_consumer.get_user_type() != 2)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return;
    }
    //如果消费者已经登陆成功了
    cout << "****************************************" << endl;
    cout << "Now begin to show your information." << endl;
    cout << "****************************************" << endl;
    cout << "Your name is " << all_consumer.get_user_name() << "." << endl;
    cout << "Your authority is a consumer." << endl;
    cout << "Your balance is " << all_consumer.get_user_balance() << "." << endl;
    return;
}

void user_func::show_business()
{
    //检查商家是否登录
    if (all_business.get_user_type() != 1)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return;
    }
    //如果商家已经登陆成功
    cout << "****************************************" << endl;
    cout << "Now begin to show your information." << endl;
    cout << "****************************************" << endl;
    cout << "Your name is " << all_business.get_user_name() << "." << endl;
    cout << "Your authority is a business." << endl;
    cout << "Your balance is " << all_business.get_user_balance() << "." << endl;
    //下面展示该商家店铺下的所有商品
    cout << "****************************************" << endl;
    cout << "Now begin to show your goods information." << endl;
    cout << "****************************************" << endl;
    goods_func goods;
    //直接调用写好的函数打印商品
    goods.goods_merchant_interface(all_business.get_user_name());
    return;
}

int user_func::change_goods()
{
    //检查商家是否登录
    if (all_business.get_user_type() != 1)
    {
        cout << "Sorry, you haven't sign in, please sign in first." << endl;
        return 0;
    }
    //如果商家已经登陆成功
    cout << "****************************************" << endl;
    cout << "Now begin to change your goods." << endl;
    cout << "****************************************" << endl;

    string goods_kind;
    string goods_name;
    string goods_description;
    double goods_price;
    int goods_surplus;
    string goods_owner;
    int goods_type;
    double discount;

    //先询问商品类别，查看是否需要整体打折
    cout << "Which kind of goods do you want to change?" << endl;
    cout << "'food','clothes','book'" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> goods_kind;
    while ((goods_kind != "food" && goods_kind != "clothes" && goods_kind != "book") || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong kind, please input 'food' or 'clothes' or 'book', or '#' to quit:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> goods_kind;
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

    cout << "Do you want to give a discount to all the " << goods_kind << " ?('yes' or 'no')" << endl;
    string temp;
    cin.sync(); //清除缓冲区的数据流
    cin >> temp;
    while ((temp != "yes" && temp != "no") || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear(); //更改cin的状态标识符
            cin.sync();  //清除缓冲区的数据流
        }
        cout << "Wrong command, please input 'yes' or 'no':" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> temp;
    }
    if (temp == "yes")
    {
        cout << "Please input the discount (0.0,1.0]:" << endl;
        cin.sync(); //清除缓冲区的数据流
        cin >> discount;
        while (discount <= 0.0 || discount > 1.0 || cin.fail())
        {
            if (cin.fail())
            {
                cin.clear(); //更改cin的状态标识符
                cin.sync();  //清除缓冲区的数据流
            }
            cout << "Wrong number, please input a number belongs to (0.0,1.0]:" << endl;
            cin.sync(); //清除缓冲区的数据流
            cin >> discount;
        }
        //修改打折信息
        for (goods *tmp : business_goods)
        {
            if (tmp->get_goods_type() == 0 && goods_type == 0) //food
            {
                goods_Food *p_1 = dynamic_cast<goods_Food *>(tmp);
                p_1->discount = discount;
            }
            else if (tmp->get_goods_type() == 1 && goods_type == 1) //food
            {
                goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(tmp);
                p_1->discount = discount;
            }
            else if (tmp->get_goods_type() == 2 && goods_type == 2) //food
            {
                goods_Book *p_1 = dynamic_cast<goods_Book *>(tmp);
                p_1->discount = discount;
            }
        }
        cout << "Change discount successfully(only the discount is changed)!" << endl;
    }

    //下面针对某一个商品进行更加细致的修改操作
    cout << "Which goods do you want to change?" << endl;
    cin.sync(); //清除缓冲区的数据流
    cin >> goods_name;
    //判断这个商品是否存在
    int flag = 1; //提供循环操作
    int id;       //提供选择不同操作的功能
    while (flag)
    {
        for (goods *tmp : business_goods)
        {
            if (tmp->get_goods_type() == goods_type && tmp->get_goods_name() == goods_name) //同时满足类别和商品名称
            {
                flag = 0; //表示找到了
                while (1)
                {
                    cout << "What kind of operation do you want to do?" << endl;
                    cout << "1:Change the description of goods." << endl;
                    cout << "2:Change the price of goods." << endl;
                    cout << "3:Delete this good." << endl;
                    cout << "4:Change surplus." << endl;
                    cout << "0:Quit." << endl;
                    cout << "Please input the id:" << endl;
                    cin.sync(); //清除缓冲区的数据流
                    cin >> id;  //输入id
                    while ((id != 0 && id != 1 && id != 2 && id != 3 && id != 4) || cin.fail())
                    {
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.sync();
                        }
                        cout << "Wrong id, please input 0 or 1 or 2 or 3:" << endl;
                        cin.sync(); //清除缓冲区的数据流
                        cin >> id;
                    }
                    if (id == 0)
                        return 0;
                    else if (id == 1)
                    {
                        cout << "Please input the new description:" << endl;
                        cin.sync(); //清除缓冲区的数据流
                        getchar();
                        getline(cin, goods_description);
                        // cin >> goods_description;
                        // //对business_goods和大容器进行修改
                        // tmp->set_goods_description(goods_description);
                    }
                    else if (id == 2)
                    {
                        cout << "Please input the new price:" << endl;
                        cin.sync(); //清除缓冲区的数据流
                        cin >> goods_price;
                        while (goods_price < 0.0 || cin.fail())
                        {
                            if (cin.fail())
                            {
                                cin.clear(); //更改cin的状态标识符
                                cin.sync();  //清除缓冲区的数据流
                            }
                            cout << "Wrong number, please input a number>=0.0:" << endl;
                            cin.sync(); //清除缓冲区的数据流
                            cin >> goods_price;
                        }
                    }
                    else if (id == 4)
                    {
                        cout << "Please input the new surplus:" << endl;
                        cin.sync(); //清除缓冲区的数据流
                        cin >> goods_surplus;
                        while (goods_surplus < 1 || cin.fail())
                        {
                            if (cin.fail())
                            {
                                cin.clear(); //更改cin的状态标识符
                                cin.sync();  //清除缓冲区的数据流
                            }
                            cout << "Wrong number, please input a positive integer:" << endl;
                            cin.sync(); //清除缓冲区的数据流
                            cin >> goods_surplus;
                        }
                    }
                    else //id=3，删除操作
                    {
                        // //首先在business_goods中删除
                        // tmp = business_goods.erase(tmp);
                        // //再在v_goods中删除
                        // for (goods *del : v_goods)
                        // {
                        //     if (del->get_goods_type() == goods_type && del->get_goods_name() == goods_name)
                        //         del = v_goods.erase(del);
                        // }

                        //首先在business_goods中删除
                        for (vector<goods *>::iterator it = business_goods.begin(); it != business_goods.end();)
                        {
                            if (*it == tmp)
                                it = business_goods.erase(it);
                            else
                                ++it;
                        }
                        //再在v_goods中删除
                        for (vector<goods *>::iterator it = v_goods.begin(); it != v_goods.end();)
                        {
                            if (*it == tmp)
                                it = v_goods.erase(it);
                            else
                                ++it;
                        }

                        cout << "Delete successfully! Now quit." << endl;
                        return 0;
                    }
                    //对business_goods和大容器进行修改
                    if (id == 1)
                        tmp->set_goods_description(goods_description); //对business_goods和大容器进行修改
                    else if (id == 2)
                        tmp->set_goods_price(goods_price);
                    else if (id == 4)
                        tmp->set_goods_surplus(goods_surplus);
                }
            }
        }
        if (flag == 1)
        {
            cout << "Sorry, the goods is not found, please check your input:" << endl;
            cin.sync(); //清除缓冲区的数据流
            cin >> goods_name;
        }
    }
    return 0;
}
