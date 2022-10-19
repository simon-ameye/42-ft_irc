#include "../Server.hpp"

void Server::_pass(std::string args, User &user)
{
    // only because needed by `_errorReplies`
	Channel channel;

	if (user.getIsPassProvided())
		return _errorReplies(user, ERR_ALREADYREGISTRED, "PASS", "", channel);

	std::vector<std::string> splitArgs = Utils::split(args, ' ');

	if (splitArgs.size() == 0)
		return _errorReplies(user, ERR_NEEDMOREPARAMS, "PASS", "", channel);

    // in case of wrong password no error returned
	if (splitArgs[0] == _password)
		user.setIsPassProvided(true);
}
