#include "../Server.hpp"

void Server::_mode(std::string args, User &user)
{
	(void) user;

	if (!user.getIsPassProvided())
		return;
	if (user.getNickName() == "*")
		return;

	std::vector<std::string> data;
	data = Utils::split(args, ' ');
//	std::vector<std::string>::iterator itb;
	if (data.size() >= 2) // name +i // +b channel
	{
		std::string param1;
		param1 = Utils::split(args, ' ')[0];
		//std::cout << "------> param1 = " <<  param1 << std::endl;

		std::string param2;
		param2 = args.substr(param1.size(), args.size());
		//std::cout << "------> param2 = " <<  param2 << std::endl;

		if (param2.compare("+i"))
		{
			//std::cout << "====> invit" <<  std::endl;
		}
		else
		{

		}
	}
}