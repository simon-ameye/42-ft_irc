#include "../Server.hpp"

void Server::_die(std::string args, User &user)
{
    Channel c;
    (void)args;
    (void)user;
    
    if (user.getIsOperator() == false)
    	_errorReplies(user, ERR_NOPRIVILEGES, "DIE", c);
    else
    {
        std::cout << "GOODBYE" << std::endl;
        _exitSignal = 1;
    }

}