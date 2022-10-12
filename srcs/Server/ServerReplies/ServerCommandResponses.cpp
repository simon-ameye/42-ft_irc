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
	case RPL_WELCOME:
		result << user.getNickName() << " :Welcome to the Internet Relay Chat Network " << user.getNickName() << "!" << user.getUserName();
		break;
	case RPL_TOPIC:
		result << user.getNickName() << " " << channel.getName() << " :" << channel.getTopic();
		break;
	case RPL_NAMREPLY:
		result << user.getNickName() << " = " << channel.getName() << " :" << optionalString;
		break; //"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}" break;
	case RPL_ENDOFNAMES:
		result << user.getNickName() << " " << channel.getName() << " :End of /NAMES list";
		break;
	case RPL_YOUREOPER:
		result << ":You are now an IRC operator";
		break;
	default:
		result << "Unknown reply";
	}
	user.addOutputMessage(result.str());
}
