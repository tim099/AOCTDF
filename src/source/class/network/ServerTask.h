#ifndef SOURCE_CLASS_NETWORK_SERVERTASK_H_
#define SOURCE_CLASS_NETWORK_SERVERTASK_H_
#include "class/tim/thread/task/Task.h"
namespace game {
namespace network {
class Server;
class ServerTask : public Tim::Task {
public:
	ServerTask(Server* server);
	virtual ~ServerTask();
protected:
	virtual void ExecuteTask();
	Server* server;
};

} /* namespace network */
} /* namespace game */

#endif /* SOURCE_CLASS_NETWORK_SERVERTASK_H_ */
