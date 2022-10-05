#include "Utils.hpp"

void Utils::clearBuffer(char *buffer, int size)
{
	for (int i = 0; i < size; i++)
		buffer[i] = '\0';
}

std::vector<std::string> Utils::split_cmd(std::string str, char delimiter)
{
	size_t pos = 0;
	std::vector<std::string> result;
	pos = str.find(delimiter);
	if (pos < 0)
	{
		result.push_back("");
		result.push_back("");
	}
	result.push_back(str.substr(0, pos));
	result.push_back(str.substr(pos + 1, str.size() - pos - 1));
	return result;
}


std::vector<std::string> Utils::split(std::string s, char delimiter)
{
	std::vector<std::string> result;
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		s.erase(0, pos + 1);
		result.push_back(token);
	}
	if (s.size() > 0)
		result.push_back(s);

	return result;
}