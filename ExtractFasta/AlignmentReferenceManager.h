
#include <string>
#include <stdio.h>
#include "ParseBed.h"
#include "Reference.h"

class AlignmentReferenceManager
{
private:
	ParseBed *_BedParser;
	Reference *_Reference;


public:
	AlignmentReferenceManager();

	void set_bed_file(std::string fn);
	void set_reference_file(std::string fn);

	void extract_fasta(std::string out_fn);


	virtual ~AlignmentReferenceManager();
};

