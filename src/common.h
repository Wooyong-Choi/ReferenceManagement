#ifndef COMMON_HEADER
#define COMMON_HEADER

#include <string>
#include <vector>

#include "FieldName.h"

static std::string ENTRY_TYPE = "ent_typ";

static std::string DB_FILE_NAME = "rm_db.bin";

static std::vector<FieldName> reqField_article = { FieldName::author, FieldName::title, FieldName::journal, FieldName::year };
static std::vector<FieldName> optField_article = { FieldName::volume, FieldName::number, FieldName::pages, FieldName::month, FieldName::note, FieldName::group };
 
static std::vector<FieldName> reqField_book = { FieldName::author, FieldName::title, FieldName::publisher, FieldName::year };
static std::vector<FieldName> optField_book = { FieldName::volume, FieldName::number, FieldName::series, FieldName::address, FieldName::edition, FieldName::month, FieldName::note, FieldName::group };
 
static std::vector<FieldName> reqField_inproceedings = { FieldName::author, FieldName::title, FieldName::booktitle, FieldName::year };
static std::vector<FieldName> optField_inproceedings = { FieldName::editor, FieldName::volume, FieldName::number, FieldName::series, FieldName::pages, FieldName::address, FieldName::month, FieldName::organization, FieldName::publisher, FieldName::note, FieldName::group };

#endif