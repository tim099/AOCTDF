#ifndef SOURCE_CLASS_NETWORK_SERVER_H_
#define SOURCE_CLASS_NETWORK_SERVER_H_
#include "class/network/Socket.h"
#include "class/tim/thread/mutex/Mutex.h"
#include <queue>
namespace game {
namespace network{
class ServerTask;


class Server {
	friend ServerTask;
public:
	Server();
	virtual ~Server();

	void start();
	void end();
	void sent_data(std::string str);
	bool client_connected();
	bool get_new_connection(){
		if(new_connection){
			new_connection=false;
			return true;
		}
		return false;
	}
	std::string receive_data();

	bool server_start;

	std::string local_addr;
	std::string server_addr;
protected:
	void server_active();

	void push_receive_data(std::string str);

	Tim::Mutex receive_mutex;
	Tim::Mutex connect_mutex;
	Tim::Mutex socket_mutex;
	std::queue<std::string> sent_q;
	std::queue<std::string> receive_q;
	bool new_connection;


	Socket *sConnect;
	Socket *socket;
	bool server_end;
};
}
} /* namespace game */

#endif /* SOURCE_CLASS_NETWORK_SERVER_H_ */
