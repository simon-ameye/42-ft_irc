

#include "../Server.hpp"

void Server::nameReply(User &user, Channel &channel)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	if (user.getNickName() == "")
		return;
	/*----------------command protect------------------*/

	std::vector<std::vector<User>::iterator> vectorOfUserIterators;
	vectorOfUserIterators = getUsersInChannel(channel.getName());
	std::string users = "";
	for (size_t i = 0; i < vectorOfUserIterators.size(); i++)
	{
		users += "@";
		users += vectorOfUserIterators[i]->getNickName();
		users += " ";
	}
	user.addOutputMessage(":" + _serverName + " 353 " + user.getNickName() + " = " + channel.getName() + " :" + users);
	user.addOutputMessage(":" + _serverName + " 366 " + user.getNickName() + " " + channel.getName() + " :End of /NAMES list");
}

void Server::joinReply(User &newUser, Channel &channel)
{
	std::vector<std::vector<User>::iterator> it = getUsersInChannel(channel.getName());
	for (size_t i = 0; i < it.size(); i++)
	{
		it[i]->addOutputMessage(":" + newUser.getFullClientIdentifier() + " JOIN " + channel.getName());
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

	std::vector<Channel>::iterator channelIt;
	for (std::vector<std::string>::iterator it = channels.begin(), ite = channels.end(); it != ite; it++) //loops over input channels
	{
		if (!hasChannel(*it))
		{
			//create channel
			std::cout << "Create New Channel : " << *it << std::endl;
			_channels.push_back(Channel(*it));
			channelIt = findChannel(*it);
			user.addChannel(channelIt);
			joinReply(user, *channelIt);
			_commandResponces(user, RPL_TOPIC, "JOIN", "", *channelIt);
			nameReply(user, *channelIt);
		}

		else
		{
			//welcome on this channel
			channelIt = findChannel(*it);
			user.addChannel(channelIt);
			joinReply(user, *channelIt);
			_commandResponces(user, RPL_TOPIC, "JOIN", "", *channelIt);
			nameReply(user, *channelIt);
		}
	}
}