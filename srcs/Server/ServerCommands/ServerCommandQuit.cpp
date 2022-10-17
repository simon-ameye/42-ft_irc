#include "../Server.hpp"

void Server::_quit(std::string args, User &user)
{
    (void) args;

    if (!user.getIsRegistered())
		return;

    _sendMessageToChannels(user.getChannels(), user.getNickName() + " [" + user.getUserName() + "@" + user.getHostName() + "] has quit");

    user.setIsDeleted(1);
}