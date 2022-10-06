#include "Server.hpp"
#include <stdio.h>
#include <stdlib.h>

Server::Server(char *port, char *password)
{
	/*Set server parameters*/
	_serverName = "ft_irc";
	_exitSignal = 0;
	_port = atoi(port);
	_password = password;
	std::cout << "Server starting on port " << _port << " with password " << _password << std::endl;

	/*Defining server sockaddr_in structure*/
	// set port
	if (!isdigit(htons(_port))) //checker si le port est un nombre ? 
	{
		std::cout << "Invalid port" << std::endl;
		exit (-1);
	}
	else
		_sin.sin_port = htons(_port); // utilite htons ?			  
	
	_sin.sin_addr.s_addr = htonl(INADDR_ANY); // set IP address automatically
	_sin.sin_family = AF_INET;

	/*Defining server sockaddr_in structure size*/
	_sizeofsin = sizeof(_sin);

	/*Creating socket*/
	//std::cout << "socket()" << std::endl;
	_masterSocket = socket(AF_INET, SOCK_STREAM, 0); // int socket(int domain, int type, int protocol), AF_INET=TCP/IP, SOCK_STREAM=TCP/IP
	if (_masterSocket == -1)
	{
		std::cout << "error: socket()" << std::endl;
		exit (-1);
	}

	/*Setting socket reuse*/
	//std::cout << "setsockopt()" << std::endl;
	int enable = 1; // pas compris encore
	if (setsockopt(_masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)) == -1)
	{
		std::cout << "error: setsockopt()" << std::endl;
		exit (-1);
	}
	/*Setting socket to be non blocking*/
	//std::cout << "fcntl()" << std::endl;
	if (fcntl(_masterSocket, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "error: fcntl()" << std::endl;
		exit (-1);
	}	

	/*Binding socket to port and set socket settings*/
	//std::cout << "bind()" << std::endl;
	if (bind(_masterSocket, (sockaddr *)&_sin, _sizeofsin) == -1) // int bind(int socket, const struct sockaddr* addr, socklen_t addrlen)
	{
		std::cout << "error: bind()" << std::endl;
		exit (-1);
	}
	/*Listening*/
	//std::cout << "listen()" << std::endl;
	if (listen(_masterSocket, 5) == -1) // int listen(int socket, int backlog)
	{
		std::cout << "error: listen()" << std::endl;
		exit (-1);
	}
}

/*Create the pollfds structure.
It will be used here and also in further functions
Check master socket and all users fd with pollfds structure
If none is ready, wait (saves computer ressources)
Check the master socket
It it is ready, it means that a user is trying to connect
Thus, creates a user and give it its new fd.
This user is not set in pollfs. Thus, its fd will be read in the next loop*/
void Server::connect(void)
{
	std::cout << "---------- ICI 0 ---------" << std::endl;

	int tempFd;
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
	if (poll(&(_pollfds[0]), _pollfds.size(), 300000) == -1) // BLOCKS untill a fd is available + set max ping to 300s
	{
		std::cout << "error: poll()" << std::endl; //le time est-il bon ?
		exit (-1);
	}

	/*Check masterSocket's fd to check for new connection
	Create new User
	-->Users are created in Server::connect
	-->Fds are created ans associated to Users in Server::connect
	-->Eventually Users are close() and cleared in Server::connect
	-->Any remaning User is close() and cleared at Server destruction
	==>This guarantees that users are closed only once*/
	if (_pollfds[0].revents == POLLIN)
	{
		/*Accepting and creating new user*/
		//std::cout << "accept()" << std::endl;
		tempFd = accept(_masterSocket, (sockaddr *)&_sin, &_sizeofsin); // accept connection and get the fd
		_users[tempFd];													// create a user (without calling constructor twice)
		if (tempFd == -1)
		{
			std::cout << "error: accept()" << std::endl;
			exit (-1);
		}
		std::cout << "New user accepted with fd: " << tempFd << std::endl;
	}
}

