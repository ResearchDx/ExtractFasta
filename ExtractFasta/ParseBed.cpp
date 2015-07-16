#include "stdafx.h"
#include "ParseBed.h"

ParseBed::ParseBed()
{
}


ParseBed::ParseBed(std::string r)
{
	this->set_bed_file(r);
}


void ParseBed::set_bed_file(std::string fn)
{
	this->fn = fn;
	this->fs = new std::fstream;
	(*this->fs).open(this->fn, std::ios::in);
}

BedEntry* ParseBed::ReadBed()
{
	std::string *line;
	line = this->_ReadLine(this->fs);

	if (line == NULL)
		return NULL;

	std::vector<std::string> data = utils::_SplitByDelimiter(*line, '\t');
	BedEntry *e = new BedEntry();
	e->strand = 0;
	e->chrom = data[CHROM];
	e->start = std::atol(data[START].c_str());
	e->end = std::atol(data[END].c_str());

	if (data[STRAND] == "+")
		e->strand = 1;
	else
		e->strand = -1;

	e->region = data[REGION];

	delete(line);

	return e;
}

std::string* ParseBed::_ReadLine(std::fstream *fs)
{
	std::string *line = new std::string();
	char base[2];
	base[1] = '\0';

	if (!fs->eof())
	{
		fs->read(base, 1);
		while (base[0] != '\n')
		{
			*line += base;
			fs->read(base, 1);
			if (fs->eof())
			{
				break;
			}
		}
	}
	else
	{
		return NULL;
	}
	return line;
}

std::vector<std::string> ParseBed::_SplitByDelimiter(std::string s)
{
	std::string entry;
	std::vector<std::string> result;
	for (std::string::iterator siter = s.begin(); siter != s.end(); siter++)
	{
		if (*siter != '\t')
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

ParseBed::~ParseBed()
{
}
