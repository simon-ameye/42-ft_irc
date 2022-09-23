#include "Server.hpp"

Server::Server()
{
	Client client;

	/*Defining server sockaddr_in structure*/
	_sin.sin_port = htons(_port); //set port
	_sin.sin_addr.s_addr = htonl(INADDR_ANY); //set IP address automatically
	_sin.sin_family = AF_INET;

	/*Defining server sockaddr_in structure size*/
	_sizeofsin = sizeof(_sin);

	_sock = socket(AF_INET, SOCK_STREAM, 0); //int socket(int domain, int type, int protocol), AF_INET=TCP/IP, SOCK_STREAM=TCP/IP

	bind(_sock, (sockaddr*)&_sin, _sizeofsin); //int bind(int socket, const struct sockaddr* addr, socklen_t addrlen)

	listen(_sock, 5); //int listen(int socket, int backlog)
	client.setSock(accept(_sock, (sockaddr*)&client._sin, &client._sizeofsin)); //int accept(int socket, struct sockaddr* addr, socklen_t* addrlen)
	int closesocket(int sock);
	HANDLE ERRORS
	


}

Server::~Server()
{

}

void Server::setPort(char *str)
{
	port = atoi(str);
}

void Server::setPassword(char *str)
{
	password = str;
}
