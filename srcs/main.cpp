#include "Server.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "ircserv needs 3 arguments" << std::endl;
		return 1;
	}
	Server server;
	server.setPort(argv[1]);
	server.setPassword(argv[2]);
}