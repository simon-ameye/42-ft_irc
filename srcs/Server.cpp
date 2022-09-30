#include "Server.hpp"

Server::Server(char *port, char *password)
{
	/*Set server parameters*/
	_exitSignal = 0;
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

/*Create the pollfds structure.
It will be used here and also in further functions
Check master socket and all clients fd with pollfds structure
If none is ready, wait (saves computer ressources)
Check the master socket
It it is ready, it means that a client is trying to connect
Thus, creates a client and give it its new fd.
This client is not set in pollfs. Thus, its fd will be read in the next loop*/
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

	/*Check masterSocket's fd to check for new connection
	Create new Client
	-->Clients are created in Server::connect
	-->Fds are created ans associated to Clients in Server::connect
	-->Eventually Clients are close() and cleared in Server::connect
	-->Any remaning Client is close() and cleared at Server destruction
	==>This guarantees that clients are closed only once*/
	if (_pollfds[0].revents == POLLIN)
	{
		/*Accepting and creating new client*/
		std::cout << "accept()" << std::endl;
		tempFd = accept(_masterSocket, (sockaddr*)&_sin, &_sizeofsin); //accept connection and get the fd
		//_clients.
		std::cout << "INSTANCING" << std::endl;
		//_clients[tempFd] = (*(new Client()));
		_clients[tempFd]; //create a client (without calling constructor twice)
		std::cout << "INSTANCING DONE" << std::endl;
		if (tempFd == -1)
			std::cout << "error: accept()" << std::endl;
	}
}

/*If client's fd is ready, get the data
And put it in client buffer and inputMessages*/
void Server::getData(void)
{
	char buffer[BUFFER_SIZE];
	int sizeRead;

	/*Output debugging data*/
	std::cout << "size of _clients : " << _clients.size() << std::endl;
	std::cout << "list of fds     : ";
	for (long unsigned int i = 0; i < _pollfds.size(); i++)
		std::cout << _pollfds[i].fd << " ";
	std::cout << std::endl;
	std::cout << "list of revents : ";
	for (long unsigned int i = 0; i < _pollfds.size(); i++)
		std::cout << _pollfds[i].revents << " ";
	std::cout << std::endl;

	/*Check if clients's fd is sending new data*/
	for (std::vector<pollfd>::iterator itb = ++_pollfds.begin(); itb!=_pollfds.end(); itb++) //skipping the master socket
	{
		if (itb->revents == POLLIN)
		{
			/*Clients fd is ready, lets read it on one buffer.*/
			std::cout << "recv()" << std::endl;
			sizeRead = recv(itb->fd, buffer, BUFFER_SIZE, 0);
			if (sizeRead == -1) //recv error
				std::cout << "error: recv()" << std::endl;
			else if (sizeRead == 0) //recv size = 0 : nothing to read anymore. Client dosconnected.
			{
				getpeername(itb->fd, (struct sockaddr*)&_sin, (socklen_t*)&_sizeofsin); 
				std::cout << "Host disconnected , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
				close(itb->fd);
				_clients.erase(itb->fd);
				std::cout << "host closed and erased" << std::endl;
			}
			else //data to read, add buffer to clients inputMessages
			{
				_clients[itb->fd].addCmdBuffer(buffer, sizeRead);
				std::cout << "new input buffer for fd " << itb->fd << " : " << _clients[itb->fd].inputBuffer << std::endl;
			}
		}
	}
}

/*Double loop : 
Loops over clients
Loops over inputMessages for each client
Does something for each inputMessage
Then clears client inputMessages*/
void Server::processData(void)
{
	/*loop over clients*/
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		std::cout << "evaluation client with fd : " << itb->first << std::endl;
		itb->second.outputBuffer.clear();
		/*loop over inputMessages*/
		for (std::vector<std::string>::iterator itb2 = itb->second.inputMessages.begin(); itb2 != itb->second.inputMessages.end(); itb2++) //loop over 
		{
			/*Example of function on each command*/
			std::cout << "Threating command : $" << *itb2 << "$" << std::endl;
			if (*itb2 == "exitServer")
			{
				_exitSignal = 1;
				itb->second.outputBuffer += "SERVER : you have asked for server shutdown\n";
			}
			else if(*itb2 == "say hello")
				itb->second.outputBuffer += "SERVER : hello\n";
			else if(*itb2 == "say yo")
				itb->second.outputBuffer += "SERVER : yo\n";
		}
		itb->second.inputMessages.clear(); //all messages have been threated, clearing.
	}
}

/*Loops while client outputBuffer is not empty
sends outputBuffer buffer by buffer*/
void Server::sendData(void)
{
	char buffer[BUFFER_SIZE];
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		std::cout << "Sending Client.outputBuffer to fd : " << itb->first << std::endl;
		while (itb->second.outputBuffer.size() > 0)
		{
			Utils::clearBuffer(buffer, BUFFER_SIZE);
			for (int i = 0; i < BUFFER_SIZE; i++)
			{
				if (itb->second.outputBuffer.size() > 0)
				{
					buffer[i] = itb->second.outputBuffer[0];
					itb->second.outputBuffer.erase(0, 1);
				}
			}
			send(itb->first , buffer , BUFFER_SIZE , 0 );
		}
		std::cout << "Finished sending Client.outputBuffer to fd : " << itb->first << std::endl;
	}
}

/*Will close all client fd using close()*/
Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		std::cout << "Clearing host , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
		getpeername(itb->first, (struct sockaddr*)&_sin, (socklen_t*)&_sizeofsin);
		close(itb->first);
	}

	_clients.clear();
	shutdown(_masterSocket, 2); //int shutdown(int socket, int how);
}

const int &Server::getExitSignal(void)
{
	return (_exitSignal);
}