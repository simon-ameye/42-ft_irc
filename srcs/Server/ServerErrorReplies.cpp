#include "Server.hpp"

void Server::_errorReplies(User &user, int error, std::string cmd, Channel &channel)
{
	std::stringstream result;

	result << ":" << _serverName << " ";
	result << error << " ";

	switch (error)
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

		case 461:
			result << cmd << " :Not enough parameters";
			break;
		case 462:
			result << ":Unauthorized command (already registered)";
			break;

		default:
			result << "Unknown error";
			
	}
	result << DELIMITER;
	user.outputBuffer += result.str();
}
