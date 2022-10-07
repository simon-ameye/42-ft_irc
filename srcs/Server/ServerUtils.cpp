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

//returns true if the channel exists
bool Server::hasChannel(std::string channelName)
{
	for (std::vector<Channel>::iterator itb = _channels.begin(); itb != _channels.end(); itb++)
	{
		if (itb->_channelName == channelName)
			return (true);
	}
	return (false);
}

/*returns an iterator
if not found, returns iterator on end*/
std::vector<Channel>::iterator Server::findChannel(std::string channelName)
{
	for (std::vector<Channel>::iterator itb = _channels.begin(); itb != _channels.end(); itb++)
	{
		if (itb->_channelName == channelName)
			return (itb);
	}
	return (_channels.end());
}

//delete user from server
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

//delete channel from server
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

//returns vector of iterators on each User in a channel
std::vector<std::map<int, User>::iterator> Server::getUsersInChannel(std::string channelName)
{
	std::vector<std::map<int, User>::iterator> vectorOfUserIterators;
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second.isInChannel(channelName)) //user is in channel
		{
			vectorOfUserIterators.push_back(itb);
		}
	}
	return vectorOfUserIterators;
}
