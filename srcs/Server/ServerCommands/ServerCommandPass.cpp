#include "../Server.hpp"

void Server::_pass(std::vector<std::string> args, User &user)
{
	Channel channel; //useless, just used to pass to _errorReplies
	if (user._passProvided == 1)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "PASS", channel);
		return;
	}

	if (args.size() == 0)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PASS", channel);
		return;
	}

	if (args[0] == _password) //In case of wrong password : no error is returned
		user._passProvided = 1;
}
