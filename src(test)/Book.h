#ifndef BOOK_HEADER
#define BOOK_HEADER

#include <vector>

#include "Entry.h"

class Book : public Entry {
private:
	//static std::vector<FieldName> reqField;
	//static std::vector<FieldName> optField;

	Book(std::vector<Field> fieldList) : Entry(EntryType::book, fieldList) {

	}

	friend class EntryFactory;

public:
};

#endif