#include "../Server.hpp"

void Server::_user(std::string args, User &user)
{
	std::vector<std::string> _parts;
	std::vector<std::string> _args;
	std::string _realName;
	std::string _username;

	_parts = Utils::split(args, ':');
	_args = Utils::split(_parts[0], ' ');
	_realName = _parts[1];
	_username = _args[0];

	Channel c;
	if (user.isRegistered)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "USER", c);
		return;
	}

	if ((_args.size() + 1) < 4)
	{
		return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);
	}

	if (_username.size() < 1)
	{
		return _errorReplies(user, ERR_NEEDMOREPARAMS, "USER", c);
	}

	user.setUserName(_username);
	user.setRealName(_realName);
	user.isRegistered = true;
	_commandResponces(user, RPL_WELCOME, "USER", c);
}
