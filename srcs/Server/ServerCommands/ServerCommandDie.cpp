#include "../Server.hpp"

void Server::_die(std::string args, User &user)
{
	/*----------------command protect------------------*/
    if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

    (void)args;
    (void)user;

    if (!user.getIsOperator())
    	return _errorReplies(user, ERR_NOPRIVILEGES, "DIE", "");

    _exitSignal = 1;
}