#include "User.hpp"

User::User()
{
	std::cout << "user constructor called" << std::endl;
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
Split and place sentences in users inputMessages
Eventually the buffer is not empty at the end of the loop.
Rest of the message will be recieved in the next loop*/
void User::addCmdBuffer(char *buffer, size_t size)
{
	int pos;
	std::string bufferString;

	bufferString.insert(0, buffer, size);
	inputBuffer += bufferString;
	while ((pos = inputBuffer.find(DELIMITER)) != -1)
	{
		inputMessages.push_back(inputBuffer.substr(0, pos));
		inputBuffer = inputBuffer.erase(0, pos + sizeof(DELIMITER) - 1);
		std::cout << sizeof(DELIMITER);
	}
}
