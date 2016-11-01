#ifndef SOURCE_CLASS_NETWORK_SOCKET_H_
#define SOURCE_CLASS_NETWORK_SOCKET_H_



#include <winsock2.h>
//#include <ws2tcpip.h>
#include <string>
#define WIN32_LEAN_AND_MEAN

//#define _WIN32_WINNT 0x501
namespace game {
namespace network{
class Socket {
	static bool init;
	static WSAData wsaData;
	static const int type_TCP=SOCK_STREAM;
	static const int type_UDP=SOCK_DGRAM;
	static const int IPv4=AF_INET;
	static const int IPv6=AF_INET6;
	static const int protocol_TCP=IPPROTO_TCP;
	static const int protocol_UDP=IPPROTO_UDP;
public:
	static const  int buffer_len=1024;
	static void socket_init();
	static void socket_exit();
	Socket(int af=IPv4,int type=type_TCP,int protocol=protocol_TCP);
	Socket(SOCKET socket_handle);
	virtual ~Socket();


	void set_address(std::string address="127.0.0.1",int port=1234);

	void unblock_mode();
	void socket_bind();
	void socket_listen(int backlog=SOMAXCONN);

	void sent_data(std::string str);
	void sent_data(char* data,unsigned len);
	bool connect_server();
	void sock_shutdown(int how);
	void sock_close();
	Socket* accept_connect(SOCKADDR_IN *clinetAddr);

	static std::string get_local_address();
	static std::string get_external_address();
	std::string receive_data();

	std::string address;

	SOCKADDR_IN addr;
	SOCKET socket_handle;
};
}
} /* namespace socket */

#endif /* SOURCE_CLASS_NETWORK_SOCKET_H_ */
