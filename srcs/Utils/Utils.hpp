#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

class Utils
{
	public:
	static void clearBuffer(char *buffer, int size);
	static std::vector<std::string> split(std::string s, char delimiter);
};

#endif