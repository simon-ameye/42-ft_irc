#include "Server.hpp"

Server::Server()
{
	sockaddr_in sin; //srtuct used to set socket options

	sock = socket(AF_INET, SOCK_STREAM, 0); //int socket(int domain, int type, int protocol), AF_INET=TCP/IP, SOCK_STREAM=TCP/IP

	sin.sin_port = htons(port); //set port
	sin.sin_addr.s_addr = htonl(INADDR_ANY); //set IP address automatically
	sin.sin_family = AF_INET;

	/*
	bind(sock, (sockaddr*)&sin, sizeof(sin)); //int bind(int socket, const struct sockaddr* addr, socklen_t addrlen)
	listen(sock, 5); //int listen(int socket, int backlog)
	csock = accept(sock, (SOCKADDR*)&csin, &(sizeof(csin)));
	int closesocket(int sock);
	HANDLE ERRORS
	*/


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
