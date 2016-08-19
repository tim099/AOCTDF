#include "class/network/ServerTask.h"
#include "class/network/Server.h"
namespace game {
namespace network {
ServerTask::ServerTask(Server* _server) {
	server=_server;
}
ServerTask::~ServerTask() {

}
void ServerTask::ExecuteTask(){
	server->server_active();
}
} /* namespace network */
} /* namespace game */
