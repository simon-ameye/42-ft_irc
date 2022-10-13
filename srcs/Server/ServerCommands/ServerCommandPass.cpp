#include "../Server.hpp"

void Server::_pass(std::string args, User &user)
{
	std::vector<std::string> splitArgs;
	splitArgs = Utils::split(args, ' ');

	Channel channel; //useless, just used to pass to _errorReplies
	if (user.getIsPassProvided() == 1)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "PASS", "", channel);
		return;
	}

	if (splitArgs.size() == 0)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PASS", "", channel);
		return;
	}

	if (splitArgs[0] == _password) //In case of wrong password : no error is returned
		user.setIsPassProvided(true);
}
