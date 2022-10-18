#include "../Server.hpp"

void Server::_nameReply(User &user, std::string channelName)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	if (user.getNickName() == "")
		return;
	/*----------------command protect------------------*/

	std::vector<std::vector<User>::iterator> vectorOfUserIterators;
	vectorOfUserIterators = getUsersInChannel(channelName);
	std::string users = "";
	for (size_t i = 0; i < vectorOfUserIterators.size(); i++)
	{
		users += "@";
		users += vectorOfUserIterators[i]->getNickName();
		users += " ";
	}
	user.addOutputMessage(":" + _serverName + " 353 " + user.getNickName() + " = " + channelName + " :" + users);
	user.addOutputMessage(":" + _serverName + " 366 " + user.getNickName() + " " + channelName + " :End of /NAMES list");
}

void Server::_joinReply(User &newUser, std::string channelName)
{
	std::vector<std::vector<User>::iterator> it = getUsersInChannel(channelName);
	for (size_t i = 0; i < it.size(); i++)
	{
		it[i]->addOutputMessage(":" + newUser.getFullClientIdentifier() + " JOIN " + channelName);
	}
}

void Server::_join(std::string args, User &user)
{

	std::vector<std::string> splitArgs = Utils::split(args, ' ');
	if (!splitArgs.size())
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "JOIN", "");
		return;
	}

	std::string rowChannels = splitArgs[0];

	std::vector<std::string> channels = Utils::split(rowChannels, ',');
	if (!channels.size())
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "JOIN", "");
		return;
	}

	for (std::vector<std::string>::iterator it = channels.begin(), ite = channels.end(); it != ite; it++) //loops over input channels
	{
		if (!hasChannel(*it))
		{
			//create channel
			std::cout << "Create New Channel : " << *it << std::endl;
			_channels.push_back(Channel(*it));
			user.addChannel(*it);
			_joinReply(user, *it); //laaa
			_commandResponces(user, RPL_TOPIC, "JOIN", "", *findChannel(*it));
			_nameReply(user, *it);
		}

		else
		{
			user.addChannel(*it);
			_joinReply(user, *it);
			_commandResponces(user, RPL_TOPIC, "JOIN", "", *findChannel(*it));
			_nameReply(user, *it);
		}
	}
}