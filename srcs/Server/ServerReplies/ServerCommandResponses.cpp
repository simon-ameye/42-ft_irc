#include "../Server.hpp"


void Server::_commandResponces(User &user, int rpl, std::string cmd, Channel &channel, const std::string &optionalString)
{
	(void)cmd;
	(void)channel;
	std::stringstream result;

	result << ":" << _serverName << " ";
	result << Utils::getCode(rpl) << " ";



	switch (rpl)
	{
	case 1:
		result << user.getNickName() << " :Welcome to the Internet Relay Chat Network " << user.getNickName() << "!" << user.getUserName();
		break;
	case 332:
		result << user.getNickName() << channel._channelName << " :" <<channel._topic;
		break;
	case 353:
		result << user.getNickName() << " " << channel._channelName << " :" << user.symbol << optionalString; //"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
		break;
	case 366:
		result << user.getNickName() << " " << channel._channelName << " :End of /NAMES list";
		break;
	case 381:
		result << ":You are now an IRC operator";
		break;
	default:
		result << "Unknown reply";
	}
	result << DELIMITER;
	user._outputMessage += result.str();
}
