#include "cart_func.h"
#include <iostream>

int cart_func::add_cart()
{
	stringstream sstream;
	string ss;
	int r;
	if (all_consumer.get_user_type() != 2)
	{
		//发送0，表示未登录
		sstream.str("");
		sstream.clear();
		sstream << 0;
		//strcpy(buff_out, (sstream.str()).c_str());
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//发送1，表示登录
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	string cart_owner = all_consumer.get_user_name();
	//接收发来的ack
	server::reve_ACK();
	//紧接着我们需要先检查是否有订单未支付，有的话传过去1，没有的话传过去0
	r = server::check_order_wait(cart_owner);
	sstream.str("");
	sstream.clear();
	sstream << r;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
	if (r == 1)
	{
		cout << "an order wait" << endl;
		return 2;
	}

	//如果没有订单未支付
	//此时自动向客户端发送所有的商品
	goods_func::goods_init_interface();
	int choose = 0;//0为不需要，1为需要
	//此时接收客户端的信息，是否根据名称查询以及需要查询的商品
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "来自客户端的消息:" << buff_in << endl;
		ss = buff_in;
		sstream.str("");
		sstream.clear();
		sstream << ss;
		sstream >> choose;
	}
	sstream.str("");
	sstream.clear();
	int num = 5;
	while (choose == 1 && num > 0)
	{
		//在这个函数内部，会接受来自客户端的数据，并根据数据反馈
		r = goods_func::goods_name_interface();
		if (r == 1)//表示找到了
			choose = 0;
		//这里限定最多输入5次，然后会不再允许输入
		else
			num--;
	}
	//接收来自客户端的商品信息，判断商品存在后确定购买数量
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int goods_surplus;
	int goods_type = -1;
	int status = 0;
	int flag = 1;
	while (flag)
	{
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "来自客户端的消息:" << buff_in << endl;
			ss = buff_in;
			sstream.str("");
			sstream.clear();
			//顺序应该是商品类别，商品所有者
			sstream << ss;
			sstream >> goods_type;
			sstream >> goods_owner;
		}
		//发一个ack
		server::send_ACK();
		//然后接收商品的名称
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "来自客户端的消息:" << buff_in << endl;
			goods_name = buff_in;
		}
		//下面检查该商品是否真的存在
		goods* tmp = server::check_goods_exist(goods_type, goods_name, goods_owner);
		if (tmp == NULL)//没有找到商品，传过去-1
		{
			cout << "goods not exist" << endl;
			sstream.str("");
			sstream.clear();
			sstream << -1;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);

			//然后接收客户端是否继续寻找商品的信号，0表示退出，1为继续
			r = recv(clientSocket, buff_in, 1023, NULL);
			if (r > 0) {
				buff_in[r] = 0;
				cout << "来自客户端的消息:" << buff_in << endl;
				ss = buff_in;
				sstream.str("");
				sstream.clear();
				if (ss == "0")//表示退出
					return 0;
			}
		}

		else//找到商品，传过去剩余量
		{
			goods_surplus = tmp->get_goods_surplus();
			cout << "goods exist" << endl;
			sstream.str("");
			sstream.clear();
			sstream << goods_surplus;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);


			//然后接收要购买的数量
			r = recv(clientSocket, buff_in, 1023, NULL);
			if (r > 0) {
				buff_in[r] = 0;
				cout << "来自客户端的消息:" << buff_in << endl;
				ss = buff_in;
				sstream.str("");
				sstream.clear();
				sstream << ss;
				sstream >> goods_quantity;
				//system("pause");
			}
			//需要判断一下商品是不是已经存在于购物车中
			cart* m = server::check_cart_exist(goods_type, goods_name, goods_owner, cart_owner);
			if (m == NULL)//是一个新的商品
			{
				//传过去-1并添加商品
				sstream.str("");
				sstream.clear();
				sstream << -1;
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				cart* temp = new cart(status, cart_owner, tmp, goods_quantity, goods_type, goods_name, goods_owner);
				v_cart.push_back(temp);
				cout << "Add successfully!" << endl;
				//system("pause");
			}
			else
			{
				//传过去1并修改商品购买量
				sstream.str("");
				sstream.clear();
				sstream << 1;
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				m->set_cart_quantity(m->get_cart_quantity() + goods_quantity);
				cout << "The goods has existed, now add the quantity." << endl;
				cout << "Add successfully!" << endl;
				//system("pause");
			}
			flag = 0;
			return 1;//添加成功，客户端在传送购买量自动显示添加成功
			//不用再循环接收了
		}
	}

}

