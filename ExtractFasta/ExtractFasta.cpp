// ExtractFasta.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AlignmentReferenceManager.h"
#include <iostream>
#include <string.h>
#include <direct.h>
#include "utils.h"

//#define DEBUG

void PrintHelp()
{
	printf("Extract Fasta\n");
	printf("Extract the corresponding fasta sequence given a bed file");
	printf("Version: 0.1.0 by Michael Ta");
	printf("Usage: ExtractFasta /path/to/reference.fa /path/to/region.bed");
	printf("\n");

}


std::string GetFileName(std::string fn)
{
	std::vector<std::string> basenames = utils::_SplitByDelimiter(fn, '/');
	return basenames[basenames.size() - 1];
}

int main(int argc, char* argv[])
{
	std::string args = *argv;

#ifndef DEBUG
	if ((argv[1] == NULL) || (argv[2] == NULL))
	{
		PrintHelp();
		return 0;
	}

	std::string ref_fn = argv[1];
	std::string bed_fn = argv[2];
#endif
#ifdef DEBUG
	std::string ref_fn = "/path/to/reference.fa";
	std::string bed_fn = "/path/to/regions.bed";
#endif
	char CurrentDir[FILENAME_MAX];
	std::string cwd = _getcwd(CurrentDir, sizeof(CurrentDir));
	std::string out_fn = cwd + "/" + GetFileName(bed_fn) + ".fasta";

	AlignmentReferenceManager ref_ex = AlignmentReferenceManager::AlignmentReferenceManager();

	ref_ex.set_bed_file(bed_fn);
	ref_ex.set_reference_file(ref_fn);

	ref_ex.extract_fasta(out_fn);
	return 0;
}

