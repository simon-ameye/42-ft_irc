#include "User.hpp"

User::User(int fd)
{
	_fd = fd;
	std::cout << "user constructor called" << std::endl;
	_isPassProvided = 0;
	_isOperator = 0;
	_isRegistered = 0;
	_nickName = "";
	_isDeleted = false;
}

User::~User()
{
	std::cout << "user destructor called" << std::endl;
}

int User::getFd() const
{
	return _fd;
}

std::string User::getRealName(void) const
{
	return (_realName);
}

std::string User::getNickName(void) const
{
	return (_nickName);
}

std::string User::getNickNameOrStar(void) const
{
	if (_nickName == "")
		return ("*");
	return (_nickName);
}

std::string User::getUserName(void) const
{
	return (_userName);
}

std::string User::getHostName(void) const
{
	return (_hostName);
}

std::string User::getFullClientIdentifier(void) const
{
	//<nick>!<user>@<host>
	return (_nickName + "!" + _userName + "@" + _hostName);
}

bool User::getIsRegistered(void) const
{
	return _isRegistered;
}

bool User::getIsPassProvided(void) const
{
	return _isPassProvided;
}

bool User::getIsOperator(void) const
{
	return _isOperator;
}

const std::vector<std::string>& User::getInputMessages(void) const
{
	return _inputMessages;
}

std::string User::getInputMessagesBuffer() const
{
	return _inputMessagesBuffer;
}

const std::string User::getOutputMessage() const
{
	return _outputMessage;
}

std::vector<std::string> User::getChannels() const
{
	return _channels;
}

bool User::getIsDeleted() const
{
	return _isDeleted;
}

void User::setRealName(std::string _realName)
{
	this->_realName = _realName;
}

void User::setNickName(std::string _nickName)
{
	this->_nickName = _nickName;
}

void User::setUserName(std::string _userName)
{
	this->_userName = _userName;
}

void User::setHostName(std::string _userName)
{
	this->_hostName = _userName;
}

void User::setIsRegistered(bool _isRegistered)
{
	this->_isRegistered = _isRegistered;
}

void User::setIsPassProvided(bool _isPassProvided)
{
	this->_isPassProvided = _isPassProvided;
}

void User::setIsOperator(bool _isOperator)
{
	this->_isOperator = _isOperator;
}

void User::setInputMessages(std::vector<std::string> _inputMessages)
{
	this->_inputMessages = _inputMessages;
}

void User::setInputMessagesBuffer(std::string _inputMessagesBuffer)
{
	this->_inputMessagesBuffer = _inputMessagesBuffer;
}

void User::addOutputMessage(std::string _outputMessage)
{
	this->_outputMessage += _outputMessage;
	this->_outputMessage += DELIMITER;
}

void User::setIsDeleted(bool isDeleted)
{
	this->_isDeleted = isDeleted;
}

/*Adds the reiceved buffer to the users buffer.
Then, while delimiters are found in users buffer:
Split and place sentences in users _inputMessages
Eventually the buffer is not empty at the end of the loop.
Rest of the message will be recieved in the next loop*/
void User::addBufferToMessages(char *buffer, size_t size)
{
	int pos;
	std::string bufferString;

	bufferString.insert(0, buffer, size);
	_inputMessagesBuffer += bufferString;
	while ((pos = _inputMessagesBuffer.find(DELIMITER)) != -1)
	{
		_inputMessages.push_back(_inputMessagesBuffer.substr(0, pos));
		_inputMessagesBuffer = _inputMessagesBuffer.erase(0, pos + sizeof(DELIMITER) - 1);
	}
}

bool User::isInChannel(std::string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i] == channelName)
			return 1;
	}
	return (0);
}

void User::deleteChannel(std::string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i] == channelName)
			_channels.erase(_channels.begin() + i);
	}
}

void User::addChannel(std::string channelName)
{
	_channels.push_back(channelName);
}

void User::clearInputMessages()
{
	this->_inputMessages.clear();
}

void User::clearOutputMessage()
{
	this->_outputMessage.clear();
}