int cart_func::change_cart()
{
	stringstream sstream;
	string ss;
	int r;
	if (all_consumer.get_user_type() != 2)
	{
		//发送0，表示未登录
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//发送1，表示登录
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	string cart_owner = all_consumer.get_user_name();
	server::reve_ACK();
	//传过去购物车的信息
	show_cart(cart_owner);
	server::reve_ACK();
	//紧接着我们需要先检查是否有订单未支付，有的话传过去1，没有的话传过去0
	r = server::check_order_wait(cart_owner);
	sstream.str("");
	sstream.clear();
	sstream << r;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
	if (r == 1)
	{
		cout << "an order wait" << endl;
		return 2;
	}

	//如果没有订单未支付
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int goods_type;
	int flag = 1;
	//从客户端接收要修改的购物车的信息
	//顺序为商品类别，商品所有者
	//然后是商品名称
	while (flag)
	{
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "来自客户端的消息:" << buff_in << endl;
			ss = buff_in;
			sstream.str("");
			sstream.clear();
			sstream << ss;
			sstream >> goods_type;
			sstream >> goods_owner;
		}
		server::send_ACK();
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "来自客户端的消息:" << buff_in << endl;
			ss = buff_in;
			sstream.str("");
			sstream.clear();
			sstream << ss;
			sstream >> goods_name;
		}
		//判断这个信息是不是真的在购物车中
		cart* m = server::check_cart_exist(goods_type, goods_name, goods_owner, cart_owner);
		if (m == NULL)//传过去-1表示没找到
		{
			cout << "not found" << endl;
			sstream.str("");
			sstream.clear();
			sstream << -1;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			//需要再次传数据
		}
		else//传过去1表示找到了
		{
			flag = 0;
			cout << "found" << endl;
			sstream.str("");
			sstream.clear();
			sstream << 1;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			//下面询问客户端想要的操作，1:Change quantity.2:Delete this goods.0:Quit.
			int id = 0;
			r = recv(clientSocket, buff_in, 1023, NULL);
			if (r > 0) {
				buff_in[r] = 0;
				cout << "来自客户端的消息:" << buff_in << endl;
				ss = buff_in;
				sstream.str("");
				sstream.clear();
				sstream << ss;
				sstream >> id;
			}
			//发送ack
			server::send_ACK();

			if (id == 0)//退出
			{
				cout << "quit" << endl;
				return 1;
			}
			else if (id == 1)
			{
				//从客户端接收新的购买数量
				r = recv(clientSocket, buff_in, 1023, NULL);
				if (r > 0) {
					buff_in[r] = 0;
					cout << "来自客户端的消息:" << buff_in << endl;
					ss = buff_in;
					sstream.str("");
					sstream.clear();
					sstream << ss;
					sstream >> goods_quantity;
				}
				m->set_cart_quantity(goods_quantity);
			}
			else
			{
				//从购物车中删除
				for (vector<cart*>::iterator it = v_cart.begin(); it != v_cart.end();)
				{
					if (*it == m)
						it = v_cart.erase(it);
					else
						it++;
				}
				return 1;
			}
		}
	}
	return 1;
}

void cart_func::show_cart(string owner)//将这个人的购物车信息传回去，指针就用NULL代替
{
	stringstream sstream;
	string ss;
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int goods_type;
	int status = 0;
	int flag = 1;

	//传回去的顺序为：商品类别，商品现价，商品所有者，商品购买量，是否已经生成订单
	//商品的名称，商品的描述
	//传回去-1表示结束
	for (cart* temp : v_cart)
	{
		if (temp->get_cart_owner() == owner)
		{
			sstream.str("");
			sstream.clear();
			sstream << temp->get_cart_want()->get_goods_type() << " ";
			sstream << temp->get_cart_want()->get_goods_price_change() << " ";
			sstream << temp->get_cart_want()->get_goods_owner() << " ";
			sstream << temp->get_cart_quantity() << " ";
			sstream << temp->get_cart_status();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();
			sstream << temp->get_cart_want()->get_goods_name();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();

			sstream.str("");
			sstream.clear();
			sstream << temp->get_cart_want()->get_goods_description();
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			server::reve_ACK();
		}
	}
	sstream.str("");
	sstream.clear();
	sstream << -1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
}

