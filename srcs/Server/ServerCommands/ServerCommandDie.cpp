#include "../Server.hpp"

void Server::_die(std::string args, User &user)
{
    Channel c;
    (void)args;
    (void)user;
    
    if (user._operator == false)
    	_errorReplies(user, ERR_NOPRIVILEGES, "JOIN", c);
    else
    {
        std::cout << "GOODBYE" << std::endl;
        // no need to clears userlist cause destructor delete new User
        exit (-1);
    }

}