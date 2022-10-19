#include "Channel.hpp"

Channel::Channel (void)
{
	_topic = "default topic";
}

Channel::Channel (std::string channelName)
{
	_topic = "default topic";
	_channelName = channelName;
	std::cout << "channel constructor called with name : " << _channelName << std::endl;
}

std::string Channel::getName() const
{ return (_channelName); }

std::string Channel::getTopic() const
{ return (_topic); }

void Channel::setTopic(std::string topic)
{ _topic = topic; }

Channel::~Channel(){}