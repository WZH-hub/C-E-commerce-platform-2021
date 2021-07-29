#include "cart_func.h"
#include <iostream>

int cart_func::add_cart()
{
	stringstream sstream;
	string ss;
	int r;
	if (all_consumer.get_user_type() != 2)
	{
		//����0����ʾδ��¼
		sstream.str("");
		sstream.clear();
		sstream << 0;
		//strcpy(buff_out, (sstream.str()).c_str());
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//����1����ʾ��¼
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	string cart_owner = all_consumer.get_user_name();
	//���շ�����ack
	server::reve_ACK();
	//������������Ҫ�ȼ���Ƿ��ж���δ֧�����еĻ�����ȥ1��û�еĻ�����ȥ0
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

	//���û�ж���δ֧��
	//��ʱ�Զ���ͻ��˷������е���Ʒ
	goods_func::goods_init_interface();
	int choose = 0;//0Ϊ����Ҫ��1Ϊ��Ҫ
	//��ʱ���տͻ��˵���Ϣ���Ƿ�������Ʋ�ѯ�Լ���Ҫ��ѯ����Ʒ
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
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
		//����������ڲ�����������Կͻ��˵����ݣ����������ݷ���
		r = goods_func::goods_name_interface();
		if (r == 1)//��ʾ�ҵ���
			choose = 0;
		//�����޶��������5�Σ�Ȼ��᲻����������
		else
			num--;
	}
	//�������Կͻ��˵���Ʒ��Ϣ���ж���Ʒ���ں�ȷ����������
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
			cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
			ss = buff_in;
			sstream.str("");
			sstream.clear();
			//˳��Ӧ������Ʒ�����Ʒ������
			sstream << ss;
			sstream >> goods_type;
			sstream >> goods_owner;
		}
		//��һ��ack
		server::send_ACK();
		//Ȼ�������Ʒ������
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
			goods_name = buff_in;
		}
		//���������Ʒ�Ƿ���Ĵ���
		goods* tmp = server::check_goods_exist(goods_type, goods_name, goods_owner);
		if (tmp == NULL)//û���ҵ���Ʒ������ȥ-1
		{
			cout << "goods not exist" << endl;
			sstream.str("");
			sstream.clear();
			sstream << -1;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);

			//Ȼ����տͻ����Ƿ����Ѱ����Ʒ���źţ�0��ʾ�˳���1Ϊ����
			r = recv(clientSocket, buff_in, 1023, NULL);
			if (r > 0) {
				buff_in[r] = 0;
				cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
				ss = buff_in;
				sstream.str("");
				sstream.clear();
				if (ss == "0")//��ʾ�˳�
					return 0;
			}
		}

		else//�ҵ���Ʒ������ȥʣ����
		{
			goods_surplus = tmp->get_goods_surplus();
			cout << "goods exist" << endl;
			sstream.str("");
			sstream.clear();
			sstream << goods_surplus;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);


			//Ȼ�����Ҫ���������
			r = recv(clientSocket, buff_in, 1023, NULL);
			if (r > 0) {
				buff_in[r] = 0;
				cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
				ss = buff_in;
				sstream.str("");
				sstream.clear();
				sstream << ss;
				sstream >> goods_quantity;
				//system("pause");
			}
			//��Ҫ�ж�һ����Ʒ�ǲ����Ѿ������ڹ��ﳵ��
			cart* m = server::check_cart_exist(goods_type, goods_name, goods_owner, cart_owner);
			if (m == NULL)//��һ���µ���Ʒ
			{
				//����ȥ-1�������Ʒ
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
				//����ȥ1���޸���Ʒ������
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
			return 1;//��ӳɹ����ͻ����ڴ��͹������Զ���ʾ��ӳɹ�
			//������ѭ��������
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
		//����0����ʾδ��¼
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//����1����ʾ��¼
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	string cart_owner = all_consumer.get_user_name();
	server::reve_ACK();
	//����ȥ���ﳵ����Ϣ
	show_cart(cart_owner);
	server::reve_ACK();
	//������������Ҫ�ȼ���Ƿ��ж���δ֧�����еĻ�����ȥ1��û�еĻ�����ȥ0
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

	//���û�ж���δ֧��
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int goods_type;
	int flag = 1;
	//�ӿͻ��˽���Ҫ�޸ĵĹ��ﳵ����Ϣ
	//˳��Ϊ��Ʒ�����Ʒ������
	//Ȼ������Ʒ����
	while (flag)
	{
		r = recv(clientSocket, buff_in, 1023, NULL);
		if (r > 0) {
			buff_in[r] = 0;
			cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
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
			cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
			ss = buff_in;
			sstream.str("");
			sstream.clear();
			sstream << ss;
			sstream >> goods_name;
		}
		//�ж������Ϣ�ǲ�������ڹ��ﳵ��
		cart* m = server::check_cart_exist(goods_type, goods_name, goods_owner, cart_owner);
		if (m == NULL)//����ȥ-1��ʾû�ҵ�
		{
			cout << "not found" << endl;
			sstream.str("");
			sstream.clear();
			sstream << -1;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			//��Ҫ�ٴδ�����
		}
		else//����ȥ1��ʾ�ҵ���
		{
			flag = 0;
			cout << "found" << endl;
			sstream.str("");
			sstream.clear();
			sstream << 1;
			strcpy(buff_out, (sstream.str()).c_str());
			send(clientSocket2, buff_out, strlen(buff_out), NULL);
			//����ѯ�ʿͻ�����Ҫ�Ĳ�����1:Change quantity.2:Delete this goods.0:Quit.
			int id = 0;
			r = recv(clientSocket, buff_in, 1023, NULL);
			if (r > 0) {
				buff_in[r] = 0;
				cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
				ss = buff_in;
				sstream.str("");
				sstream.clear();
				sstream << ss;
				sstream >> id;
			}
			//����ack
			server::send_ACK();

			if (id == 0)//�˳�
			{
				cout << "quit" << endl;
				return 1;
			}
			else if (id == 1)
			{
				//�ӿͻ��˽����µĹ�������
				r = recv(clientSocket, buff_in, 1023, NULL);
				if (r > 0) {
					buff_in[r] = 0;
					cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
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
				//�ӹ��ﳵ��ɾ��
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

void cart_func::show_cart(string owner)//������˵Ĺ��ﳵ��Ϣ����ȥ��ָ�����NULL����
{
	stringstream sstream;
	string ss;
	string goods_name;
	string goods_owner;
	int goods_quantity;
	int goods_type;
	int status = 0;
	int flag = 1;

	//����ȥ��˳��Ϊ����Ʒ�����Ʒ�ּۣ���Ʒ�����ߣ���Ʒ���������Ƿ��Ѿ����ɶ���
	//��Ʒ�����ƣ���Ʒ������
	//����ȥ-1��ʾ����
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
		//����0����ʾδ��¼
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//����1����ʾ��¼
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	server::reve_ACK();

	string cart_owner = all_consumer.get_user_name();
	//����ȥ���ﳵ����Ϣ
	show_cart(cart_owner);
	//�������ݣ��鿴�������Ƿ�ȷ��Ҫ���ɶ���
	int flag = 1;
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
		ss = buff_in;
		sstream.str("");
		sstream.clear();
		sstream << ss;
		sstream >> flag;
	}
	if (flag == 0)//��������
	{
		cout << "Cancel successfully." << endl;
		return 0;
	}
	//ȷ��Ҫ����
	flag = 0;
	//����û����ﳵ��ÿһ�����Ʒ���������Ƿ񳬹����̼�Ŀǰ��ʣ����
	//��������֪�ˣ�ֱ���ڿͻ��˸����û������ǽ����й���������ļ�С��ʣ������
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
			//��Ʒʣ��������
			temp->get_cart_want()->set_goods_surplus(temp->get_cart_want()->get_goods_surplus() - temp->get_cart_quantity());
		}
	}
	if (flag == 1)
	{
		//����1��ʾ�ɹ����ɶ���
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
		//����-1��ʾ����֮ǰ�Ѿ����ɶ���
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
		//����0����ʾδ��¼
		sstream.str("");
		sstream.clear();
		sstream << 0;
		strcpy(buff_out, (sstream.str()).c_str());
		send(clientSocket2, buff_out, strlen(buff_out), NULL);
		return -1;
	}
	//����1����ʾ��¼
	sstream.str("");
	sstream.clear();
	sstream << 1;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	server::reve_ACK();
	string cart_owner = all_consumer.get_user_name();
	//�����鶩���Ƿ��Ѿ����ɣ������˴�1��δ���ɴ�0�����ﳵ��û�еĴ�-1
	for (cart* temp : v_cart)
	{
		if (temp->get_cart_owner() == cart_owner) //�ҵ�
		{
			flag = 1;
			if (temp->cart_status == 0) //��δ���ɶ���
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
	//�ͻ��˷�����Ϣ��1��ʾ��ɾ��������0��ʾɾ������
	r = recv(clientSocket, buff_in, 1023, NULL);
	if (r > 0) {
		buff_in[r] = 0;
		cout << "���Կͻ��˵���Ϣ:" << buff_in << endl;
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
	//�����ɾ��������֧��
	double all_money = 0.0;
	for (cart* temp : v_cart)
	{
		//��ȡ�ܹ��ļ۸�
		if (temp->get_cart_owner() == cart_owner)
		{
			all_money = all_money + temp->get_cart_want()->get_goods_price_change() * temp->get_cart_quantity(); //ע�⣡�������ܱ�֤��ȷ���ȴ�����
		}
	}
	//���ܹ��ļ۸񴫻�ȥ
	sstream.str("");
	sstream.clear();
	sstream << all_money;
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);
	//����ack
	server::reve_ACK();
	//�ж�һ���Ƿ񳬹����û������
	if (all_money > all_consumer.get_user_balance())
	{
		cout << "Sorry, your balance is not enough. Please recharge." << endl;
		//����1��ʾ�����ˣ�0��ʾû����
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
	//��ɲ������̼���Ǯ�������߿�Ǯ�����ﳵ���
	string business_owner;
	for (cart* temp : v_cart)
	{
		if (temp->get_cart_owner() == cart_owner) //�ҵ����ﳵ
		{
			business_owner = temp->get_cart_want()->get_goods_owner();
			for (user* tmp : v_user) //�ҵ��̼�
			{
				if (tmp->get_user_name() == business_owner)
				{
					double temp_money = temp->get_cart_want()->get_goods_price_change() * temp->get_cart_quantity();

					tmp->set_user_balance(tmp->get_user_balance() + temp_money); //�̼���Ǯ
				}
			}
		}
	}
	//ɾ�����ﳵ
	for (vector<cart*>::iterator it = v_cart.begin(); it != v_cart.end();)
	{
		if ((*it)->get_cart_owner() == cart_owner)
			it = v_cart.erase(it);
		else
			++it;
	}
	//��ǮҪ�������ط���all_consumer��v_user
	all_consumer.set_user_balance(all_consumer.get_user_balance() - all_money);
	for (user* temp : v_user)
	{
		if (temp->get_user_name() == all_consumer.get_user_name())
		{
			temp->set_user_balance(temp->get_user_balance() - all_money);
		}
	}
	cout << "Pay successfully!" << endl;
	//����ȥ���
	sstream.str("");
	sstream.clear();
	sstream << all_consumer.get_user_balance();
	strcpy(buff_out, (sstream.str()).c_str());
	send(clientSocket2, buff_out, strlen(buff_out), NULL);

	return 1;
}