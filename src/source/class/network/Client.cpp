#include "class/network/Client.h"
#include "class/network/ClientTask.h"
#include "class/tim/thread/Thread.h"
#include <iostream>
namespace game {
namespace network{
Client::Client() {
	client_start=false;
	client_end=false;
	ip="127.0.0.1";
}
Client::~Client() {

}
void Client::set_ip(std::string _ip){
	ip=_ip;
}
void Client::sent_data(std::string str){
	sent_mutex.wait_for_this();
	sent_q.push(str);
	sent_mutex.release();
}
std::string Client::get_sent_data(){
	sent_mutex.wait_for_this();
	std::string str;
	if(!sent_q.empty()){
		str=sent_q.front();
		sent_q.pop();
	}
	sent_mutex.release();
	return str;
}
std::string Client::receive_data(){
	receive_mutex.wait_for_this();
	std::string str;
	if(!receive_q.empty()){
		str=receive_q.front();
		receive_q.pop();
	}

	receive_mutex.release();
	return str;
}
void Client::push_receive_data(std::string str){
	receive_mutex.wait_for_this();
	receive_q.push(str);
	receive_mutex.release();
}
void Client::client_active(){
	Socket *socket=new Socket();

	socket->set_address(ip,1125);
	socket->connect_server();//server_addr

	while(!client_end){
	    std::string receive_dat=socket->receive_data();
		push_receive_data(receive_dat);

		std::string str;
		do{
			str=get_sent_data();
		}while(str==""&&!client_end);

		socket->sent_data(str);

	}

	delete socket;
	client_start=false;
}
void Client::start(){
	client_start=true;

	Tim::Thread *thread=new Tim::Thread(NORMAL_PRIORITY_CLASS,0,true);
	thread->push_task(new ClientTask(this));
	thread->start();
}
void Client::end(){
	client_end=true;
	while(client_start);
}

}
} /* namespace game */
