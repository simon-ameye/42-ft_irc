#include "../Server.hpp"

void Server::nameReply(User &user, Channel &channel)
{
	std::vector<std::map<int, User>::iterator> vectorOfUserIterators;
	vectorOfUserIterators = getUsersInChannel(channel._channelName);
	std::string users = "";
	for (size_t i = 0; i < vectorOfUserIterators.size(); i++)
	{
		users += vectorOfUserIterators[i]->second.getNickName();
		if (i != vectorOfUserIterators.size() - 1)
			users += " ";
	}
	_commandResponces(user, RPL_NAMREPLY, "JOIN", channel, users);
	_commandResponces(user, RPL_ENDOFNAMES, "JOIN", channel);
}

void Server::joinReply(User &newUser, Channel &channel)
{
	std::vector<std::map<int, User>::iterator> it = getUsersInChannel(channel._channelName);
	for (size_t i = 0; i < it.size(); i++)
	{
		it[i]->second._outputMessage += ":" + newUser.getNickName() + " JOIN " + channel._channelName + DELIMITER;
	}
}

void Server::_join(std::string args, User &user)
{
	(void)args;
	(void)user;

	std::string rowChannels;
	std::vector<std::string> channels;
	std::vector<Channel>::iterator channelIt;

	rowChannels = Utils::split(args, ' ')[0];
	channels = Utils::split(rowChannels, ',');

	Channel c;

	if (args == "")
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "JOIN", c);
	}

	for (std::vector<std::string>::iterator itb = channels.begin(); itb != channels.end(); itb++) //loops over input channels
	{
		if (!hasChannel(*itb))
		{
			//create channel
			std::cout << "Create New Channel : " << *itb << std::endl;
			_channels.push_back(Channel(*itb));
			channelIt = findChannel(*itb);
			user.addChannel(channelIt);
			// JOIN
			user._outputMessage += ":" + user.getNickName() + " JOIN " + *itb;
			user._outputMessage += DELIMITER;
			nameReply(user, *channelIt);
		}

		else
		{
			//welcome on this channel
			channelIt = findChannel(*itb);
			user.addChannel(channelIt);
			_commandResponces(user, RPL_TOPIC, "JOIN", *channelIt);
			std::cout << user.getNickName() << " joins " << channelIt->_channelName << std::endl;
			joinReply(user, *channelIt);
			nameReply(user, *channelIt);
		}
	}

	//A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message.
	// RPL_TOPIC (332)
	// one or more RPL_NAMREPLY (353) + RPL_ENDOFNAMES (366)
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}