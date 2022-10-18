#include "../Server.hpp"

void Server::_part(std::string args, User & user)
{
	if (!user.getIsRegistered())
		return;

    std::vector<std::string> channels_to_leave = Utils::split(args, ' ');

    if (channels_to_leave.size() == 0)
        return _errorReplies(user, ERR_NEEDMOREPARAMS, "PART", "");

    std::vector<std::string>::iterator it = channels_to_leave.begin();
    std::vector<std::string>::iterator ite = channels_to_leave.end();

    while (it != ite)
    {
        if (!hasChannel(*it))
            _errorReplies(user, ERR_NOSUCHCHANNEL, "PART", "", *it);
        else if (!user.deleteChannel(*it))
            _errorReplies(user, ERR_NOTONCHANNEL, "PART", "", *it);
        else
            //_sendMessageToChannel(*it, user.getNickName() + " [" + user.getUserName() + "@" + user.getHostName() + "] left " + *it);
            _sendMessageToChannel(*it, ":" + user.getFullClientIdentifier() + " left " + *it);
        it++;
    }
}
