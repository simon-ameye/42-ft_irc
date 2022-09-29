#include "Server.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return 1;
	}
	Server server(argv[1], argv[2]);
	while (1)
	{
		server.connect();
		server.getData();
		server.processData();
		server.sendData();
		sleep(1);
	}
}