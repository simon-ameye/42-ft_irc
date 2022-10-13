#ifndef CLIENT_HPP
#define CLIENT_HPP

/*Basics*/
#include <iostream>
#include <vector>

#include "../ServerSettings.hpp"
#include "../Channel/Channel.hpp"

class User
{
private:
	int			_fd;
	std::string _nickName;
	std::string _realName;
	std::string _userName;
	std::string _hostName;

	std::string _symbol;
	bool _isRegistered;
	bool _isPassProvided;
	bool _isOperator;
	std::vector<std::string> _inputMessages;
	std::string _inputMessagesBuffer;
	std::string _outputMessage;
	std::vector<std::vector<Channel>::iterator> _channels; // vector of iterators on server's channels vector

public:
	User(int fd);
	~User();

	int			getFd() const;
	std::string getRealName() const;
	std::string getNickName() const;
	std::string getNickNameOrStar() const;
	std::string getUserName() const;
	std::string getHostName() const;
	std::string getSymbol() const;
	std::string getFullClientIdentifier() const;
	bool getIsRegistered() const;
	bool getIsPassProvided() const;
	bool getIsOperator() const;
	const std::vector<std::string>& getInputMessages() const;
	std::string getInputMessagesBuffer() const;
	const std::string getOutputMessage() const;
	std::vector<std::vector<Channel>::iterator> getChannels() const;

	void setRealName(std::string _realName);
	void setNickName(std::string _nickName);
	void setUserName(std::string _userName);
	void setHostName(std::string _userName);
	void setSymbol(std::string _symbol);
	void setIsRegistered(bool _isRegistered);
	void setIsPassProvided(bool _isPassProvided);
	void setIsOperator(bool _isOperator);
	void setInputMessages(std::vector<std::string> _inputMessages);
	void setInputMessagesBuffer(std::string _inputMessagesBuffer);
	void addOutputMessage(std::string _outputMessage);
	void setChannels(std::vector<std::vector<Channel>::iterator> _channels);

	void addBufferToMessages(char *buffer, size_t size);
	void addChannel(std::vector<Channel>::iterator channelIt);
	void deleteChannel(std::string channelName);
	bool isInChannel(std::string channelName);
	void clearInputMessages();
	void clearOutputMessage();
};

#endif