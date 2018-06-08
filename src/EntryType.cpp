#include "EntryType.h"

EntryType strToEntryType(std::string str) {
	if (str == "article")
		return EntryType::article;
	else if (str == "inproceedings")
		return EntryType::inproceedings;
	else if (str == "book")
		return EntryType::book;
	else {
		return EntryType::error;
	}
}

std::string entryTypeToStr(EntryType entryName) {
	switch (entryName) {
	case EntryType::article:
		return "article";
	case EntryType::inproceedings:
		return "inproceedings";
	case EntryType::book:
		return "book";
	default:
		//error handling
		return "error";
	}
}