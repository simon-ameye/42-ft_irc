#include "Server.hpp"

Server::Server(char *port, char *password)
{
	Client client;

	/*Set server parameters*/
	_port = atoi(port);
	_password = password;
	std::cout << "Server starting on port " << _port << " with password " << _password << std::endl;

	/*Defining server sockaddr_in structure*/
	_sin.sin_port = htons(_port); //set port
	_sin.sin_addr.s_addr = htonl(INADDR_ANY); //set IP address automatically
	_sin.sin_family = AF_INET;

	/*Defining server sockaddr_in structure size*/
	_sizeofsin = sizeof(_sin);

	/*Creating socket*/
	std::cout << "socket()" << std::endl;
	_masterSocket = socket(AF_INET, SOCK_STREAM, 0); //int socket(int domain, int type, int protocol), AF_INET=TCP/IP, SOCK_STREAM=TCP/IP
	if(_masterSocket == -1)
		std::cout << "error: socket()" << std::endl;

	/*Setting socket reuse*/
	std::cout << "setsockopt()" << std::endl;
	int enable = 1; //pas compris encore
	if (setsockopt(_masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)) == -1)
		std::cout << "error: setsockopt()" << std::endl;

	/*Setting socket to be non blocking*/
	std::cout << "fcntl()" << std::endl;
	if (fcntl(_masterSocket, F_SETFL, O_NONBLOCK) == -1)
		std::cout << "error: fcntl()" << std::endl;

	/*Binding socket to port and set socket settings*/
	std::cout << "bind()" << std::endl;
	if (bind(_masterSocket, (sockaddr*)&_sin, _sizeofsin) == -1) //int bind(int socket, const struct sockaddr* addr, socklen_t addrlen)
		std::cout << "error: bind()" << std::endl;

	/*Listening*/
	std::cout << "listen()" << std::endl;
	if (listen(_masterSocket, 5) == -1) //int listen(int socket, int backlog)
		std::cout << "error: listen()" << std::endl;
}

void Server::connect(void)
{
	int tempFd;
	pollfd tempPollFd;

	_pollfds.clear();

	/*Add masterSocket to pollfds*/
	tempPollFd.fd = _masterSocket;
	tempPollFd.events = POLLIN;
	_pollfds.push_back(tempPollFd);

	/*Add all the clients sockets to pollfds*/
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		tempPollFd.fd = itb->first;
		_pollfds.push_back(tempPollFd);
	}

	/*wait for an event*/
	std::cout << "poll()" << std::endl;
	if (poll(&(_pollfds[0]), _pollfds.size(), 30000) == -1) // BLOCKS untill a fd is available + set max ping to 300s
		std::cout << "error: poll()" << std::endl;

	/*Check masterSocket's fd to check for new connection*/
	if (_pollfds[0].revents == POLLIN)
	{
		/*Accepting and creating new client*/
		std::cout << "accept()" << std::endl;
		tempFd = accept(_masterSocket, (sockaddr*)&_sin, &_sizeofsin);
		_clients[tempFd] = (*(new Client()));
		if (tempFd == -1)
			std::cout << "error: accept()" << std::endl;
	}
}

void Server::getData(void)
{
	/*Check clients's fd for new data*/
	char buffer[BUFFER_SIZE];
	int sizeRead;
	std::cout << "list of fds     : ";
	for (long unsigned int i = 0; i < _pollfds.size(); i++)
		std::cout << _pollfds[i].fd << " ";
	std::cout << std::endl;
	std::cout << "list of revents : ";
	for (long unsigned int i = 0; i < _pollfds.size(); i++)
		std::cout << _pollfds[i].revents << " ";
	std::cout << std::endl;

	for (std::vector<pollfd>::iterator itb = ++_pollfds.begin(); itb!=_pollfds.end(); itb++) //skipping the master socket
	{
		//std::cout << "itb->first" << itb->first << std::endl;
		//std::cout << "_pollfds[itb->first].fd" << _pollfds[itb->first].fd << std::endl;
		//std::cout << "_pollfds[itb->first].revents" << _pollfds[itb->first].revents << std::endl;
		if (itb->revents == POLLIN)
		{
			std::cout << "recv()" << std::endl;

			sizeRead = recv(itb->fd, buffer, BUFFER_SIZE, 0);
			if (sizeRead == -1)
				std::cout << "error: recv()" << std::endl;
			if (sizeRead == 0)
			{
				getpeername(itb->fd, (struct sockaddr*)&_sin, (socklen_t*)&_sizeofsin); 
				std::cout << "Host disconnected , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
			}
			else
			{
				_clients[itb->fd].addCmdBuffer(buffer, sizeRead);
				std::cout << "new input buffer for fd " << itb->fd << " : " << _clients[itb->fd].inputBuffer << std::endl;
				//send(itb->fd , buffer , sizeof(buffer) , 0 );
			}
		}
	}
}

void Server::processData(void)
{
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		std::cout << "evaluation client with fd : " << itb->first << std::endl;
		for (std::vector<std::string>::iterator itb2 = itb->second.inputMessages.begin(); itb2 != itb->second.inputMessages.end(); itb2++)
		{
			std::cout << "command found : " << *itb2 << std::endl;
		}
		if (itb->second.inputMessages.size() > 0)
			itb->second.outputBuffer = "You have more than 1 message pending. Your first message was : " + itb->second.inputMessages[0] + "\n";
	}
}

void Server::sendData(void) //loops untils all the outputBuffer is sent
{
	char buffer[BUFFER_SIZE];
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		std::cout << "sending a message to client with fd : " << itb->first << std::endl;
		while (itb->second.outputBuffer.size() > 0)
		{
			for (int i = 0; i < BUFFER_SIZE; i++)
			{
				if (itb->second.outputBuffer.size() > 0)
				{
					buffer[i] = itb->second.outputBuffer[0];
					itb->second.outputBuffer.erase(0, 1);
				}
			}
			send(itb->first , buffer , sizeof(buffer) , 0 );
		}
	}
}

Server::~Server()
{
	shutdown(_masterSocket, 2); //int shutdown(int socket, int how);
}
