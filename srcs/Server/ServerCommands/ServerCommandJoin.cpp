#include "../Server.hpp"

void Server::nameReply(User &user, Channel &channel)
{
	/*----------------command protect------------------*/
    if (!user.getIsRegistered())
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
		//if (i != vectorOfUserIterators.size() - 1)
		//	users += " ";
	}
	_commandResponces(user, RPL_NAMREPLY, "JOIN", users, channel);
	_commandResponces(user, RPL_ENDOFNAMES, "JOIN", "", channel);
}

void Server::joinReply(User &newUser, Channel &channel)
{
	std::vector<std::vector<User>::iterator> it = getUsersInChannel(channel.getName());
	for (size_t i = 0; i < it.size(); i++)
	{
		it[i]->addOutputMessage(":" + newUser.getNickName() + "@" + newUser.getRealName() + " JOIN " + channel.getName());
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
			// JOIN
			//user.addOutputMessage(":" + user.getNickName() + " JOIN " + *it);
			_commandResponces(user, RPL_TOPIC, "JOIN", "", *channelIt);
			nameReply(user, *channelIt);
		}

		else
		{
			//welcome on this channel
			channelIt = findChannel(*it);
			user.addChannel(channelIt);
			_commandResponces(user, RPL_TOPIC, "JOIN", "", *channelIt);
			std::cout << user.getNickName() << " joins " << channelIt->getName() << std::endl;
			joinReply(user, *channelIt);
			nameReply(user, *channelIt);
		}
	}

	//A JOIN message with the client as the message <source> and the channel they have joined as the first parameter of the message.
	// RPL_TOPIC (332)
	// one or more RPL_NAMREPLY (353) + RPL_ENDOFNAMES (366)
	//"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
}