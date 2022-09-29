#include "Utils.hpp"

int Utils::stringIsTerminated(std::string str)
{
	if (str.size() < 1)
		return (0);
	return (str[str.size() - 1] == '\0');
}
