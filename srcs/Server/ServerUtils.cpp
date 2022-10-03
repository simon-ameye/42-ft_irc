#include "Server.hpp"

bool Server::hasUser(std::string nick)
{
	std::cout << "comparing";
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second.nickName.compare(nick) == 0)
		{
			return (true);
		}
	}
	return (false);
}
