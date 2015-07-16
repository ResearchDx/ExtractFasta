#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"

typedef struct BedEntry
{
	std::string chrom;
	unsigned long start;
	unsigned long end;
	short strand;
	std::string region;
} BEDENTRY;

class ParseBed
{
private:
	std::string fn;
	std::fstream *fs;

	enum bed_entry {
		CHROM = 0,
		START = 1,
		END = 2,
		STRAND = 3,
		REGION = 4
	};

	unsigned int MAX_STRING_SIZE = 255;

	std::string* _ReadLine(std::fstream *fs);

	// Split bed entry string by tabs
	std::vector<std::string> _SplitByDelimiter(std::string s);

public:
	// Constructor for ParseBed
	ParseBed(std::string r);
	ParseBed();

	// Set the bed file, given the file name as a string
	void set_bed_file(std::string fn);
	BedEntry* ReadBed();

	~ParseBed();
};