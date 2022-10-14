#include "Server.hpp"

bool Server::hasUser(std::string nickName, std::string exclude)
{
	std::vector<User>::iterator it = _users.begin();
	std::vector<User>::iterator ite = _users.end();

    while (it != ite)
    {
		if (it->getNickName().compare(nickName) == 0
        && (exclude == "" || it->getNickName() != exclude))
			return true;
        it++;
    }
	return false;
}

std::vector<User>::iterator Server::findUser(std::string nickName)
{
	std::vector<User>::iterator it = _users.begin();
	std::vector<User>::iterator ite = _users.end();

    while (it != ite)
    {
		if (it->getNickName().compare(nickName) == 0)
			return it;
        it++;
    }
    return ite;
}

//returns true if the channel exists
bool Server::hasChannel(std::string channelName)
{
	for (std::vector<Channel>::iterator it = _channels.begin(), ite = _channels.end(); it != ite; it++)
		if (it->getName() == channelName)
			return true;
	return false;
}

/*returns an iterator
if not found, returns iterator on end*/
std::vector<Channel>::iterator Server::findChannel(std::string channelName)
{
	std::vector<Channel>::iterator it = _channels.begin();
	std::vector<Channel>::iterator ite = _channels.end();

    while (it != ite)
    {
		if (it->getName() == channelName)
			return it;
        it++;
    }
	return ite;
}

//delete user from server
void Server::deleteUser(std::string nickName)
{
	for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
	{
		if (it->getNickName() == nickName)
		{
			close(it->getFd());
			_users.erase(it);
		}
	}
}

//delete channel from server
void Server::deleteChannel(std::string channelName) //first delete the channel from each User
{
    for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
    {
        it->deleteChannel(channelName);
    }

	std::vector<Channel>::iterator itb2 = _channels.begin();
	while (itb2 != _channels.end())
	{
		if (itb2->getName() == channelName)
		{
			itb2 = _channels.erase(itb2);
		}
		else
			itb2++;
	}
}
//returns vector of iterators on each User in a channel
std::vector<std::vector<User>::iterator> Server::getUsersInChannel(std::string channelName)
{
	std::vector<std::vector<User>::iterator> vectorOfUserIterators;

	for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
	{
		if (it->isInChannel(channelName))
			vectorOfUserIterators.push_back(it);
	}
	return vectorOfUserIterators;
}

std::vector<User>::iterator Server::getUserItByFd(int fd)
{
	std::vector<User>::iterator it = _users.begin();
	std::vector<User>::iterator ite = _users.end();

    while (it != ite)
    {
		if (it->getFd() == fd)
			return it;
        it++;
    }
    return ite;
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

std::vector<User> Server::getChannelUsers(std::string channelName)
{
	std::vector<User> users;

	for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
	{
		if (it->isInChannel(channelName))
			users.push_back(*it);
	}
	return users;
}