#include "class/network/Socket.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <wininet.h>
//#pragma comment(lib,"wininet")
namespace game {
namespace network{
bool Socket::init=false;
WSAData Socket::wsaData;
void Socket::socket_init(){
	if(init)return;

	WSAStartup(MAKEWORD(2,1),&wsaData);
	init=true;
}
void Socket::socket_exit(){
	init=false;
	WSACleanup();
}
Socket::Socket(int af,int type,int protocol) {
    socket_handle=socket(af,type,protocol);
    if(socket_handle==INVALID_SOCKET){
    	std::cerr<<"socket failed with error:"<<WSAGetLastError()<<std::endl;
	}
    //set_address(_address);
}
Socket::Socket(SOCKET _socket_handle){
	socket_handle=_socket_handle;
}
Socket::~Socket() {
	sock_close();
	//WSACleanup();
}
void Socket::sock_close(){
	if(socket_handle){
		closesocket(socket_handle);
		socket_handle=0;
	}
}
void Socket::sock_shutdown(int how){
	shutdown(socket_handle,how);
}

std::string Socket::get_external_address(){
	HINTERNET hInternet, hFile;
	DWORD rSize;
	char buffer[100];

	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	hFile = InternetOpenUrl(hInternet,
			"https://api.ipify.org?format=json",
			NULL,0,INTERNET_FLAG_RELOAD,0);
	InternetReadFile(hFile,&buffer,sizeof(buffer),&rSize);
	for(unsigned i=0;i<rSize-9;i++){
		buffer[i]=buffer[i+7];
	}
	//memcpy(buffer+7,buffer,rSize-9);
	buffer[rSize-9]='\0';
	InternetCloseHandle(hFile);
	InternetCloseHandle(hInternet);

	return std::string(buffer);
}
std::string Socket::get_local_address(){
	char szHostName[255];
	gethostname(szHostName,255);
	struct hostent* hos=gethostbyname(szHostName);
	char *str_buff=inet_ntoa(*(struct in_addr*)*hos->h_addr_list);
	std::string addr(str_buff);
	//delete str_buff;
	return addr;
}
void Socket::set_address(std::string _address,int port){
	address=_address;//"127.0.0.1"
    addr.sin_addr.s_addr=inet_addr(address.c_str());
    addr.sin_family=IPv4;

    addr.sin_port=htons(port);
}
void Socket::socket_bind(){
	bind(socket_handle,(SOCKADDR*)&addr,sizeof(addr));
	//std::cout<<"address="<<inet_ntoa(addr.sin_addr)<<std::endl;
}
void Socket::socket_listen(int backlog){
	int r=listen(socket_handle,backlog);	    //SOMAXCONN: listening without any limit
	if(r==SOCKET_ERROR){
		std::cout<<"Socket::socket_listen error!!"<<std::endl;
	}
}
Socket* Socket::accept_connect(SOCKADDR_IN *clinetAddr){
	int addrlen = sizeof(addr);
	SOCKET soc=accept(socket_handle,(SOCKADDR*)clinetAddr,&addrlen);
	if(soc){
		return new Socket(soc);
	}else{
		std::cerr<<"Socket::accept_connect failed with error:"<<WSAGetLastError()<<std::endl;
	}
	return 0;
}
void Socket::sent_data(std::string str){
	send(socket_handle,str.c_str(),str.length(),0);
}
void Socket::sent_data(char* data,unsigned len){
	send(socket_handle,data,len,0);
}
void Socket::unblock_mode(){
	unsigned long int val=1;
	ioctlsocket(1,socket_handle,&val);
}
std::string Socket::receive_data(){
	char message[buffer_len];
	memset(message,0,buffer_len);
	recv(socket_handle, message, sizeof(message),0);//int n=
	return std::string(message);
}
bool Socket::connect_server(){
	if(connect(socket_handle,(SOCKADDR*)&addr,sizeof(addr))){//connect fail
		std::cerr<<"Socket::connect_server failed with error:"<<WSAGetLastError()<<std::endl;
		return false;
	}
	return true;
}
}
} /* namespace socket */
