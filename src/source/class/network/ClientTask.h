#ifndef SOURCE_CLASS_NETWORK_CLIENTTASK_H_
#define SOURCE_CLASS_NETWORK_CLIENTTASK_H_

#include "class/tim/thread/task/Task.h"

namespace game {
namespace network {
class Client;

class ClientTask: public Tim::Task {
public:
	ClientTask(Client* client);
	virtual ~ClientTask();

protected:
	virtual void ExecuteTask();
	Client* client;
};

} /* namespace network */
} /* namespace game */

#endif /* SOURCE_CLASS_NETWORK_CLIENTTASK_H_ */
