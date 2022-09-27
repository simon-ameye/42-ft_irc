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
	if(_sock == -1)
		std::cout << "error: socket()" << std::endl;

	/*Setting socket reuse*/
	int enable = 1; //pas compris encore
	if (setsockopt(_masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)) == -1)
		std::cout << "error: setsockopt()" << std::endl;

	/*Setting socket to be non blocking*/
	if (fcntl(_masterSocket, F_SETFL, O_NONBLOCK) == -1)
		std::cout << "error: fcntl()" << std::endl;

	/*Binding socket to port and set socket settings*/
	std::cout << "bind()" << std::endl;
	if (bind(_masterSocket, (sockaddr*)&_sin, _sizeofsin) == -1) //int bind(int socket, const struct sockaddr* addr, socklen_t addrlen)
		std::cout << "error: bind()" << std::endl;

	/*Listening*/
	std::cout << "listen()" << std::endl;
	if (listen(_sock, 5) == -1) //int listen(int socket, int backlog)
		std::cout << "error: listen()" << std::endl;
}

void Server::connect(void)
{
	pollfd tempfd;
	std::vector<pollfd> pollfds;

	/*Add masterSocket to pollfds*/
	tempfd.fd = _masterSocket;
	tempfd.events = POLLIN;
	pollfds.push_back(tempfd);

	/*Add all the clients sockets to pollfds*/
	for (std::vector<Client>::iterator itb = _clients.begin(); itb != _clients.end(); itb++)
	{
		tempfd.fd = _masterSocket;
		tempfd.events = POLLIN;
		pollfds.push_back(tempfd);
	}

	/*wait for an avent*/
	std::cout << "poll()" << std::endl;
	if (poll(&pollfds[0], pollfds.size(), (300 * 1000) / 10) == -1) // BLOCKS untill a fd is available + set max ping to 300s
		std::cout << "error: poll()" << std::endl;

	/*Check masterSocket's fd to check for new connection*/
	if (pollfds[0].revents == POLLIN)
	{
		/*Accepting and creating new client*/
		std::cout << "accept()" << std::endl;
		_clients.push_back(*(new Client()));
		_clients.back()._sock = accept(_sock, (sockaddr*)&_sin, &_sizeofsin); //int accept(int socket, struct sockaddr* addr, socklen_t* addrlen)
		if (_clients.back()._sock == -1)
			std::cout << "error: listen()" << std::endl;
	}

}









	while (1)
	{

		//if (pfds[0].revents == POLLIN)


		/*Recieving*/
		char buffer[32] = "";
		std::cout << "recv()" << std::endl;
		if (recv(client._sock, buffer, sizeof(buffer), 0) == -1)
			std::cout << "error: recv()" << std::endl;

		printf("Recu : %s\n", buffer);

		sleep(1);
	}
}

Server::~Server()
{
	shutdown(_sock, 2); //int shutdown(int socket, int how);
}
