#include "../Server.hpp"

void			Server::_ping(std::vector<std::string> args, User &user)
{
	Channel channel;

	if (args.size() != 1)
		return ;

	if (_serverName != args[0])
	{
		_errorReplies(user, ERR_NOSUCHSERVER, "OPER", channel);
		return;
	}

	user._outputMessage += "PONG ";
	user._outputMessage += _serverName + " " + user.nickName;
	user._outputMessage += DELIMITER;

}