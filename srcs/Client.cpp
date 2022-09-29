#include "Client.hpp"

Client::Client() {}

Client::~Client() {}

Client &Client::newClient()
{
	return *(new Client);
}

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
		inputBuffer = inputBuffer.erase(0, pos + 1);
	}
}
