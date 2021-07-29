#ifndef USER_H
#define USER_H

using namespace std;
#include <string>

class user //�û�-����
{
private:
    string user_name;     //�û����˻���
    string user_password; //�û�������
    double user_balance;  //�û������
public:
    int user_type; //�û������ͣ�0Ϊ�οͣ�1Ϊ�̼ң�2Ϊ������

    void set_user_name(string name); //��ʼ�������û����˺���
    string get_user_name() const;    //��ȡ�û����˺���

    void set_user_password(string password); //��ʼ�����޸��û�������
    string get_user_password() const;        //��ȡ�û�������

    void set_user_balance(double balance); //�ṩ�û���ֵ���޸�
    double get_user_balance() const;       //��ȡ�û������

    void set_user_type(int type);    //��ʼ���û�������
    virtual int get_user_type() = 0; //��ȡ�û�������
    virtual ~user() = default;
};

class user_Business : public user //�̼���
{
public:
    user_Business(int user_type,
                  string user_name,
                  string user_password,
                  double user_balance);
    int get_user_type() override; //��ȡ�û�����
};

class user_Consumer : public user //��������
{
public:
    user_Consumer(int user_type,
                  string user_name,
                  string user_password,
                  double user_balance);
    int get_user_type() override; //��ȡ�û�����
};

#endif