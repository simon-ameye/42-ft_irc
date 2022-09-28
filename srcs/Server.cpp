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
	char buffer[42];
	int valread;
	for (std::map<int, Client>::iterator itb = _clients.begin(); itb!=_clients.end(); itb++)
	{
		if (_pollfds[itb->first].revents == POLLIN)
		{
			std::cout << "recv()" << std::endl;
			valread = recv(itb->first, buffer, 42, 0);
			if (valread == -1)
				std::cout << "error: recv()" << std::endl;
			if (valread == 0)
			{
				getpeername(itb->first, (struct sockaddr*)&_sin, (socklen_t*)&_sizeofsin); 
				std::cout << "Host disconnected , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
			}
			else
			{
				itb->second.inputBuffer = buffer;
				std::cout << "new input buffeer for fd " << itb->first << " : " << itb->second.inputBuffer << std::endl;
				send(itb->first , buffer , 42 , 0 );
			}
		}
	}
}

Server::~Server()
{
	shutdown(_masterSocket, 2); //int shutdown(int socket, int how);
}
