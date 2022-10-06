#include "../Server.hpp"

void Server::_join(std::string args, User &user)
{
	(void)args;
	(void)user;

	std::string rowChannels;
	std::string rowKeys;
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	rowChannels = Utils::split(args, ' ')[0];
	channels = Utils::split(rowChannels, ',');

	if (Utils::split(args, ' ').size() == 2)
	{
		rowKeys = Utils::split(args, ' ')[1];
		keys = Utils::split(rowKeys, ',');
	}
	
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (!hasChannel(channels[i]))
		{
			//create channel
			//make user an operator
		}
		else if (findChannel(channels[i])->_key != keys[i])
		{
			//return Not right password
		}
		else
		{
			//welcome on this channel
		}
	}

	//A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message.
	// RPL_TOPIC (332)
	// one or more RPL_NAMREPLY (353)
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}