#include "../Server.hpp"

void Server::_join(std::string args, User &user)
{
	(void)args;
	(void)user;

	std::vector<Channel>::iterator channelIt;
	std::string rowChannels;
	std::string channel;
	std::vector<std::string> channels;


	rowChannels = Utils::split(args, ' ')[0];

	Channel c;

	if (args == "")
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "JOIN", c);
	}

	
	for (std::vector<std::string>::iterator itb = channels.begin(); itb != channels.end(); itb++)
	{
		


	if (Utils::split(args, ' ').size() >= 2)
		key = Utils::split(args, ' ')[1];
	else
		key = ""; //if no key, key = ""

	if (!hasChannel(channel))
	{
		//create channel
		std::cout << "Create New Channel" << std::endl;
		_channels.push_back(Channel(channel));
		channelIt = findChannel(channel);
		user.addChannel(channelIt);
		//channelIt->opUsers.push_back(User.nickName);
		//make user an operator
		
	}
	else if (findChannel(channel)->_key != key)
	{
		//return Not right password
	}
	else
	{
		//welcome on this channel
	}

	//A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message.
	// RPL_TOPIC (332)
	// one or more RPL_NAMREPLY (353)
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}