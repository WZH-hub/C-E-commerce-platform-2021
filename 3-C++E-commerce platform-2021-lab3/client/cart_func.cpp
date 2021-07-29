#include "cart_func.h"
#include <iostream>


void cart_func::show_cart(string cart_owner)
{
	cout << "****************************************" << endl;
	cout << "Here is cart of " << cart_owner << endl;
	cout << "****************************************" << endl;
	stringstream sstream;
	string ss;
	string goods_name;
	string goods_owner;
	string goods_description;
	int goods_quantity;
	int goods_type = 0;
	string type;
	int status = 0;
	int flag = 1;
	int m, i = 1;
	double goods_price_change;
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> goods_type;
	}
	while (goods_type != -1)
	{
		sstream >> goods_price_change;
		sstream >> goods_owner;
		sstream >> goods_quantity;
		sstream >> status;

		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			goods_name = buff_in;
		}
		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			goods_description = buff_in;
		}
		if (goods_type == 0)
			type = "Food";
		else if (goods_type == 1)
			type = "Clothes";
		else if (goods_type == 2)
			type = "Book";
		cout << i << ")" << type << ":" << goods_name << endl;
		cout << "The description:         " << goods_description << endl;
		cout << "The current price:       " << goods_price_change << endl;
		cout << "The owner of goods:      " << goods_owner << endl;
		cout << "The quantity:            " << goods_quantity << endl;
		if (status == 0)
			cout << "No order has been generated." << endl;
		else if (status == 1)
			cout << "The order has been generated." << endl;
		cout << "****************************************" << endl;
		i++;
		//接收下一个
		client::send_ACK();
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			ss = buff_in;
			sstream << ss;
			sstream >> goods_type;
		}
	}
}

int cart_func::add_cart()
{
	stringstream sstream;
	string ss;
	int m, flag, r;
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int status = 0;
	flag = 1;
	string goods_kind;
	int goods_type = 0;
	//首先接收服务器的数据，判断是否登录
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)
	{
		cout << "Sorry, you haven't sign in, please sign in first." << endl;
		return -1;
	}
	//发送ACK
	client::send_ACK();

	//接收数据，判单是否有订单未支付
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 1)
	{
		cout << "Sorry, you have a order wait for paying. Please pay for it first." << endl;
		return 2;
	}
	//展示所有的商品
	goods_func::goods_init_interface();
	//发送信息，是否需要名称查询
	int num = 4;//最多5次
	cout << "Do you want to quire a goods?" << endl;
	cout << "'yes' or 'no'" << endl;
	string choose;
	user_func::get_string(choose);
	while (choose != "yes" && choose != "no")
	{
		cout << "Please input 'yes' or 'no':" << endl;
		cin.sync();
		user_func::get_string(choose);
	}
	if (choose == "yes")
	{
		sstream.str("");
		sstream.clear();
		sstream << 1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
		//进入函数内部
		r = goods_func::goods_name_interface();
		while (r == 0 && num > 0)//没有找到
		{
			cout << "Please check your input." << endl;
			r = goods_func::goods_name_interface();
			num--;
		}
	}
	else
	{
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
	}
	r = 1;
	while (r)
	{
		//输入商品类别，商品所有者，商品名称，传给服务器
		//输入想要购买的商品类型
		cout << "Please input the type of goods you want to buy:" << endl;
		cout << "'food','clothes','book'" << endl;
		cin.sync(); //清除缓冲区的数据流
		user_func::get_string(goods_kind);
		while ((goods_kind != "food" && goods_kind != "clothes" && goods_kind != "book") || cin.fail())
		{
			if (cin.fail())
			{
				cin.clear(); //更改cin的状态标识符
				cin.sync();  //清除缓冲区的数据流
			}
			cout << "Wrong kind, please input 'food' or 'clothes' or 'book', or '#' to quit:" << endl;
			cin.sync(); //清除缓冲区的数据流
			user_func::get_string(goods_kind);
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
		//下面用户选择商品的名称和所有者，来定位想要购买的商品，但要求是这一类的商品

		cout << "Which goods do you want to buy? Please input the goods's name:" << endl;
		cin.sync();
		getline(cin, goods_name);
		cout << "Please input the owner of this goods:" << endl;
		cin.sync();
		user_func::get_string(goods_owner);

		//先发送商品类别和商品所有者
		sstream.str("");
		sstream.clear();
		sstream << goods_type << " " << goods_owner;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
		//接收ack
		client::reve_ACK();
		//然后发送商品的名称
		sstream.str("");
		sstream.clear();
		sstream << goods_name;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);

		//接收服务器数据，没有找到商品，-1；找到商品，剩余量
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			ss = buff_in;
			sstream << ss;
			sstream >> flag;
		}
		if (flag == -1)
		{
			cout << "goods not exist." << endl;
			cout << "'check' or 'quit'?" << endl;
			string temp;
			cin.sync(); //清除缓冲区的数据流
			user_func::get_string(temp);
			while (temp != "quit" && temp != "check")
			{
				cout << "'check' or 'quit':" << endl;
				cin.sync(); //清除缓冲区的数据流
				user_func::get_string(temp);
			}
			if (temp == "quit")
			{
				//传过去0
				sstream.str("");
				sstream.clear();
				sstream << 0;
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket, buff_out, strlen(buff_out), NULL);
				return 0;
			}
			else
			{
				//传过去1
				sstream.str("");
				sstream.clear();
				sstream << 1;
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket, buff_out, strlen(buff_out), NULL);
			}

		}
		else//找到商品，剩余量
		{
			r = 0;
			//现在flag是剩余量
			cout << "Please input the quantity you want to buy:" << endl;
			cin.sync();
			user_func::get_int(goods_quantity);
			while (goods_quantity <= 0)
			{
				cout << "Sorry, please input a positive interger number:" << endl;
				cin.sync();
				user_func::get_int(goods_quantity);
			}
			//发送购买数量
			sstream.str("");
			sstream.clear();
			sstream << goods_quantity;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket, buff_out, strlen(buff_out), NULL);
			//接收信号，看是不是已经在购物车里面了
			sstream.str("");
			sstream.clear();
			int exist;
			m = recv(clientSocket2, buff_in, 1023, NULL);
			if (m > 0) {
				buff_in[m] = 0;
				//cout << "来自服务器的消息:" << buff_in << endl;
				ss = buff_in;
				sstream << ss;
				sstream >> exist;
			}
			if (exist == -1)//是一个新商品
			{
				cout << "Add successfully!" << endl;
				return 1;
			}
			else
			{
				cout << "The goods has existed, now add the quantity." << endl;
				cout << "Add successfully!" << endl;
				return 1;
			}
		}
	}

}

