#include "user.h"
#include <iostream>

/***********user类***********/
void user::set_user_name(string name = "user_name")
{
    user_name = name;
}
string user::get_user_name() const
{
    return user_name;
}

void user::set_user_password(string password = "user_password")
{
    user_password = password;
}
string user::get_user_password() const
{
    return user_password;
}

void user::set_user_balance(double balance = 0.0)
{
    user_balance = balance;
}
double user::get_user_balance() const
{
    return user_balance;
}

void user::set_user_type(int type = 0)
{
    user_type = type;
}

/***********business类***********/
user_Business::user_Business(int type,
                             string name,
                             string password,
                             double balance)
{
    set_user_name(name);
    set_user_password(password);
    set_user_balance(balance);
    set_user_type(type);
}
int user_Business::get_user_type()
{
    return user_type;
}

/***********consumer类***********/
user_Consumer::user_Consumer(int type,
                             string name,
                             string password,
                             double balance)
{
    set_user_name(name);
    set_user_password(password);
    set_user_balance(balance);
    set_user_type(type);
}
int user_Consumer::get_user_type()
{
    return user_type;
}