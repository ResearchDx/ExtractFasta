#include "stdafx.h"
#include "AlignmentReferenceManager.h"


AlignmentReferenceManager::AlignmentReferenceManager()
{
}

void AlignmentReferenceManager::set_bed_file(std::string fn)
{
	this->_BedParser = new ParseBed(fn);
}

void AlignmentReferenceManager::set_reference_file(std::string fn)
{
	this->_Reference = new Reference(fn);
}

void AlignmentReferenceManager::extract_fasta(std::string out_fn)
{
	std::FILE *out;
	fopen_s(&out, out_fn.c_str(), "w");
	this->_Reference->ReadIndex();
	while (true)
	{
		BedEntry *be = this->_BedParser->ReadBed();
		if (be == NULL)
		{
			delete(be);
			break;
		}

		std::string fasta_header;
		std::string fasta;

		fasta_header = ">" + be->chrom + ":" + std::to_string(be->start) + ":" + std::to_string(be->end);
		fasta = this->_Reference->Query(be->chrom, be->start, be->end);

		std::fputs(fasta_header.c_str(), out);
		std::fputs("\n", out);

		// this will work as long as the bed file provided extends beyond the capture region (insert size)
		while (fasta.size() > 80)
		{
			std::fputs(fasta.substr(0, 80).c_str(), out);
			std::fputs("\n", out);
			fasta = fasta.substr(80, fasta.size() - 80);

		}

		if (fasta.size() > 0)
		{
			std::fputs(fasta.substr(0, 80).c_str(), out);
			std::fputs("\n", out);
		}
		// free from memory once complete
		delete(be);
	}

	std::fflush(out);
	std::fclose(out);
}



AlignmentReferenceManager::~AlignmentReferenceManager()
{
}
