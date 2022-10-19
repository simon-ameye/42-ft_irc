#include "../Server.hpp"

void Server::_restart(std::string args, User &user)
{
	(void)args;

	/*----------------command protect------------------*/
	if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	if (!user.getIsOperator())
		return _errorReplies(user, ERR_NOPRIVILEGES, "RESTART", "");

	setRestartNeeded(true);
	_exitSignal = true;
}