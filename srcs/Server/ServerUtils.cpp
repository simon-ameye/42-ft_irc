#include "Server.hpp"

bool Server::hasUser(std::string nickName, std::string exclude)
{
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second.nickName.compare(nickName) == 0 && (exclude == "" || itb->second.nickName != exclude) )
		{
			return (true);
		}
	}
	return (false);
}


void Server::deleteUser(std::string nickName)
{
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second.nickName  == nickName)
		{
			close(itb->first);
			_users.erase(itb->first);
		}
	}
}

void Server::deleteChannel(std::string channelName) //first delete the channel from each User
{
	for (std::map<int, User>::iterator itb1 = _users.begin(); itb1 != _users.end(); itb1++)
	{
		itb1->second.deleteChannel(channelName);
	}

	for (std::vector<Channel>::iterator itb2 = _channels.begin(); itb2 != _channels.end(); itb2++)
	{
		if (itb2->_channelName == channelName)
		{
			_channels.erase(itb2);
		}
	}
}