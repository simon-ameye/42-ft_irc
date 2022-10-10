#include "Channel.hpp"

Channel::Channel (void)
{
	std::cout << "Channel Default Constructor Called" << std::endl;
	_channelName = "";
	_topic = "default topic";
}

Channel::Channel (std::string channelName)
: _channelName(channelName)
{
	std::cout << "Channel Constructor Called" << std::endl;
}

Channel::~Channel(){}