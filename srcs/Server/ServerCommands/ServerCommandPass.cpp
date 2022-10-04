#include "../Server.hpp"

void Server::_pass(std::vector<std::string> tokens, User &user)
{
	Channel channel; //useless, just used to pass to _errorReplies
	if (user._passProvided == 1)
	{
		_errorReplies(user, ERR_ALREADYREGISTRED, "PASS", channel);
		return;
	}

	if (tokens.size() == 0)
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PASS", channel);
		return;
	}

	if (tokens[0] == _password)
		user._passProvided = 1;
}
