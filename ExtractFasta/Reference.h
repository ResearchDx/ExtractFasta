#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <stdint.h>
#include <cstdlib>

class Reference
{
	//Load up the reference fastq file and grab the reference sequence
	//given the ref, start, and end positions

private:
	std::string fn;
	std::string faidx_fn;
	std::map<std::string, std::vector<const char*>> *faidx;
	bool faidx_set = false;

	enum faindex {
		REF = 0,
		BASES = 1,
		BYTE = 2,
		LEN = 3,
		BLEN = 4
	};

	uint32_t _GetOffset(std::vector<const char*> *index, uint32_t *pos);
	char Reference::_ReadByte(std::fstream *fs);
	std::string _ReadLine(std::fstream *fs);
	std::vector<const char*> _SplitStringBy(std::string s, char delimiter);

public:
	// Constructor for reference
	Reference();
	Reference(std::string r);

	// Set the reference file names for later use
	void set_reference_file(std::string fn);

	void ReadIndex();
	std::string Query(std::string c, uint32_t start, uint32_t end);

	std::string GetFn();

	Reference::~Reference();
};