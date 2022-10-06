#include "User.hpp"

User::User()
{
	std::cout << "user constructor called" << std::endl;
	_passProvided = 0;
	_operator = 0;
	 isRegistered = 0;

}

User::~User()
{
	std::cout << "user destructor called" << std::endl;
}

User &User::newUser()
{
	return *(new User);
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
		if (_channels[i]->_channelName == channelName)
			return 1;
	}
	return (0);
}

void User::deleteChannel(std::string channelName)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i]->_channelName == channelName)
			_channels.erase(_channels.begin() + i);
	}
}
