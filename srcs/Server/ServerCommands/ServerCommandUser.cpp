#include "../Server.hpp"

void Server::_user(std::vector<std::string> tokens, User &user)
{

	Channel c;
	if (tokens.size() < 4)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);
	}

	if (user.isRegistered)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "USER", c);
	}

	user.userName = tokens[0];
	user.hostName = tokens[1];
	user.serverName = tokens[2];

	// todo real name

	user.isRegistered = 1;
	user.outputBuffer += ":" + user.nickName + " 001 " + user.userName + " :Welcome to the Internet Relay Chat Network " + user.nickName + "!" + user.userName + "@" + user.hostName;
	user.outputBuffer += DELIMITER;

	// todo use _commandResponces(user, RPL_WELCOME, "USER", c);
}
