#include "stdafx.h"
#include "utils.h"


utils::utils()
{
}

std::vector<std::string> utils::_SplitByDelimiter(std::string s, char delimiter)
{
	std::string entry;
	std::vector<std::string> result;
	for (std::string::iterator siter = s.begin(); siter != s.end(); siter++)
	{
		if (*siter != delimiter)
			entry += *siter;
		else
		{
			result.push_back(entry);
			entry.clear();
		}

		if ((siter + 1) == s.end())
		{
			result.push_back(entry);
			entry.clear();
		}
	}
	return result;
}

utils::~utils()
{
}
