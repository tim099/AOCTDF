#include "class/network/ClientTask.h"
#include "class/network/Client.h"
namespace game {
namespace network {

ClientTask::ClientTask(Client* _client) {
	client=_client;
}
ClientTask::~ClientTask() {

}
void ClientTask::ExecuteTask(){
	client->client_active();
}
} /* namespace network */
} /* namespace game */
