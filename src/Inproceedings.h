#ifndef INPROCEEDINGS_HEADER
#define INPROCEEDINGS_HEADER

#include <vector>

#include "Entry.h"

class Inproceedings : public Entry {
private:

	Inproceedings(std::vector<Field> fieldList) : Entry(EntryType::inproceedings, fieldList) {

	}

	friend class EntryFactory;

public:
};

#endif