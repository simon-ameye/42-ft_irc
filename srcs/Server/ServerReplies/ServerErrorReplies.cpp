#include "../Server.hpp"

void Server::_errorReplies(User &user, int err, std::string cmd, Channel &channel)
{
	std::stringstream result;

	result << ":" << _serverName << " ";
	result << err << " ";

	switch (err)
	{
		case 401:
			result << user.nickName << " :No such nick/channel";
			break;
		case 402:
			result << _serverName << " :No such server";
			break;
		case 403:
			result << channel.channelName << " :No such server";
			break;
		case 404:
			result << channel.channelName << " :Cannot send to channel";
			break;
		case 405:
			result << channel.channelName << " :You have joined too many channels";
			break;
		case 406:
			result << user.nickName << " :There was no such nickname";
			break;
		case 421:
			result << cmd << " :Unknown command";
			break;
		case 461:
			result << cmd << " :Not enough parameters";
			break;
		case 462:
			result << ":Unauthorized command (already registered)";
			break;
		case 464:
			result << ":Password incorrect";
			break;

		default:
			result << "Unknown error";
			
	}
	result << DELIMITER;
	user._outputMessage += result.str();
}
