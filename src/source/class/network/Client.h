#ifndef SOURCE_CLASS_NETWORK_CLIENT_H_
#define SOURCE_CLASS_NETWORK_CLIENT_H_
#include "class/network/Socket.h"
#include "class/tim/thread/mutex/Mutex.h"
#include <queue>
namespace game {
namespace network{
class ClientTask;


class Client {
	friend ClientTask;
public:
	Client();
	virtual ~Client();

	void start();
	void end();

	void sent_data(std::string str);
	std::string receive_data();
	void set_ip(std::string ip);

	bool client_start;
	std::string ip;
protected:
	void client_active();

	std::string get_sent_data();
	void push_receive_data(std::string str);

	Tim::Mutex sent_mutex;
	Tim::Mutex receive_mutex;
	std::queue<std::string> sent_q;
	std::queue<std::string> receive_q;
	bool client_end;
};
}
} /* namespace game */

#endif /* SOURCE_CLASS_NETWORK_CLIENT_H_ */
