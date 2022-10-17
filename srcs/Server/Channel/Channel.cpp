#include "Channel.hpp"

Channel::Channel (void)
{ _topic = "default topic"; }

Channel::Channel (std::string channelName) : _channelName(channelName)
{ _topic = "default topic"; }

std::string Channel::getName() const
{ return (_channelName); }

std::string Channel::getTopic() const
{ return (_topic); }

Channel::~Channel(){}