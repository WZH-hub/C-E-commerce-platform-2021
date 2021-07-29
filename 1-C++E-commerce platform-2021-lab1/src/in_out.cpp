#include "in_out.h"

void in_out::read_in_goods(vector<goods *> &p)
{
    ifstream fp("goods.txt"); //打开文件
    if (!fp.is_open())        //检测是否成功打开
    {
        cout << "error,can't open goods.txt" << endl;
        return;
    }
    string temp;
    //首先读入第一行的数据，为管理员对商品的整体打折信息
    getline(fp, temp);
    int i, k;
    k = temp.length(); //长度
    char admin_temp[k + 1];
    for (i = 0; i < k; i++)
        admin_temp[i] = temp[i];
    //读入数据，为打折信息
    sscanf(admin_temp, "%lf %lf %lf", &all_discount[0], &all_discount[1], &all_discount[2]);

    while (getline(fp, temp))
    {
        int num = temp.length();
        char ch_temp[num + 1];
        int j = 6; //一共有6个数据,discount
        double k;
        for (i = 0; i < num; i++) //从string到char*
            ch_temp[i] = temp[i];
        ch_temp[num] = '#'; //为了防止之前的ch_temp有多的字符

        int goods_type;
        string goods_name;
        string goods_description;
        double goods_initprice;
        double goods_price;
        int goods_surplus;
        string goods_owner;
        double discount = 1.0;

        char *s;
        s = strtok(ch_temp, " "); //以空格为分隔符划分数据
        while (j--)
        {
            switch (j + 1)
            {
            case 6:
                sscanf(s, "%d", &i); //将字符串转为整型i
                goods_type = i;
                break;
            // case 6:
            //     goods_name = s;
            //     break;
            // case 6:
            //     goods_description = s;
            //     break;
            case 5:
                sscanf(s, "%lf", &k);
                goods_initprice = k;
                break;
            case 4:
                sscanf(s, "%lf", &k);
                goods_price = k;
                break;
            case 3:
                sscanf(s, "%d", &i); //将字符串转为整型i
                goods_surplus = i;
                break;
            case 2:
                goods_owner = s;
                break;
            case 1:
                sscanf(s, "%lf", &k);
                discount = k;
                break;
            }
            s = strtok(NULL, " ");
        }
        getline(fp, goods_name);
        getline(fp, goods_description);
        if (goods_type == 0)
        {
            // goods_Food *p_temp = new goods_Food(
            //     goods_price, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);
            goods *p_temp = new goods_Food(
                goods_type, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);

            goods_Food *p_1 = dynamic_cast<goods_Food *>(p_temp);

            p_1->discount = discount;
            p.push_back(p_temp);
        }
        else if (goods_type == 1)
        {
            // goods_Clothes *p_temp = new goods_Clothes(
            //     goods_price, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);
            // p_temp->discount = discount;
            goods *p_temp = new goods_Clothes(
                goods_type, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);

            goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(p_temp);

            p_1->discount = discount;
            p.push_back(p_temp);
        }
        else if (goods_type == 2)
        {
            // goods_Book *p_temp = new goods_Book(
            //     goods_price, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);
            goods *p_temp = new goods_Book(
                goods_type, goods_name, goods_description, goods_initprice, goods_price, goods_surplus, goods_owner);

            goods_Book *p_1 = dynamic_cast<goods_Book *>(p_temp);

            p_1->discount = discount;
            p.push_back(p_temp);
        }
    }
    fp.close();
    cout << "Read in goods.txt successfully." << endl;
}

