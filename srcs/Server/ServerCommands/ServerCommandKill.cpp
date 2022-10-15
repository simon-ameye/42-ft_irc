#include "../Server.hpp"

void Server::_kill(std::string args, User &user)
{

	std::string nickname;
	std::string reason;
	std::vector<std::string> _args;
	Channel c;

	/*----------------command protect------------------*/
	if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	if (!user.getIsOperator())
		return _errorReplies(user, ERR_NOPRIVILEGES, "KILL", "");

	_args = Utils::split(args, ':');
	if (_args.size() != 2)
		return _errorReplies(user, ERR_NEEDMOREPARAMS, "KILL", "");

	nickname = _args[0];
	reason = _args[1];
	Utils::rtrim(nickname, ' ');

	std::vector<User>::iterator userToKill = findUser(nickname);
	if (userToKill == _users.end())
		return _errorReplies(user, ERR_NOSUCHNICK, "KILL", "");

	// send kill message to user
	userToKill->addOutputMessage(user.getFullClientIdentifier() + " KILL");

	std::vector<User *> usersToNotify;
	usersToNotify.push_back((&(*userToKill)));
	std::vector<Channel> channelsToDelete;

	// remove user from all channels
	for (std::vector<Channel>::iterator chanIt = _channels.begin(); chanIt != _channels.end(); chanIt++)
	{
		if (userToKill->isInChannel((*chanIt).getName()))
		{
			userToKill->deleteChannel((*chanIt).getName());
			if (getUsersInChannel((*chanIt).getName()).size() == 0)
			{
				// deleteChannel((*chanIt).getName());
				channelsToDelete.push_back(*chanIt);
			}
			else
			{
				std::vector<User *> _usersInChannel = getChannelUsers((*chanIt).getName());
				for (std::vector<User *>::iterator userIt = _usersInChannel.begin(); userIt != _usersInChannel.end(); userIt++)
				{
					usersToNotify.push_back(*userIt);
				}
			}
		}
	}

	if (channelsToDelete.size())
	{
		std::vector<Channel>::iterator it = channelsToDelete.begin();
		while (it != channelsToDelete.end())
		{
			deleteChannel(it->getName());
			it++;
		}
	}

	// send QUIT messge to all users in the same channel
	for (std::vector<User *>::iterator userIt = usersToNotify.begin(); userIt != usersToNotify.end(); userIt++)
	{
		(*userIt)->addOutputMessage(":" + userToKill->getFullClientIdentifier() + " QUIT :killed (" + user.getFullClientIdentifier() + ") " + reason + ")");
	}

	userToKill->addOutputMessage("ERROR :Closing Link " + _serverName + " killed (" + user.getFullClientIdentifier() + ") " + reason + ")");
	userToKill->setIsDeleted(true);
}
