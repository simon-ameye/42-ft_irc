#include "../Server.hpp"

void Server::_cap(std::string args, User &user)
{
	(void)args;
	(void)user;

	if (!user.getIsPassProvided())
		return;
}