#ifndef ENTRYTYPE_HEADER
#define ENTRYTYPE_HEADER

#include <string>

enum class EntryType
{
	article,
	inproceedings,
	book
};

EntryType strToEntryType(std::string str);
std::string entryTypeToStr(EntryType entryName);

#endif