#include "stdafx.h"
#include "Reference.h"


Reference::Reference(std::string ref_fn)
{
	this->set_reference_file(ref_fn);
}

void Reference::set_reference_file(std::string fn)
{
	this->fn = fn;
	this->faidx_fn = fn + ".fai";
}

void Reference::ReadIndex()
{
	std::fstream fs;
	fs.open(this->faidx_fn, std::ios::in);

	this->faidx = new std::map<std::string, std::vector<const char*>>;
	this->faidx_set = true;
	std::string line = this->_ReadLine(&fs);
	while (fs.eof() == false)
	{
		std::vector<const char*> t_list = this->_SplitStringBy(line, '\t');
		(*(this->faidx))[t_list[REF]] = t_list;
		line = this->_ReadLine(&fs);
	}
}

std::string Reference::GetFn()
{
	return this->fn;
}

std::string Reference::Query(std::string c, uint32_t start, uint32_t end)
{
	std::vector<const char*> index = (*(this->faidx))[c];
	//std::cout << index[REF] << "\t" << index[BASES] << std::endl;

	std::fstream fs;
	fs.open(this->fn, std::ios::in);

	// subtract two if the from the start offset to make it inclusive
	// when it fetches from the start of a line, otherwise subtract only
	// 1 and add 1 to the end of a line
	uint32_t start_offset = this->_GetOffset(&index, &start) - 1;
	uint32_t end_offset = this->_GetOffset(&index, &end);


	//printf("start offset: %lu\n", start_offset);
	//printf("end offset: %lu\n", end_offset);

	std::string line;
	fs.seekg(start_offset);
	while (line.size() <= (end - start))
	{
		line += this->_ReadByte(&fs);
	}
	return line;
}

uint32_t Reference::_GetOffset(std::vector<const char*> *index, uint32_t *pos)
{
	// Return the byte corresponding to the start of the line
	// where the region of interest was
	uint32_t ref_start = std::stoul((*index)[BYTE]);
	uint32_t line_offset = *pos / std::stoi((*index)[LEN]);
	uint8_t base_offset = *pos % std::stoi((*index)[LEN]);

	ref_start = ref_start + (line_offset * std::stoi((*index)[BLEN]));
	ref_start += base_offset;

	// if the start or end occurs at the start or end of a line we subtract
	// one from to to account for the newline character
	if (base_offset == 0)
		ref_start -= 1;
	return ref_start;
}

char Reference::_ReadByte(std::fstream *fs)
{
	char base[2];
	base[1] = '\0';

	if (!fs->eof())
	{
		fs->read(base, 1);
		base[1] = '\0';
		while (std::strcmp(base, "\n\0") == 0)
		{
			fs->read(base, 1);
			base[1] = '\0';
			if (fs->eof())
			{
				base[0] = '\0';
				break;
			}
		}
	}

	return base[0];
}

std::string Reference::_ReadLine(std::fstream *fs)
{
	// Return a line of text from the file stream
	std::string line;
	char buf[2];

	buf[1] = '\0';
	while (std::strcmp(buf, "\n\0") != 0)
	{
		fs->read(buf, 1);
		line += buf;
		buf[1] = '\0';
		if (fs->eof())
			break;
	}
	return line;
}

std::vector<const char*> Reference::_SplitStringBy(std::string s, char delimiter)
{
	// Return a vector with each entry in the fasta index
	std::string *token = new std::string();
	std::vector<const char*> token_list;
	for (int index = 0; index < s.length(); index++)
	{
		if (s[index] == delimiter)
		{
			token_list.push_back((*token).c_str());
			token = new std::string();
		}
		else if (index == (s.length() - 1))
		{
			token_list.push_back((*token).c_str());
			token = new std::string();
		}
		else
		{
			*token += s[index];
		}
	}
	return token_list;
}


Reference::~Reference()
{
	if (this->faidx_set)
		delete this->faidx;
}
