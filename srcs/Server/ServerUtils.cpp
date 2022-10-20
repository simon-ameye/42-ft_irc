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
		{
			std::cout << "found channel " << it->getName() << std::endl;
			return it;
		}
        it++;
    }
	return ite;
}

void Server::_clearDeletedUsers()
{
	std::vector<User>::iterator it = _users.begin();

	while (it != _users.end())
	{
		if (it->getIsRegistered() && it->getIsDeleted())
		{
			close(it->getFd());
			it = _users.erase(it);
		}
		else
			it++;
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
		{
			vectorOfUserIterators.push_back(it);

		}
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

std::string Server::_toupper(const std::string &str)
{
	size_t len = str.size();
	std::string res;
	for (size_t i = 0; i < len; i++)
		res += std::toupper(str[i]);
	return res;
}

void Server::_removeEmptyChannels()
{
    std::vector<Channel>::iterator it = _channels.begin();
    std::vector<Channel>::iterator ite = _channels.end();

    while (it != ite)
    {
        if (getUsersInChannel(it->getName()).size() == 0)
        {
            std::cout << "remove empty channel " << it->getName() << std::endl;
            deleteChannel(it->getName());
        }
        it++;
    }
}

void Server::_sendMessageToChannel(std::string channel, std::string message, const std::string &excludeUser)
{
    std::vector<std::vector<User>::iterator> users = getUsersInChannel(channel);

    for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getNickName() != excludeUser)
			users[i]->addOutputMessage(message);
	}
}

bool Server::_sendPrivMessageToUser(std::string recipient, std::string message, std::string sender)
{
	bool sent = 0;
	std::vector<User>::iterator recip = findUser(recipient);
	if (recip != _users.end())
	{
		recip->addOutputMessage(":" + sender + " PRIVMSG " + recipient + " :" + message);
		sent = 1;
	}
	return sent;
}

bool Server::_sendPrivMessageToChannel(std::string channel, std::string message, std::string sender, const std::string &excludeUser)
{
	bool sent = 0;
    std::vector<std::vector<User>::iterator> users = getUsersInChannel(channel);

    for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->getNickName() != excludeUser)
		{
			users[i]->addOutputMessage(":" + sender + " PRIVMSG " + channel + " :" + message);
			sent = 1;
		}
	}
	return sent;
}

void Server::_sendMessageToChannels(std::vector<std::string> channels, std::string message)
{
    for (size_t i = 0; i < channels.size(); i++)
        _sendMessageToChannel(channels[i], message);
}

void Server::debug()
{
	std::cout << "chans:	";
	for (size_t i = 0; i < _channels.size(); i++)
		std::cout << YELLOW << _channels[i].getName() << " " << RESET;
	std::cout << std::endl;

	for (size_t j = 0; j < _users.size(); j++)
	{
		std::cout << "user :	" << BLUE << _users[j].getNickName() << RESET;
		for (size_t k = 0; k < _users[j].getChannels().size(); k++)
			std::cout << YELLOW << " " << _users[j].getChannels()[k] << RESET;
		std::cout << std::endl;
	}
}
