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
    }
    catch(...)
    {
        return;
    }

	bool userSent;
	bool chanSent;

	for (size_t i = 0; i < targets.size(); i++)
	{
		// message to users
		userSent = _sendPrivMessageToUser(targets[i], message, user.getNickName());

		// message to channel
		chanSent = _sendPrivMessageToChannel(targets[i], message, user.getNickName(), user.getNickName());
	}
}