int cart_func::change_cart()
{
	stringstream sstream;
	string ss;
	int m, flag, r;
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int status = 0;
	flag = 1;
	string goods_kind;
	int goods_type = 0;
	//首先接收服务器的数据，判断是否登录
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)
	{
		cout << "Sorry, you haven't sign in, please sign in first." << endl;
		return -1;
	}
	cout << "****************************************" << endl;
	cout << "Now begin to change your cart information." << endl;
	cout << "****************************************" << endl;
	//发送ACK
	client::send_ACK();
	//接送购物车信息并展示
	string cart_owner = all_consumer.get_user_name();
	show_cart(cart_owner);
	//发送ACK
	client::send_ACK();
	//接收数据，判单是否有订单未支付
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 1)
	{
		cout << "Sorry, you have a order wait for paying. Please pay for it first." << endl;
		return 2;
	}
	r = 1;
	while (r)
	{
		//发送要修改的类别，商家和商品名称
		cout << "Please choose the goods you want to change?" << endl;

		cout << "Please input the type of goods(0 food,1 clothes,2 book):" << endl;
		cin.sync(); //清除缓冲区的数据流
		user_func::get_int(goods_type);
		cout << "Please input the name of goods:" << endl;
		cin.sync(); //清除缓冲区的数据流
		getline(cin, goods_name);
		cout << "Please input the owner of goods?" << endl;
		cin.sync();
		user_func::get_string(goods_owner);

		sstream.str("");
		sstream.clear();
		sstream << goods_type << " " << goods_owner;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);

		client::reve_ACK();

		sstream.str("");
		sstream.clear();
		sstream << goods_name;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);

		//接收服务器数据，在购物车中没有找到商品，-1；找到商品，1
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的消息:" << buff_in << endl;
			ss = buff_in;
			sstream << ss;
			sstream >> flag;
		}

		if (flag == -1)//没有找到
		{
			cout << "Sorry, the goods is not found, please check your input:" << endl;
		}

		else//找到了
		{
			r = 0;
			int id;
			cout << "What kind of operation do you want to do?" << endl;
			cout << "1:Change quantity." << endl;
			cout << "2:Delete this goods." << endl;
			cout << "0:Quit." << endl;
			cin.sync();
			user_func::get_int(id);
			while ((id != 0 && id != 1 && id != 2) || cin.fail())
			{
				if (cin.fail())
				{
					cin.clear();
					cin.sync();
				}
				cout << "Wrong id, please input 0 or 1 or 2:" << endl;
				cin.sync(); //清除缓冲区的数据流
				user_func::get_int(id);
			}
			//传给服务器要进行的动作
			sstream.str("");
			sstream.clear();
			sstream << id;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket, buff_out, strlen(buff_out), NULL);
			//收到ack
			client::reve_ACK();

			if (id == 0)
				return 1;
			else if (id == 1)
			{
				cout << "Please input the quantity you want to buy:" << endl;
				cin.sync();
				user_func::get_int(goods_quantity);
				while (goods_quantity <= 0)
				{
					cout << "Sorry, please input a positive interger number:" << endl;
					cin.sync();
					user_func::get_int(goods_quantity);
				}
				//发送到服务器
				sstream.str("");
				sstream.clear();
				sstream << goods_quantity;
				strcpy(buff_out, (sstream.str()).c_str());
				send(clientSocket, buff_out, strlen(buff_out), NULL);
				cout << "Change quantity successfully!" << endl;
				return 1;
			}
			else
			{
				cout << "Delete successfully! Now quit." << endl;
				return 1;
			}
		}
	}

}

