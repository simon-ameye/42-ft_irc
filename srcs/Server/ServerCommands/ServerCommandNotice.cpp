#include "../Server.hpp"

void Server::_notice(std::string args, User &user)
{
	/*----------------command protect------------------*/
    if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

    std::vector<std::string> targets;
    std::string message;

    try
    {
	    targets = Utils::split(Utils::split(args, ':').at(0), ' ');
	    message = Utils::split(args, ':').at(1);
    }   catch (...) { return; }

	for (size_t i = 0; i < targets.size(); i++)
	{
		// message to users
		_sendPrivMessageToUser(targets[i], message, user.getNickName());

		// message to channel
		_sendPrivMessageToChannel(targets[i], message, user.getNickName(), user.getNickName());
	}
}