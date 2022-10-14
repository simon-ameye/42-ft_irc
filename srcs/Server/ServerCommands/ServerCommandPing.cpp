#include "../Server.hpp"

// ERR_NEEDMOREPARAMS   (461)
// ERR_NOORIGIN         (409)
// ERR_NOSUCHSERVER     (402)

void Server::_ping(std::string args, User &user)
{
    (void)args;

	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	/*----------------command protect------------------*/

    user.addOutputMessage(":" + _serverName + " PONG :" + user.getNickName());
}