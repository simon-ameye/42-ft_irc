#include "../Server.hpp"

static void sendMesage(User &sender, User &recipient, std::string &message, std::string channelName)
{
	std::cout << " ===== SEND MESSAGE ======" << std::endl;
	recipient._outputMessage += ":" + sender.nickName + " PRIVMSG " + channelName + " :" + message;
	recipient._outputMessage += DELIMITER;
}

void Server::_privmsg(std::string args, User &user)
{
	std::string message;
	std::vector<std::string> parts;
	std::vector<std::string> recievers;
	Channel channel;

	parts = Utils::split(args, ':');
	recievers = Utils::split(parts[0], ' ');

	if (!recievers.size() || !parts.size())
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PRIVMSG", channel);
		return;
	}
	message = parts[1];
	

	for (size_t i = 0; i < recievers.size(); i++)
	{
		std::cout << "receveir[i] = " << recievers[i] << std::endl;

		std::map<int, User>::iterator it1 = findUser(recievers[i]); //for users
		if (it1 != _users.end())
		{
			std::cout << "------- USER --------\n";
			std::cout << "user found = " << user.nickName << std::endl;
			std::cout << "destinataire found = " << it1->second.nickName << std::endl;

			it1->second._outputMessage += ":" + user.nickName + " PRIVMSG " + it1->second.nickName + " :" + message;
			it1->second._outputMessage += DELIMITER;
		}

		std::vector<Channel>::iterator it2 = findChannel(recievers[i]); //for channels
		if (it2 != _channels.end())
		{
			std::vector<std::map<int, User>::iterator> itUsers;
			itUsers = getUsersInChannel(recievers[i]);
			std::cout << "------- CHANNEL --------\n";
			for (size_t i = 0; i < itUsers.size(); i++)
			{
				std::cout << "user found = " << user.nickName << std::endl;
				std::cout << "destinataire found = " << itUsers[i]->second.nickName << std::endl;
				sendMesage(user, itUsers[i]->second, message, it2->_channelName);
			}
		}

	}

//no need add error cause fin alone if not enought param
	
}
