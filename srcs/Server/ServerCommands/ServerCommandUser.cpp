#include "../Server.hpp"

void Server::_user(std::string args, User &user)
{
	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	Channel c;
	if (splitArgs.size() < 4)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);
		return ;
	}

	if (user.isRegistered)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "USER", c);
		return ;
	}

	user.userName = splitArgs[0];
	std::cout << "username = " << user.userName << std::endl;
	user.hostName = splitArgs[1];
	std::cout << "hostname = " << user.hostName << std::endl;
	user.serverName = splitArgs[2];
	std::cout << "servername = " << user.serverName << std::endl;

	// todo real name
	if (user._passProvided == 0) // add error message
		return ;


	user.isRegistered = 1;
	user._outputMessage += ":" + user.nickName + " 001 " + user.userName + " :Welcome to the Internet Relay Chat Network " + user.nickName + "!" + user.userName + "@" + user.hostName;
	user._outputMessage += DELIMITER;

	// todo use _commandResponces(user, RPL_WELCOME, "USER", c);
}
