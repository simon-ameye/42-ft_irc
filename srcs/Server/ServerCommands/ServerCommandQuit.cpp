#include "../Server.hpp"

void Server::_quit(std::string args, User &user)
{
	/*----------------command protect------------------*/
    if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

    (void) args;
    _sendMessageToChannels(user.getChannels(), user.getNickName() + " left server");
    user.setIsDeleted(1);
}