void in_out::read_in_user(vector<user *> &p)
{
    ifstream fp("user.txt"); //打开文件
    if (!fp.is_open())
    {
        cout << "error,can't open user.txt" << endl;
        return;
    }
    string temp;

    // getline(fp, temp);
    // while (!fp.eof())
    // cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    while (getline(fp, temp))
    {
        // cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        int num = temp.length();
        char ch_temp[num + 1];
        int i;
        double k;
        int j = 4;                //一共有4个数据
        for (i = 0; i < num; i++) //从string到char*
            ch_temp[i] = temp[i];
        ch_temp[num] = '#'; //为了防止之前的ch_temp有多的字符

        int user_type;
        string user_name;
        string user_password;
        double user_balance;

        char *s;
        s = strtok(ch_temp, " "); //以空格为分隔符划分数据
        while (j--)
        {
            // cout << "s:" << s << endl;
            switch (j + 1)
            {
            case 4:
                sscanf(s, "%d", &i);
                user_type = i;
                break;
            case 3:
                user_name = s;
                break;
            case 2:
                user_password = s;
                break;
            case 1:

                sscanf(s, "%lf", &k);
                // cout << "k:" << k << endl;
                user_balance = k;
                // k = 0.0;
                break;
            }
            s = strtok(NULL, " ");
        }
        if (user_type == 1)
        {
            user_Business *p_temp = new user_Business(user_type, user_name, user_password, user_balance);
            p.push_back(p_temp);
        }
        else if (user_type == 2)
        {
            user_Consumer *p_temp = new user_Consumer(user_type, user_name, user_password, user_balance);
            p.push_back(p_temp);
        }
        // getline(fp, temp);
    }
    fp.close();
    cout << "Read in user.txt successfully." << endl;
}

void in_out::read_out_goods(const vector<goods *> p)
{
    ofstream fp("goods.txt");
    if (!fp.is_open()) //检测是否成功打开
    {
        cout << "error,can't open goods.txt" << endl;
        return;
    }
    //读入管理员打折信息
    fp << all_discount[0] << " ";
    fp << all_discount[1] << " ";
    fp << all_discount[2] << endl;
    //读入商品的信息
    for (goods *temp : p)
    {
        fp << temp->get_goods_type() << " ";
        // fp << temp->get_goods_name() << " ";
        // fp << temp->get_goods_description() << " ";
        fp << temp->get_goods_initprice() << " ";
        fp << temp->get_goods_price() << " ";
        fp << temp->get_goods_surplus() << " ";
        fp << temp->get_goods_owner() << " ";

        if (temp->get_goods_type() == 0)
        {
            goods_Food *p_1 = dynamic_cast<goods_Food *>(temp);
            fp << p_1->discount << "\n";
        }
        else if (temp->get_goods_type() == 1)
        {
            goods_Clothes *p_1 = dynamic_cast<goods_Clothes *>(temp);
            fp << p_1->discount << "\n";
        }
        else if (temp->get_goods_type() == 2)
        {
            goods_Book *p_1 = dynamic_cast<goods_Book *>(temp);
            fp << p_1->discount << "\n";
        }
        fp << temp->get_goods_name() << endl;
        fp << temp->get_goods_description() << endl;
    }
    fp.close();
    cout << "Read out goods.txt successfully." << endl;
}

void in_out::read_out_user(const vector<user *> p)
{
    ofstream fp("user.txt");
    if (!fp.is_open()) //检测是否成功打开
    {
        cout << "error,can't open user.txt" << endl;
        return;
    }
    for (user *temp : p)
    {
        if (temp->user_type == 1)
        {
            user_Business *p_1 = dynamic_cast<user_Business *>(temp);
            fp << p_1->get_user_type() << " ";
        }
        else if (temp->user_type == 2)
        {
            user_Consumer *p_1 = dynamic_cast<user_Consumer *>(temp);
            fp << p_1->get_user_type() << " ";
        }
        if (temp->user_type == 1 || temp->user_type == 2)
        {
            fp << temp->get_user_name() << " ";
            fp << temp->get_user_password() << " ";
            fp << temp->get_user_balance() << "\n";
        }
    }
    fp.close();
    cout << "Read out user.txt successfully." << endl;
}

void in_out::delete_goods(vector<goods *> &p)
{
    for (vector<goods *>::iterator it = p.begin(); it != p.end(); it++)
    {
        if (NULL != *it)
        {
            delete *it;
            *it = NULL;
        }
    }
    p.clear();
}

void in_out::delete_user(vector<user *> &p)
{
    for (vector<user *>::iterator it = p.begin(); it != p.end(); it++)
    {
        if (NULL != *it)
        {
            delete *it;
            *it = NULL;
        }
    }
    p.clear();
}