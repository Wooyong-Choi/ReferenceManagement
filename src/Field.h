#ifndef FIELD_HEADER
#define FIELD_HEADER

#include <vector>
#include <string>
#include "FieldName.h"

class Field {
private:
	FieldName name;
	std::string value;

	friend std::ostream & operator<<(std::ostream & _stream, Field const & mc) {
		_stream << "  " << fieldNameToStr(mc.name) << " = {" << mc.value << "}" << std::endl;
		return _stream;
	}

public:
	Field() {

	}

	Field(FieldName name, std::string value) {
		this->name = name;
		this->value = value;
	}
	FieldName getFieldName() {
		return name;
	}
	std::string getFieldValue() {
		return value;
	}
	void setFieldName(FieldName newFieldName) {
		this->name = newFieldName;	
	}
	void setFieldValue(std::string newValue) {
		this->value = newValue;
	}
};

#endif