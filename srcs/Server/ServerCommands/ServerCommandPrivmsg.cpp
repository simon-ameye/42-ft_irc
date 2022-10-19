#include "../Server.hpp"

void Server::_privmsg(std::string args, User &user)
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
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PRIVMSG", "");
        return;
    }

	bool userSent;
	bool chanSent;

	for (size_t i = 0; i < targets.size(); i++)
	{
		// message to users
		userSent = _sendPrivMessageToUser(targets[i], message, user.getNickName());

		// message to channel
		chanSent = hasChannel(targets[i]);
        _sendPrivMessageToChannel(targets[i], message, user.getNickName(), user.getNickName());

		if (!userSent && !chanSent)
			_errorReplies(user, ERR_NOSUCHNICK, "PRIVMSG", targets[i]);
	}
}
