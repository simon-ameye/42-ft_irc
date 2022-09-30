#include "Client.hpp"

Client::Client()
{
	std::cout << "client constructor called" << std::endl;
}

Client::~Client()
{
	std::cout << "client destructor called" << std::endl;
}

Client &Client::newClient()
{
	return *(new Client);
}

/*Adds the reiceved buffer to the clients buffer
Then, while delimiters are found in clients buffer:
Split and place sentences in clients inputMessages
Eventually the buffer is not empty at the end of the loop.
Rest of the message will be recieved in the next loop*/
void Client::addCmdBuffer(char *buffer, size_t size)
{
	int pos;
	std::string bufferString;

	bufferString = buffer;
	bufferString = bufferString.substr(0, size);

	inputBuffer += bufferString;
	while ((pos = inputBuffer.find(DELIMITER)) != -1)
	{
		inputMessages.push_back(inputBuffer.substr(0, pos));
		inputBuffer = inputBuffer.erase(0, pos + sizeof(DELIMITER));
	}
}
