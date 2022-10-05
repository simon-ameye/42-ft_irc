#include "../Server.hpp"

void			Server::_ping(std::string args, User &user)
{
	Channel channel;
	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	if (args.size() != 1)
		return ;

	if (_serverName != splitArgs[0])
	{
		_errorReplies(user, ERR_NOSUCHSERVER, "OPER", channel);
		return;
	}

	user._outputMessage += "PONG ";
	user._outputMessage += _serverName + " " + user.nickName;
	user._outputMessage += DELIMITER;

}