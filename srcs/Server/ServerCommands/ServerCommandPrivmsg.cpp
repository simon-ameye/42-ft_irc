#include "../Server.hpp"

static void sendChannelMesage(User &sender, User &recipient, std::string &message, std::string channelName)
{
	recipient.addOutputMessage(":" + sender.getNickName() + " PRIVMSG " + channelName + " :" + message);
}

void Server::_privmsg(std::string args, User &user)
{
	if (!user.getIsPassProvided())
		return;

	std::string message;
	std::vector<std::string> parts;
	std::vector<std::string> recievers;

	parts = Utils::split(args, ':');
	recievers = Utils::split(parts[0], ' ');

	if (!recievers.size() || !parts.size())
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PRIVMSG", "");
		return;
	}
	message = parts[1];


	for (size_t i = 0; i < recievers.size(); i++)
	{
		std::cout << "receveir[i] = " << recievers[i] << std::endl;

		std::vector<User>::iterator it1 = findUser(recievers[i]); //for users
		if (it1 != _users.end())
		{
			it1->addOutputMessage(":" + user.getNickName() + " PRIVMSG " + it1->getNickName() + " :" + message);
		}

		std::vector<Channel>::iterator it2 = findChannel(recievers[i]); //for channels
		if (it2 != _channels.end())
		{
			std::vector<std::vector<User>::iterator> itUsers;
			itUsers = getUsersInChannel(recievers[i]);
			for (size_t i = 0; i < itUsers.size(); i++)
			{
				if (user.getNickName() != itUsers[i]->getNickName()) //avoid sending message to sender
					sendChannelMesage(user, *itUsers[i], message, it2->getName());
			}
		}
	}
}
