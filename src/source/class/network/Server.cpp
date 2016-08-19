#include "class/network/Server.h"
#include "class/tim/thread/Thread.h"
#include "class/network/ServerTask.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <iostream>
namespace game {
namespace network{
Server::Server() {
	server_start=false;
	server_end=false;
}
Server::~Server() {

}
void Server::server_active(){
	std::string local_addr=Socket::get_local_address();
	std::cout<<"local_addr="<<local_addr<<std::endl;


	Socket *socket=new Socket();//Socket::get_local_address()
	socket->set_address(local_addr,1125);//local_addr
	//socket->addr.sin_addr.s_addr=INADDR_ANY;

	socket->socket_bind();
	socket->socket_listen();

	while(!server_end){
		SOCKADDR_IN clinetAddr;
		if (Socket* sConnect=socket->accept_connect(&clinetAddr)) {
			bool end=false;
			while(!end){
				std::string str;
				//std::cout<<"input str:"<<std::endl;
				//std::cin>>str;

				do{
					str=get_sent_data();
				}while(str==""&&!server_end);
				if(!server_end){
					std::cout<<"input str="<<str<<std::endl;
					sConnect->sent_data(str);
					std::string  receive_str=sConnect->receive_data();
					push_receive_data(receive_str);
					if(receive_str=="#end"){
						end=true;
					}
				}else{
					end=true;
				}

			}
			delete sConnect;
		}
	}
	std::cout<<"Server::server_active() end"<<std::endl;
	delete socket;
	server_start=false;
}
void Server::sent_data(std::string str){
	sent_mutex.wait_for_this();
	sent_q.push(str);
	sent_mutex.release();
}
std::string Server::get_sent_data(){
	sent_mutex.wait_for_this();
	std::string str;
	if(!sent_q.empty()){
		str=sent_q.front();
		sent_q.pop();
	}
	sent_mutex.release();
	return str;
}
std::string Server::receive_data(){
	receive_mutex.wait_for_this();
	std::string str;
	if(!receive_q.empty()){
		str=receive_q.front();
		receive_q.pop();
	}

	receive_mutex.release();
	return str;
}
void Server::push_receive_data(std::string str){
	receive_mutex.wait_for_this();
	receive_q.push(str);
	receive_mutex.release();
}
void Server::start(){
	server_start=true;

	std::string server_addr=Socket::get_external_address();
	std::cout<<"addr="<<server_addr<<std::endl;

	Tim::Thread *thread=new Tim::Thread(NORMAL_PRIORITY_CLASS,0,true);
	thread->push_task(new ServerTask(this));
	thread->start();
	//pool->Terminate();
}
void Server::end(){
	server_end=true;
	while(server_start);
}
}
} /* namespace game */
