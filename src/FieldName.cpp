#include "FieldName.h"

FieldName strToFieldName(std::string str) {
	if (str == "author")
		return FieldName::author;
	else if (str == "editor")
		return FieldName::author;
	else if (str == "title")
		return FieldName::title;
	else if (str == "year")
		return FieldName::year;
	else if (str == "volume")
		return FieldName::volume;
	else if (str == "number")
		return FieldName::number;
	else if (str == "month")
		return FieldName::month;
	else if (str == "note")
		return FieldName::note;
	else if (str == "key")
		return FieldName::key;
	else if (str == "journal")
		return FieldName::journal;
	else if (str == "pages")
		return FieldName::pages;
	else if (str == "publisher")
		return FieldName::publisher;
	else if (str == "series")
		return FieldName::series;
	else if (str == "address")
		return FieldName::address;
	else if (str == "edition")
		return FieldName::edition;
	else if (str == "url")
		return FieldName::url;
	else if (str == "booktitle")
		return FieldName::booktitle;
	else if (str == "organization")
		return FieldName::organization;
	else if (str == "group")
		return FieldName::group;
	else
		return FieldName::error;
}

std::string fieldNameToStr(FieldName fieldName) {
	switch (fieldName) {
	case FieldName::author:
		return "author";
	case FieldName::editor:
		return "editor";
	case FieldName::title:
		return "title";
	case FieldName::year:
		return "year";
	case FieldName::volume:
		return "volume";
	case FieldName::month:
		return "month";
	case FieldName::note:
		return "note";
	case FieldName::key:
		return "key";
	case FieldName::journal:
		return "journal";
	case FieldName::number:
		return "number";
	case FieldName::pages:
		return "pages";
	case FieldName::publisher:
		return "publisher";
	case FieldName::series:
		return "series";
	case FieldName::address:
		return "address";
	case FieldName::edition:
		return "edition";
	case FieldName::url:
		return "url";
	case FieldName::booktitle:
		return "booktitle";
	case FieldName::organization:
		return "organization";
	case FieldName::group:
		return "group";
	default:
		return "error";  // exception handling

	}
}