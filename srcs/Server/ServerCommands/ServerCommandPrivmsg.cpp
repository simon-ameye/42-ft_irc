#include "../Server.hpp"

void Server::_privmsg(std::string args, User &user)
{
	// (void) user;
	// std::string target;
	// target = Utils::split(args, ' ')[0];
	// std::cout << "------> target = " <<  target << std::endl;
	
	// std::string text;
	// text = args.substr(target.size(), args.size());
	// std::cout << "------> text = " <<  text << std::endl;

	std::string _message;
	std::vector<std::string> _parts;
	std::vector<std::string> _args;
	std::vector<std::string> _recievers;
	Channel channel;

	_parts = Utils::split(args, ':');
	_args = Utils::split(_parts[0], ' ');

	if (!args.size() || !_parts.size())
	{
		_errorReplies(user, ERR_NEEDMOREPARAMS, "PRIVMSG", channel);
		return;
	}
	_message = _parts[1];
	_recievers = Utils::split(_parts[0], ' ');

	for (size_t i = 0; i < _recievers.size(); i++)
	{
		std::map<int, User>::iterator it = findUser(_recievers[i]);
		if (it != _users.end())
		{
			_users[(*it).first]._outputMessage += ":" + user.nickName + " PRIVMSG " + (*it).second.nickName + " :" + _message;
			_users[(*it).first]._outputMessage += DELIMITER;
		}
	}

//no need add error cause fin alone if not enought param
	
}
