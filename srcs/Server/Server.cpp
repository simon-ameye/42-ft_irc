#include "Server.hpp"
#include <stdio.h>
#include <stdlib.h>

Server::Server(char *port, char *password)
{
	// Set server parameters
	_serverName = "ft_irc";
	_exitSignal = 0;
	_password = password;

	// Defining server sockaddr_in structure
	_port = atoi(port);
	if (_port == 0)
        _exit_server("invalid port", -1);

	_sin.sin_port = htons(_port);
	_sin.sin_addr.s_addr = htonl(INADDR_ANY); // set IP address automatically
	_sin.sin_family = AF_INET;

	// Defining server sockaddr_in structure size
	_sizeofsin = sizeof(_sin);

	// Creating socket
	_masterSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_masterSocket == -1)
        _exit_server("socket()", -1);

	// Setting socket reuse
	int enable = 1; // pas compris encore
	if (setsockopt(_masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)) == -1)
        _exit_server("setsockopt()", -1);

	// Setting socket to be non blocking
	if (fcntl(_masterSocket, F_SETFL, O_NONBLOCK) == -1)
        _exit_server("fcntl()", -1);

	// Binding socket to port and set socket settings
	if (bind(_masterSocket, (sockaddr *)&_sin, _sizeofsin) == -1)
        _exit_server("bind()", -1);

	// Listening
	if (listen(_masterSocket, 5) == -1)
        _exit_server("listen()", -1);

	std::cout << "Server starting on port " << _port << " with password " << _password << std::endl;
}

/*Create the pollfds structure.
It will be used here and also in further functions
Check master socket and all users fd with pollfds structure
If none is ready, wait (saves computer ressources)
Check the master socket
It it is ready, it means that a user is trying to connect
Thus, creates a user and give it its new fd.
This user is not set in pollfs. Thus, its fd will be read in the next loop*/
void Server::block(void)
{
	std::cout << "---------- Server::connect ---------" << std::endl;

	pollfd tempPollFd;

	_pollfds.clear();

	/*Add masterSocket to pollfds*/
	tempPollFd.fd = _masterSocket;
	tempPollFd.events = POLLIN;
	_pollfds.push_back(tempPollFd);

	/*Add all the users sockets to pollfds*/
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		tempPollFd.fd = itb->first;
		_pollfds.push_back(tempPollFd);
	}

	/*wait for an event*/
	// std::cout << "poll()" << std::endl;
	if (poll(&(_pollfds[0]), _pollfds.size(), POLL_TIMEOUT) == -1) // BLOCKS untill a fd is available
        _exit_server("poll()", -1);
}

void Server::getNewUsers(void)
{
	/*Check masterSocket's fd to check for new connection
	Create new User
	-->Users are created in Server::connect
	-->Fds are created ans associated to Users in Server::connect
	-->Eventually Users are close() and cleared in Server::connect
	-->Any remaning User is close() and cleared at Server destruction
	==>This guarantees that users are closed only once*/
	int tempFd;

	if (_pollfds[0].revents == POLLIN)
	{
		/*Accepting and creating new user*/
		//std::cout << "accept()" << std::endl;
		tempFd = accept(_masterSocket, (sockaddr *)&_sin, &_sizeofsin); // accept connection and get the fd
		_users[tempFd];													// create a user (without calling constructor twice)
		if (tempFd == -1)
            _exit_server("accept()", -1);
		std::cout << "New user accepted with fd: " << tempFd << std::endl;
	}
}


/*If user's fd is ready, get the data
And put it in user buffer and _inputMessages*/
void Server::getMessages(void)
{

	char buffer[BUFFER_SIZE];
	int sizeRead;

	/*Output debugging data*/
	// std::cout << "size of _users : " << _users.size() << std::endl;
	// std::cout << "list of fds     : ";
	// for (long unsigned int i = 0; i < _pollfds.size(); i++)
	//	std::cout << _pollfds[i].fd << " ";
	// std::cout << std::endl;
	// std::cout << "list of revents : ";
	// for (long unsigned int i = 0; i < _pollfds.size(); i++)
	//	std::cout << _pollfds[i].revents << " ";
	// std::cout << std::endl;

	/*Check if users's fd is sending new data*/
	for (std::vector<pollfd>::iterator itb = ++_pollfds.begin(); itb != _pollfds.end(); itb++) // skipping the master socket
	{
		if (itb->revents == POLLIN)
		{
			/*Users fd is ready, lets read it on one buffer.*/
			// std::cout << "recv()" << std::endl;
			Utils::clearBuffer(buffer, BUFFER_SIZE);
			sizeRead = recv(itb->fd, buffer, BUFFER_SIZE, 0);
			if (sizeRead == -1) // recv error
                _exit_server("recv()", -1);
			else if (sizeRead == 0) // recv size = 0 : nothing to read anymore. User disconnected.
			{
				getpeername(itb->fd, (struct sockaddr *)&_sin, (socklen_t *)&_sizeofsin);
				std::cout << "Host disconnected , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
				close(itb->fd);
				_users.erase(itb->fd);
				std::cout << "host closed and erased" << std::endl;
			}
			else // data to read, add buffer to users _inputMessages
			{
				_users[itb->fd].addBufferToMessages(buffer, sizeRead);
			}
		}
	}
}

/*Double loop :
Loops over users
Loops over _inputMessages for each user
Does something for each inputMessage
Then clears user _inputMessages*/
void Server::dispatchs(void)
{

	/*loop over users*/
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		// std::cout << "evaluation user with fd : " << itb->first << std::endl;
		//itb->second._outputMessage.clear(); elle supprime loutput msg d'user qu'on vient de modifier avant de l'envoyer
		/*loop over _inputMessages*/
		for (std::vector<std::string>::const_iterator itb2 = itb->second.getInputMessages().begin(); itb2 != itb->second.getInputMessages().end(); itb2++) // loop over
		{
			dispatch(*itb2, itb->second);
		}
		itb->second.clearInputMessages(); // all messages have been threated, clearing.
	}
}

/*Loops while user _outputMessage is not empty
sends _outputMessage buffer by buffer*/
void Server::sendMessage(void)
{

	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second.getOutputMessage().size() > 0)
			std::cout << "Sending fd: " << itb->first << " : $" << itb->second.getOutputMessage() << "$" << std::endl;

		if(send(itb->first, itb->second.getOutputMessage().c_str(), itb->second.getOutputMessage().length(), 0) == -1)
			std::cout << "Send error " << std::endl;
		// std::cout << "Finished sending User._outputMessage to fd : " << itb->first << std::endl;
		itb->second.clearOutputMessage();
	}
}

/*Will close all user fd using close()*/
Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		std::cout << "Clearing host , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
		getpeername(itb->first, (struct sockaddr *)&_sin, (socklen_t *)&_sizeofsin);
		close(itb->first);
	}
	_users.clear();
	shutdown(_masterSocket, 2); // int shutdown(int socket, int how);
}

const int &Server::getExitSignal(void)
{
	return (_exitSignal);
}

void Server::_exit_server(const std::string &message, int exitCode)
{
    std::cout << "Error: " << message << std::endl;
    exit(exitCode);
}