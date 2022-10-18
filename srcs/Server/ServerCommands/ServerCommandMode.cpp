#include "../Server.hpp"

void Server::_mode(std::string args, User &user)
{
	/*----------------command protect------------------*/
    if (!user.getIsRegistered())
		return;
	/*----------------command protect------------------*/

	(void) args;
	(void) user;
}