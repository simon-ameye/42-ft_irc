#include "Server.hpp"
#include <stdio.h>
#include <stdlib.h>

Server::Server(char *port, char *password)
{
	// Set server parameters
	_serverName = "ft_irc";
	_exitSignal = 0;
	_password = password;
	_restartNeeded = false;

	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(atoi(port));
	_sin.sin_addr.s_addr = htonl(INADDR_ANY); // set IP address automatically

	if (_sin.sin_port == 0)
		_exit_server("invalid port", -1);

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

	std::cout << "Server starting on port " << ntohs(_sin.sin_port) << " with password " << _password << std::endl;
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
	pollfd tempPollFd;

	_pollfds.clear();

	// Add masterSocket to pollfds
	tempPollFd.fd = _masterSocket;
	tempPollFd.events = POLLIN;
	_pollfds.push_back(tempPollFd);

	// Add all the users sockets to pollfds
	for (std::vector<User>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		tempPollFd.fd = it->getFd();
		_pollfds.push_back(tempPollFd);
	}

	// wait for an event
	if (poll(&(_pollfds[0]), _pollfds.size(), POLL_TIMEOUT) == -1)
		_exit_server("poll()", -1);
}

void Server::getNewUsers(void)
{
	int tempFd;

	if (_pollfds[0].revents == POLLIN)
	{
		// Accept and create a new user
		tempFd = accept(_masterSocket, (sockaddr *)&_sin, &_sizeofsin);
		if (tempFd == -1)
			_exit_server("accept()", -1);
		//_users[tempFd];
		_users.push_back(User(tempFd));
		std::cout << "New user accepted with fd: " << tempFd << std::endl;
	}
}

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

	// Check if user's fd is sending new data
	for (std::vector<pollfd>::iterator it = ++_pollfds.begin(), ite = _pollfds.end(); it != ite; it++) // skipping the master socket
	{
		if (it->revents == POLLIN)
		{
			// Users fd is ready, lets read it on one buffer
			Utils::clearBuffer(buffer, BUFFER_SIZE);

			sizeRead = recv(it->fd, buffer, BUFFER_SIZE, 0);

			// recv() error
			if (sizeRead == -1)
				_exit_server("recv()", -1);

			// Nothing to read anymore: user disconnected
			if (sizeRead == 0)
			{
				getpeername(it->fd, (struct sockaddr *)&_sin, (socklen_t *)&_sizeofsin);
				std::cout << "Host disconnected , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
				close(it->fd);
				_users.erase(getUserItByFd(it->fd));
				std::cout << "host closed and erased" << std::endl;
			}

			// Something to read: add buffer to users _inputMessages
			else
				getUserItByFd(it->fd)->addBufferToMessages(buffer, sizeRead);
		}
	}
}

void Server::dispatchs(void)
{
	// Loop over users
	for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
	{
		// std::cout << "evaluation user with fd : " << it->first << std::endl;
		// it->second._outputMessage.clear(); elle supprime loutput msg d'user qu'on vient de modifier avant de l'envoyer

		// Loop over _inputMessages
		for (std::vector<std::string>::const_iterator cit = it->getInputMessages().begin(), cite = it->getInputMessages().end(); cit != cite; cit++)
			dispatch(*cit, *it);

		// All messages have been threated, clearing.
		it->clearInputMessages();
	}
}

/*Loops while user _outputMessage is not empty
sends _outputMessage buffer by buffer*/
void Server::sendMessage(void)
{
	for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
	{
		if (it->getOutputMessage().size() > 0)
			std::cout << it->getFullClientIdentifier() << " : $" << GREEN << it->getOutputMessage() << RESET << "$" << std::endl;

		if (send(it->getFd(), it->getOutputMessage().c_str(), it->getOutputMessage().length(), 0) == -1)
			std::cout << "Send error " << std::endl;

		it->clearOutputMessage();
	}
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;

	// close() all users fds
	for (std::vector<User>::iterator it = _users.begin(), ite = _users.end(); it != ite; it++)
	{
		std::cout << "Clearing host , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
		getpeername(it->getFd(), (struct sockaddr *)&_sin, (socklen_t *)&_sizeofsin);
		close(it->getFd());
	}
	_users.clear();
	shutdown(_masterSocket, SHUT_RDWR);
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

void Server::clean()
{
	std::vector<User>::iterator it = _users.begin();

	while (it != _users.end())
	{
		if (it->getIsRegistered() && it->getIsDeleted())
		{
			close(it->getFd());
			it = _users.erase(it);
		}
		else
			it++;
	}
}

Config &Server::getConfig()
{
	return _confg;
}

void Server::refreshConfig()
{
	_confg = Config();
}

bool Server::getRestartNeeded() { return _restartNeeded; }
void Server::setRestartNeeded(bool restartNeeded) { _restartNeeded = restartNeeded; }