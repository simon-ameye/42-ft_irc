#include "../Server.hpp"

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

	for (std::vector<std::string>::iterator itb = channels.begin(); itb != channels.end(); itb++)
	{
		if (!hasChannel(*itb))
		{
			//create channel
			std::cout << "Create New Channel" << std::endl;
			_channels.push_back(Channel(*itb));
			channelIt = findChannel(*itb);
			user.addChannel(channelIt);
		}
		else
		{
			//welcome on this channel
			channelIt = findChannel(*itb);
			user.addChannel(channelIt);
			_commandResponces(user, RPL_TOPIC, "JOIN", *channelIt);
			std::cout << user.nickName << " joins " << channelIt->_channelName << std::endl;
		}
	}

	//A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message.
	// RPL_TOPIC (332)
	// one or more RPL_NAMREPLY (353)
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}