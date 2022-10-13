#include "../Server.hpp"

void Server::_commandResponces(User &user, int rpl, std::string cmd, Channel &channel, const std::string &optionalString)
{
	(void)cmd;
	(void)channel;
	std::stringstream result;

	result << ":" << _serverName << " " << Utils::getCode(rpl) << " " << user.getNickName() << " :";

	switch (rpl)
	{
	case RPL_WELCOME:
		result << " YOOOOO ! Welcome to our Internet Relay Chat Network " << user.getFullClientIdentifier();
		break;
	case RPL_TOPIC:
		result << " " << channel.getName() << " :" << channel.getTopic();
		break;
	case RPL_NAMREPLY:
		result << " = " << channel.getName() << " :" << optionalString;
		break; //"<client> <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}" break;
	case RPL_ENDOFNAMES:
		result << " " << channel.getName() << " :End of /NAMES list";
		break;
	case RPL_YOUREOPER:
		result << " You are now an IRC operator";
		break;
	default:
		result << " Unknown reply";
	}
	user.addOutputMessage(result.str());
}
