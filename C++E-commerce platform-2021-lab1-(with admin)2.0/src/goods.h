#ifndef GOODS_H
#define GOODS_H

using namespace std;
#include <string>
#define ALL 3
extern double all_discount[ALL];

class goods //��Ʒ-����
{
private:
    int goods_type;           //��Ʒ�����ĿǰΪ���֣�ʳ��0����װ1��ͼ��2
    string goods_name;        //��Ʒ������
    string goods_description; //��Ʒ������
    double goods_initprice;   //��Ʒԭ�ȵļ۸񣬼�¼����Ʒʱ�ļ۸�
    double goods_price;       //��Ʒ���ڵļ۸�
    int goods_surplus;        //��Ʒ��ʣ����

    string goods_owner; //��Ʒ�����̼�
public:
    void set_goods_name(string name); //��ʼ�����޸���Ʒ������
    string get_goods_name() const;    //��ȡ��Ʒ������

    void set_goods_description(string description); //��ʼ�����޸���Ʒ������
    string get_goods_description() const;           //��ȡ��Ʒ������

    void set_goods_initprice(double initprice); //��ʼ����Ʒ�ļ۸�ͬʱ��ʼ����Ʒ���ּۣ�֮�������޸ĳ�ʼ�۸�
    double get_goods_initprice() const;         //��ȡ��Ʒ�ĳ�ʼ�۸�

    void set_goods_price(double price);          //�޸���Ʒ���ּۣ��������۵�����
    double get_goods_price() const;              //��ȡ��Ʒ�ļ۸񣬲��������ۣ������޸ĺ��
    virtual double get_goods_price_change() = 0; //��ȡ��Ʒ���ּۣ��������۵�����

    void set_goods_surplus(int surplus); //��ʼ�����޸���Ʒ��ʣ����
    int get_goods_surplus() const;       //��ȡ��Ʒ��ʣ����

    void set_goods_type(int type); //��ʼ����Ʒ�����
    int get_goods_type() const;    //��ȡ��Ʒ�����

    void set_goods_owner(string temp); //��ʼ����Ʒ�������̼�,�̼ҵ�¼��ſ������룬���Բ��ôӼ������룬ֱ�ӽ��̼ҵ��˺������ƽ�ȥ
    string get_goods_owner() const;    //��ȡ��Ʒ�������̼�
    virtual ~goods() = default;
};

class goods_Food : public goods //ʳ����
{
public:
    static double discount; //�ۿ�
    goods_Food(
        int goods_type,
        string goods_name,
        string goods_description,
        double goods_initprice,
        double goods_price,
        int goods_surplus,

        string goods_owner);
    // goods_Food::goods_Food(int goods_type);
    double get_goods_price_change() override; //��ȡ���ۺ�ļ۸�
};

class goods_Clothes : public goods //��װ��
{
public:
    static double discount; //�ۿ�
    goods_Clothes(
        int goods_type,
        string goods_name,
        string goods_description,
        double goods_initprice,
        double goods_price,
        int goods_surplus,
        string goods_owner);
    double get_goods_price_change() override; //��ȡ���ۺ�ļ۸�
};

class goods_Book : public goods //�鼮��
{
public:
    static double discount; //�ۿ�
    goods_Book(
        int goods_type,
        string goods_name,
        string goods_description,
        double goods_initprice,
        double goods_price,
        int goods_surplus,
        string goods_owner);
    double get_goods_price_change() override; //��ȡ���ۺ�ļ۸�
};

#endif