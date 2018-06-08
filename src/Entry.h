#ifndef ENTRY_HEADER
#define ENTRY_HEADER

#include <map>
#include <vector>
#include <string>

#include "EntryType.h"
#include "Field.h"
#include "BibParser.h"
#include "common.h"

class Entry {
private:

protected:

	EntryType type;
	std::vector<Field> fieldList;
	
	Entry(EntryType type, std::vector<Field> fieldList) {
		this->type = type;
		this->fieldList = fieldList;

		bool groupChk = false;
		for (Field field : fieldList) {
			if (field.getFieldName() == FieldName::group) {
				groupChk = true;
				break;
			}
		}
		if (groupChk == false) {
			Field group(FieldName::group, "Default");
			this->fieldList.push_back(group);
		}
	}

	friend std::ostream & operator<<(std::ostream & _stream, Entry const & mc) {
		_stream << "@" << entryTypeToStr(mc.type) << "{" << std::endl;
		for(Field field : mc.fieldList)
			_stream << Field(field);
		_stream << "}" << std::endl;
		return _stream;
	}

	friend std::istream& operator>>(std::istream& _stream, Entry & mc)
	{
		std::vector<std::string> lines;

		std::string buf;
		while (std::getline(_stream, buf)) {
			lines.push_back(buf);
			if (buf[0] == '}')
				break;
		}

		if (lines.size() != 0) {
			std::map<std::string, std::string> parsed = BibParser::parseLines(lines);
			mc.type = strToEntryType(parsed[ENTRY_TYPE]);
			parsed.erase(ENTRY_TYPE);

			switch (mc.type) {
			case EntryType::article:
				mc.fieldList = *BibParser::makeFieldList(reqField_article, optField_article, parsed);
				break;

			case EntryType::book:
				mc.fieldList = *BibParser::makeFieldList(reqField_book, optField_book, parsed);
				break;

			case EntryType::inproceedings:
				mc.fieldList = *BibParser::makeFieldList(reqField_inproceedings, optField_inproceedings, parsed);
				break;
			}
		}
		return _stream;
	}


public:
	Entry() {

	}

	void setEntryType(EntryType newEntryType) {
		this->type = newEntryType;
	}

	void setFieldList(std::vector<Field> newFieldList) {
		this->fieldList = newFieldList;
	}

	EntryType getEntryType() {
		return type;
	}

	std::vector<Field> getFieldList() {
		return fieldList;
	}
};

#endif