int cart_func::generate_order()
{
	stringstream sstream;
	string ss;
	int m, flag, r;
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int status = 0;
	flag = 1;
	string goods_kind;
	int goods_type = 0;
	//首先接收服务器的数据，判断是否登录
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)
	{
		cout << "Sorry, you haven't sign in, please sign in first." << endl;
		return -1;
	}
	//发送ACK
	client::send_ACK();
	//接送购物车信息并展示
	string cart_owner = all_consumer.get_user_name();
	show_cart(cart_owner);

	//发送信息，确定是否生成购物车
	cout << "Sure to generate your order?" << endl;
	cout << "'yes' or 'no':" << endl;
	string answer;
	cin.sync();
	user_func::get_string(answer);
	while (answer != "yes" && answer != "no")
	{
		cout << "Please input 'yes' or 'no':" << endl;
		cin.sync();
		user_func::get_string(answer);
	}
	if (answer == "no")
	{
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
		cout << "Cancel successfully." << endl;
		return 0;
	}
	else
	{
		sstream.str("");
		sstream.clear();
		sstream << 1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
	}
	cout << "For any goods, if the quantity you want is over the surplus, we change the quantity to the surplus." << endl;
	//接收服务器的信号
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 1)
	{
		cout << "All the goods has been generated." << endl;
		return 1;
	}
	else
	{
		cout << "All the goods has been generated before." << endl;
		return 0;
	}
}

int cart_func::pay_or_cancel_order()
{
	stringstream sstream;
	string ss;
	int m, flag, r;
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int status = 0;
	flag = 1;
	string goods_kind;
	int goods_type = 0;
	//首先接收服务器的数据，判断是否登录
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)
	{
		cout << "Sorry, you haven't sign in, please sign in first." << endl;
		return -1;
	}
	//发送ACK
	client::send_ACK();
	//接送购物车信息并展示
	//string cart_owner = all_consumer.get_user_name();
	//show_cart(cart_owner);

	//接收服务器信息，检查订单是否已经生成，生成了传1，未生成传0，购物车就没有的传-1
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)
	{
		cout << "Sorry, you haven't generate an order." << endl;
		return 0;
	}
	else if (flag == -1)
	{
		cout << "Sorry, you haven't add anything to your cart." << endl;
		return 0;
	}
	//订单已经生成
	//询问客户是否想要删除订单
	cout << "Do you want to cancel this order?" << endl;
	cout << "Please input 'yes' or 'no':" << endl;
	string confirm;
	cin.sync(); //清除缓冲区的数据流
	user_func::get_string(confirm);
	while (confirm != "yes" && confirm != "no")
	{
		cout << "Please input 'yes' or 'no':" << endl;
		cin.sync(); //清除缓冲区的数据流
		user_func::get_string(confirm);
	}
	if (confirm == "yes")
	{
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
		cout << "Cancel succeddfully!" << endl;
		return 0;
	}
	else
	{
		sstream.str("");
		sstream.clear();
		sstream << 1;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket, buff_out, strlen(buff_out), NULL);
	}
	//选择不删除的话就支付
	//先接收总共的价格
	sstream.str("");
	sstream.clear();
	double price = 0.0;
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的price消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> price;
	}
	cout << "The total price is: " << price << endl;

	//发送ack
	client::send_ACK();
	//接收服务器的信号，看余额是否够用
	sstream.str("");
	sstream.clear();
	m = recv(clientSocket2, buff_in, 1023, NULL);
	if (m > 0) {
		buff_in[m] = 0;
		//cout << "来自服务器的余额消息:" << buff_in << endl;
		ss = buff_in;
		sstream << ss;
		sstream >> flag;
	}
	double balance;
	if (flag == 1)
	{
		cout << "Sorry, your balance is not enough. Please recharge." << endl;
		return 2;
	}

	else
	{
		cout << "Pay successfully!" << endl;
		//接收服务器传来的余额
		sstream.str("");
		sstream.clear();
		m = recv(clientSocket2, buff_in, 1023, NULL);
		if (m > 0) {
			buff_in[m] = 0;
			//cout << "来自服务器的余额消息:" << buff_in << endl;
			ss = buff_in;
			sstream << ss;
			sstream >> balance;
			all_consumer.set_user_balance(balance);
		}
		return 1;
	}
}