int cart_func::generate_order()
{
	stringstream sstream;
	string ss;
	int r;
	if (all_consumer.get_user_type() != 2)
	{
		//发送0，表示未登录
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//发送1，表示登录
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	server::reve_ACK();

	string cart_owner = all_consumer.get_user_name();
	//传过去购物车的信息
	show_cart(cart_owner);
	//接收数据，查看消费者是否确定要生成订单
	int flag = 1;
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "来自客户端的消息:" << buff_in << endl;
		ss = buff_in;
		sstream.str("");
		sstream.clear();
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)//不想生成
	{
		cout << "Cancel successfully." << endl;
		return 0;
	}
	//确定要生成
	flag = 0;
	//检查用户购物车的每一项的商品购买数量是否超过了商家目前的剩余量
	//不单独告知了，直接在客户端告诉用户，我们将所有购买量过大的减小到剩余量了
	for (cart* temp : v_cart)
	{
		if (temp->get_cart_owner() == cart_owner && temp->get_cart_status() == 0)
		{
			flag = 1;
			if (temp->get_cart_quantity() > temp->get_cart_want()->get_goods_surplus())
			{
				cout << "The quantity you want is over the surplus of " << temp->get_cart_want()->get_goods_name() << endl;
				temp->set_cart_quantity(temp->get_cart_want()->get_goods_surplus());
			}
			temp->set_cart_status(1);
			//商品剩余量减少
			temp->get_cart_want()->set_goods_surplus(temp->get_cart_want()->get_goods_surplus() - temp->get_cart_quantity());
		}
	}
	if (flag == 1)
	{
		//发送1表示成功生成订单
		cout << "All the goods has been generated." << endl;
		sstream.str("");
		sstream.clear();
		sstream << 1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return 1;
	}
	else
	{
		//发送-1表示在这之前已经生成订单
		cout << "All the goods has been generated before." << endl;
		sstream.str("");
		sstream.clear();
		sstream << -1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return 0;
	}
}

int cart_func::pay_or_cancel_order()
{
	stringstream sstream;
	string ss;
	int r;
	int flag = 0;
	if (all_consumer.get_user_type() != 2)
	{
		//发送0，表示未登录
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//发送1，表示登录
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	server::reve_ACK();
	string cart_owner = all_consumer.get_user_name();
	//下面检查订单是否已经生成，生成了传1，未生成传0，购物车就没有的传-1
	for (cart* temp : v_cart)
	{
		if (temp->get_cart_owner() == cart_owner) //找到
		{
			flag = 1;
			if (temp->cart_status == 0) //尚未生成订单
			{
				cout << "Sorry, you haven't generate an order." << endl;
				sstream.str("");
				sstream.clear();
				sstream << 0;
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket2, buff_out, strlen(buff_out), NULL);
				return 0;
			}
		}
	}
	if (flag == 1)
	{
		sstream.str("");
		sstream.clear();
		sstream << 1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}
	if (flag == 0)
	{
		cout << "Sorry, you haven't add anything to your cart." << endl;
		sstream.str("");
		sstream.clear();
		sstream << -1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return 0;
	}
	//客户端发来信息，1表示不删除订单，0表示删除订单
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "来自客户端的消息:" << buff_in << endl;
		ss = buff_in;
		sstream.str("");
		sstream.clear();
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)
	{
		for (cart* temp : v_cart)
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
	//如果不删除，就是支付
	double all_money = 0.0;
	for (cart* temp : v_cart)
	{
		//获取总共的价格
		if (temp->get_cart_owner() == cart_owner)
		{
			all_money = all_money + temp->get_cart_want()->get_goods_price_change() * temp->get_cart_quantity(); //注意！！！不能保证正确，等待测试
		}
	}
	//将总共的价格传回去
	sstream.str("");
	sstream.clear();
	sstream << all_money;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
	//接收ack
	server::reve_ACK();
	//判断一下是否超过了用户的余额
	if (all_money > all_consumer.get_user_balance())
	{
		cout << "Sorry, your balance is not enough. Please recharge." << endl;
		//传回1表示超过了，0表示没超过
		sstream.str("");
		sstream.clear();
		sstream << 1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return 2;
	}
	else
	{
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
	}
	//完成操作，商家增钱，消费者扣钱，购物车清空
	string business_owner;
	for (cart* temp : v_cart)
	{
		if (temp->get_cart_owner() == cart_owner) //找到购物车
		{
			business_owner = temp->get_cart_want()->get_goods_owner();
			for (user* tmp : v_user) //找到商家
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
	for (vector<cart*>::iterator it = v_cart.begin(); it != v_cart.end();)
	{
		if ((*it)->get_cart_owner() == cart_owner)
			it = v_cart.erase(it);
		else
			++it;
	}
	//扣钱要扣两个地方，all_consumer和v_user
	all_consumer.set_user_balance(all_consumer.get_user_balance() - all_money);
	for (user* temp : v_user)
	{
		if (temp->get_user_name() == all_consumer.get_user_name())
		{
			temp->set_user_balance(temp->get_user_balance() - all_money);
		}
	}
	cout << "Pay successfully!" << endl;
	//传回去余额
	sstream.str("");
	sstream.clear();
	sstream << all_consumer.get_user_balance();
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	return 1;
}