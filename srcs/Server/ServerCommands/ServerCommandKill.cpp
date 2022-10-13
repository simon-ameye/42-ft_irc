#include "../Server.hpp"

void Server::_kill(std::string args, User &user)
{

	std::string nickname;
	std::string reason;
	std::vector<std::string> _args;
	Channel c;

	_args = Utils::split(args, ' ');
	nickname = _args[0];
	reason = _args[1];
	if (!user.getIsOperator())
		return _errorReplies(user, ERR_NOPRIVILEGES, "KILL", "");
	if (!nickname.size() || !reason.size())
		return _errorReplies(user, ERR_NEEDMOREPARAMS, "KILL", "");

	std::vector<User>::iterator userToKill = findUser(nickname);
	if (userToKill == _users.end())
		return _errorReplies(user, ERR_NOSUCHNICK, "KILL", "");

	// send kill message to user
	userToKill->addOutputMessage(user.getFullClientIdentifier() + " KILL");

	std::vector<User> usersToNotify;
	usersToNotify.push_back((*userToKill));

	// remove user from all channels
	for (std::vector<Channel>::iterator chanIt = _channels.begin(); chanIt != _channels.end(); chanIt++)
	{
		if (userToKill->isInChannel((*chanIt).getName()))
		{
			userToKill->deleteChannel((*chanIt).getName());
			if (getUsersInChannel((*chanIt).getName()).size() == 0)
			{
				deleteChannel((*chanIt).getName());
			}
			else
			{
				std::vector<User> _users = getChannelUsers((*chanIt).getName());
				for (std::vector<User>::iterator userIt = _users.begin(); userIt != _users.end(); userIt++)
				{
					usersToNotify.push_back(*userIt);
				}
			}
		}
	}

	// send QUIT messge to all users in the same channel
	for (std::vector<User>::iterator userIt = usersToNotify.begin(); userIt != usersToNotify.end(); userIt++)
	{
		userIt->addOutputMessage(":" + nickname + "QUIT killed (" + user.getFullClientIdentifier() + ") " + reason + ")");
	}

	userToKill->addOutputMessage("ERROR :Closing Link " + _serverName + " killed (" + user.getFullClientIdentifier() + ") " + reason + ")");
	userToKill->setIsDeleted(true);
}
