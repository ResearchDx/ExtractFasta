#include <vector>
#include <string>

#ifndef EXTRACT_FASTA_UTILS_H
#define EXTRACT_FASTA_UTILS_H
class utils
{
public:
	utils();
	// Split bed entry string by delimiter d
	static std::vector<std::string> _SplitByDelimiter(std::string s, char d);

	~utils();
};
#endif
