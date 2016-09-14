#include "class/network/Server.h"
#include "class/tim/thread/Thread.h"
#include "class/network/ServerTask.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <iostream>
namespace game {
namespace network{
Server::Server() {
	sConnect=0;
	server_start=false;
	server_end=false;
	new_connection=false;
	socket=0;
}
Server::~Server() {

}
bool Server::client_connected(){
	if(sConnect)return true;
	return false;
}
void Server::server_active(){
	server_addr=Socket::get_external_address();
	std::cout<<"addr="<<server_addr<<std::endl;
	local_addr=Socket::get_local_address();
	std::cout<<"local_addr="<<local_addr<<std::endl;
	socket_mutex.wait_for_this();
	socket=new Socket();//Socket::get_local_address()
	socket->set_address(local_addr,1125);//local_addr
	//socket->addr.sin_addr.s_addr=INADDR_ANY;

	socket->socket_bind();
	socket->socket_listen();
	socket_mutex.release();
	while(!server_end){
		SOCKADDR_IN clinetAddr;

		connect_mutex.wait_for_this();
		sConnect=socket->accept_connect(&clinetAddr);
		connect_mutex.release();

		if (sConnect) {
			new_connection=true;
			bool end=false;
			while(!end&&!server_end){
				std::string  receive_str=sConnect->receive_data();
				push_receive_data(receive_str);
				if(receive_str=="#end"){
					end=true;
				}
			}
			connect_mutex.wait_for_this();

			delete sConnect;
			sConnect=0;
			new_connection=false;

			connect_mutex.release();

		}
	}
	std::cout<<"Server::server_active() end"<<std::endl;
	socket_mutex.wait_for_this();
	delete socket;
	socket=0;
	socket_mutex.release();
	server_start=false;
}
void Server::sent_data(std::string str){
	if(sConnect){
		sConnect->sent_data(str);
	}
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

	Tim::Thread *thread=new Tim::Thread(IDLE_PRIORITY_CLASS,0,true);
	thread->push_task(new ServerTask(this));
	thread->start();
	//pool->Terminate();
}
void Server::end(){
	server_end=true;
	if(socket){
		socket->sock_close();
	}

	connect_mutex.wait_for_this();
	if(sConnect){
		sConnect->sock_close();
	}
	connect_mutex.release();
	while(server_start);
}
}
} /* namespace game */
