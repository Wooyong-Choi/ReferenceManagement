#ifndef ARTICLE_HEADER
#define ARTICLE_HEADER

#include <vector>

#include "Entry.h"

class Article : public Entry {
private:
	//static std::vector<FieldName> reqField;
	//static std::vector<FieldName> optField;

	Article(std::vector<Field> fieldList) : Entry(EntryType::article, fieldList) {
		this->fieldList = fieldList;  // automatic deep copy
	}

	friend class EntryFactory;


public:
};

#endif