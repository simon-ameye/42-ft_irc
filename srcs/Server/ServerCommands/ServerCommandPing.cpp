#include "../Server.hpp"

// ERR_NEEDMOREPARAMS   (461)
// ERR_NOORIGIN         (409)
// ERR_NOSUCHSERVER     (402)

void Server::_ping(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	/*----------------command protect------------------*/

    args.size()
    ? user.addOutputMessage("PONG " + args)
    : user.addOutputMessage("PONG");
}