/*If user's fd is ready, get the data
And put it in user buffer and _inputMessages*/
void Server::getMessages(void)
{
	std::cout << "---------- ICI 1 ---------" << std::endl;

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
			{
				std::cout << "error: recv()" << std::endl;
				exit (-1);
			}
			else if (sizeRead == 0) // recv size = 0 : nothing to read anymore. User dosconnected.
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
				// std::cout << "new input buffer for fd " << itb->fd << " : " << _users[itb->fd]._inputMessagesBuffer << std::endl;
			}
		}
	}
}

/*Double loop :
Loops over users
Loops over _inputMessages for each user
Does something for each inputMessage
Then clears user _inputMessages*/
void Server::processMessages(void)
{
	std::cout << "---------- ICI 2 ---------" << std::endl;

	/*loop over users*/
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		// std::cout << "evaluation user with fd : " << itb->first << std::endl;
		itb->second._outputMessage.clear();
		/*loop over _inputMessages*/
		for (std::vector<std::string>::iterator itb2 = itb->second._inputMessages.begin(); itb2 != itb->second._inputMessages.end(); itb2++) // loop over
		{
			processMessage(*itb2, itb->second);
		}
		itb->second._inputMessages.clear(); // all messages have been threated, clearing.
	}
}

/*Loops while user _outputMessage is not empty
sends _outputMessage buffer by buffer*/
void Server::sendMessage(void)
{
	std::cout << "---------- ICI 3 ---------" << std::endl;
	for (std::map<int, User>::iterator itb = _users.begin(); itb != _users.end(); itb++)
	{
		if (itb->second._outputMessage.size() > 0)
			std::cout << "Sending fd: " << itb->first << " : $" << itb->second._outputMessage << "$" << std::endl;

		if(send(itb->first, itb->second._outputMessage.c_str(), itb->second._outputMessage.length(), 0) == -1)
			std::cout << "Send error " << std::endl; 
		// std::cout << "Finished sending User._outputMessage to fd : " << itb->first << std::endl;
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

void Server::processMessage(std::string &message, User &user)
{
	std::cout << "Processing command : $" << message << "$" << std::endl;

	//std::vector<std::string> args;
	std::vector<std::string> splitCmd;
	//std::string cmd;
	//std::string args;

	splitCmd = Utils::split_cmd(message, ' ');
	//std::cout << "split cmd res[0] : $" << splitCmd[0] << "$" << std::endl;
	//std::cout << "split cmd res[1] : $" << splitCmd[1] << "$" << std::endl;

	//args = Utils::split(message, ' ');
	/*
		if (args.size() == 0)
		{
			std::cout << "empty token" << std::endl;
			return ;
		}
	*/
	//cmd = splitCmd[0];
	//args.erase(args.begin());
	//args = splitCmd[1];

	if (splitCmd[0] == "")
		std::cout << "empty cmd" << std::endl;
	else if (splitCmd[0] == "NICK")
		_nick(splitCmd[1], user);
	else if (splitCmd[0] == "PASS")
		_pass(splitCmd[1], user);
	else if (splitCmd[0] == "PING")
		_ping(splitCmd[1], user); // NEW
	else if (splitCmd[0] == "OPER")
		_oper(splitCmd[1], user);
	else if (splitCmd[0] == "USER")
		_user(splitCmd[1], user);
	else if (splitCmd[0] == "PRIVMSG")
		_privmsg(splitCmd[1], user);
	else if (splitCmd[0] == "sayHello")
		user._outputMessage += "SERVER : hello\n";
	else if (splitCmd[0] == "exitServer")
	{
		_exitSignal = 1;
		user._outputMessage += "SERVER : you have asked for server shutdown";
		user._outputMessage += DELIMITER;
	}
	else
	{
		Channel channel; //useless, just used to pass to _errorReplies
		_errorReplies(user, ERR_UNKNOWNCOMMAND, splitCmd[0], channel);
	}
}
