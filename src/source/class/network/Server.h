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

	std::string receive_data();

	bool server_start;

protected:
	void server_active();

	std::string get_sent_data();
	void push_receive_data(std::string str);

	Tim::Mutex sent_mutex;
	Tim::Mutex receive_mutex;
	std::queue<std::string> sent_q;
	std::queue<std::string> receive_q;
	bool server_end;
};
}
} /* namespace game */

#endif /* SOURCE_CLASS_NETWORK_SERVER_H_ */
