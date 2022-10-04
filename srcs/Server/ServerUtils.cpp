#include "Server.hpp"

bool Server::hasUser(std::string nick, std::string exclude)
{
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second.nickName.compare(nick) == 0 && (exclude == "" || itb->second.nickName != exclude) )
		{
			return (true);
		}
	}
	return (false);
}