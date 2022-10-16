#include "../Server.hpp"

void Server::_rehash(std::string args, User &user)
{

	(void)args;

	/*----------------command protect------------------*/
	if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	if (!user.getIsOperator())
		return _errorReplies(user, ERR_NOPRIVILEGES, "REHASH", "");
	
	refreshConfig();

	_commandResponces(user, RPL_REHASHING, "REHASH", "");
}