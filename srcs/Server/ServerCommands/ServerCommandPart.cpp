#include "../Server.hpp"

void Server::_part(std::string args, User & user)
{
	if (!user.getIsRegistered())
		return;

	//Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

	std::string cmd;
	std::vector<std::string> channels_to_leave;

	try
	{
		cmd	=				Utils::split_cmd(args, ' ').at(0);
		channels_to_leave = Utils::split(cmd, ',');
	}
	catch(...)
	{ return _errorReplies(user, ERR_NEEDMOREPARAMS, "PART", ""); }

	std::string message;
	try { message = Utils::split_cmd(args, ' ').at(1); }
	catch (const std::exception& e)
	{ message = ""; }

    std::vector<std::string>::iterator it = channels_to_leave.begin();
    std::vector<std::string>::iterator ite = channels_to_leave.end();

    while (it != ite)
    {
        if (!hasChannel(*it))
            _errorReplies(user, ERR_NOSUCHCHANNEL, "PART", "", *it);
        else if (!user.isInChannel(*it))
            _errorReplies(user, ERR_NOTONCHANNEL, "PART", "", *it);
        else
		{
			message == ""
			? _sendMessageToChannel(*it, ":" + user.getFullClientIdentifier() + " PART " + *it)
    		: _sendMessageToChannel(*it, ":" + user.getFullClientIdentifier() + " PART " + *it + " :" + message);
			user.deleteChannel(*it);
		}
        it++;
    }
}
