#include "Server.hpp"

bool Server::hasUser(std::string nickName, std::string exclude)
{
	for (std::vector<User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->getNickName().compare(nickName) == 0 && (exclude == "" || itb->getNickName() != exclude) )
		{
			return (true);
		}
	}
	return (false);
}

std::vector<User>::iterator Server::findUser(std::string nickName)
{
	for (std::vector<User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->getNickName().compare(nickName) == 0 )
		{
			return (itb);
		}
	}
	return (_users.end());
}

//returns true if the channel exists
bool Server::hasChannel(std::string channelName)
{
	for (std::vector<Channel>::iterator itb = _channels.begin(); itb != _channels.end(); itb++)
	{
		if (itb->getName() == channelName)
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
		if (itb->getName() == channelName)
			return (itb);
	}
	return (_channels.end());
}

//delete user from server
void Server::deleteUser(std::string nickName)
{
	for (std::vector<User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->getNickName()  == nickName)
		{
			close(itb->getFd());
			_users.erase(itb);
		}
	}
}

//delete channel from server
void Server::deleteChannel(std::string channelName) //first delete the channel from each User
{
	for (std::vector<User>::iterator itb1 = _users.begin(); itb1 != _users.end(); itb1++)
	{
		itb1->deleteChannel(channelName);
	}

	for (std::vector<Channel>::iterator itb2 = _channels.begin(); itb2 != _channels.end(); itb2++)
	{
		if (itb2->getName() == channelName)
		{
			_channels.erase(itb2);
		}
	}
}

//returns vector of iterators on each User in a channel
std::vector<std::vector<User>::iterator> Server::getUsersInChannel(std::string channelName)
{
	std::vector<std::vector<User>::iterator> vectorOfUserIterators;
	for (std::vector<User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->isInChannel(channelName)) //user is in channel
		{
			vectorOfUserIterators.push_back(itb);
		}
	}
	return vectorOfUserIterators;
}


std::vector<User>::iterator Server::getUserItByFd(int fd)
{
	for (std::vector<User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->getFd() == fd)
			return (itb);
	}
	return (_users.end());
}

void Server::_sendWelcome(User &user)
{
	if (user.getIsRegistered() == 1)
		return ;
	if (user.getNickName() == "")
		return ;
	if (user.getHostName() == "")
		return ;
	if (user.getRealName() == "")
		return ;
	if (user.getUserName() == "")
		return ;

	user.setIsRegistered(true);
	_commandResponces(user, RPL_WELCOME, "USER", "");
}