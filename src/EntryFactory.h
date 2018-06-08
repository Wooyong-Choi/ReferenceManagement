#ifndef ENTRYFACTORY_HEADER
#define ENTRYFACTORY_HEADER

#include <map>
#include <vector>

#include "Entry.h"
#include "Article.h"
#include "Book.h"
#include "Inproceedings.h"
#include "common.h"


class EntryFactory {
private:
	/*
	@ Article
	Required fields: author, title, journal, year.
	Optional fields: volume, number, pages, month, note.

	@ Book
	Required fields: author or editor, title, publisher, year.
	Optional fields: volume, number, series, address, edition, month, note.

	@ Inproceedings
	Required fields: author, title, booktitle, year.
	Optional fields: editor, volume, number, series, pages, address, month, organization, publisher, note.
	*/

public:
	static Entry* produce(std::map<std::string, std::string> parsed) {
		EntryType type = strToEntryType(parsed.at(ENTRY_TYPE));
		parsed.erase(ENTRY_TYPE);

		Entry* product = NULL;
		std::vector<Field>* fieldList = NULL;
		try {
			switch (type) {
			case EntryType::article:
				fieldList = BibParser::makeFieldList(reqField_article, optField_article, parsed);
				if (fieldList != NULL)
					product = new Article(*fieldList);
				break;

			case EntryType::book:
				fieldList = BibParser::makeFieldList(reqField_book, optField_book, parsed);
				if (fieldList != NULL)
					product = new Book(*fieldList);
				break;

			case EntryType::inproceedings:
				fieldList = BibParser::makeFieldList(reqField_inproceedings, optField_inproceedings, parsed);
				if (fieldList != NULL)
					product = new Inproceedings(*fieldList);
				break;

			default:
				throw 2;
			}
		}
		catch (int x) {
			std::cout << "Entry Type Error!" << std::endl;
			exit(x);		
		}

		return product;
	}
};

#endif