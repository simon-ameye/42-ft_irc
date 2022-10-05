#include "../Server.hpp"

void Server::_user(std::vector<std::string> args, User &user)
{

	Channel c;
	if (args.size() < 4)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);
	}

	if (user.isRegistered)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "USER", c);
	}

	user.userName = args[0];
	user.hostName = args[1];
	user.serverName = args[2];

	// todo real name
	if (user._passProvided == 0) // add error message
		return ;


	user.isRegistered = 1;
	user._outputMessage += ":" + user.nickName + " 001 " + user.userName + " :Welcome to the Internet Relay Chat Network " + user.nickName + "!" + user.userName + "@" + user.hostName;
	user._outputMessage += DELIMITER;

	// todo use _commandResponces(user, RPL_WELCOME, "USER", c);
}
