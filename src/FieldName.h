#ifndef FIELDNAME_HEADER
#define FIELDNAME_HEADER

#include <string>

enum class FieldName
{
	author,  // author, editor 예외 처리
	editor,
	title,
	year,
	volume,
	number,
	month,
	note,
	key,
	journal,
	pages,
	publisher,
	series,
	address,
	edition,
	url,
	booktitle,
	organization,
	error
};

FieldName strToFieldName(std::string str);
std::string fieldNameToStr(FieldName fieldName);

#endif