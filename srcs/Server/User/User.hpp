#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>
#include <vector>

#include "../ServerSettings.hpp"
#include "../Channel/Channel.hpp"

class User
{
	public:
	User();
	~User();
	User &newUser();
	void addBufferToMessages(char *buffer, size_t size);
	private:
	std::string realName; 
	std::string nickName; 
	std::string userName;
	public:
	std::string symbol;
	std::string getRealName();
	std::string getNickName();
	std::string getUserName();
	void setRealName(std::string _realName);
	void setNickName(std::string _nickName);
	void setUserName(std::string _userName);

	bool		isRegistered;
	
	void		addChannel(std::vector<Channel>::iterator channelIt);
	void		deleteChannel(std::string channelName);

	public:
	std::vector<std::string> _inputMessages; //to set private + getter
	std::string _inputMessagesBuffer; //to set private + getter
	std::string _outputMessage; //to set private + getter
	bool		_passProvided; //to set private + getter
	bool		_operator; //to set private + getter

	std::vector<std::vector<Channel>::iterator> _channels; //vector of iterators on server's channels vector
	bool isInChannel(std::string channelName);
};

#endif