#ifndef USER_H
#define USER_H

using namespace std;
#include <string>

class user //用户-父类
{
private:
    string user_name;     //用户的账户名
    string user_password; //用户的密码
    double user_balance;  //用户的余额
public:
    int user_type; //用户的类型，0为游客，1为商家，2为消费者

    void set_user_name(string name); //初始化输入用户的账号名
    string get_user_name() const;    //获取用户的账号名

    void set_user_password(string password); //初始化或修改用户的密码
    string get_user_password() const;        //获取用户的密码

    void set_user_balance(double balance); //提供用户充值或修改
    double get_user_balance() const;       //获取用户的余额

    void set_user_type(int type);    //初始化用户的类型
    virtual int get_user_type() = 0; //获取用户的类型
    virtual ~user() = default;
};

class user_Business : public user //商家类
{
public:
    user_Business(int user_type,
                  string user_name,
                  string user_password,
                  double user_balance);
    int get_user_type() override; //获取用户类型
};

class user_Consumer : public user //消费者类
{
public:
    user_Consumer(int user_type,
                  string user_name,
                  string user_password,
                  double user_balance);
    int get_user_type() override; //获取用户类型
};

#endif