#include "../Server.hpp"

void Server::_die(std::string args, User &user)
{
	/*----------------command protect------------------*/
	if (!user.getIsPassProvided())
		return;
	if (user.getNickName() == "*")
		return;
	/*----------------command protect------------------*/

    (void)args;
    (void)user;

    if (user.getIsOperator() == false)
    	_errorReplies(user, ERR_NOPRIVILEGES, "DIE", "");
    else
    {
        std::cout << "GOODBYE" << std::endl;
        _exitSignal = 1;
    }

}