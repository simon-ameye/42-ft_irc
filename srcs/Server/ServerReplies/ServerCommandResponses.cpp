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
		result << user.nickName << " :Welcome to the Internet Relay Chat Network " << user.nickName << "!" << user.userName;
		break;
	case 332:
		result << user.nickName << channel._channelName << " :" <<channel._topic;
		break;
	case 353:
		result << user.nickName << user.symbol << channel._channelName << " :" << optionalString; //"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}"
		break;
	case 366:
		//result <<;
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
