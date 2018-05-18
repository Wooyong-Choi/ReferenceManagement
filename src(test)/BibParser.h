#ifndef BIBPARSER_HEADER
#define BIBPARSER_HEADER

#include <string>
#include <map>
#include <vector>

#include "Field.h"
#include "common.h"

/*
@article{aha1991instance,
	title={Instance-based learning algorithms},
	author={Aha, David W and Kibler, Dennis and Albert, Marc K},
	journal={Machine learning},
	volume={6},
	number={1},
	pages={37--66},
	year={1991},
	publisher={Springer}
}
*/

class BibParser {
private:
	static std::vector<std::string> tokenize(const std::string& str,
		std::vector<std::string>& tokens,
		const std::string& delimiters = "=")
	{
		std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

		std::string::size_type pos = str.find_first_of(delimiters, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			std::string token = str.substr(lastPos, pos - lastPos);
			for (int i = 0; i < token.length(); i++) {
				if (token[i] == ' ' || token[i] == '{' || token[i] == '}' || token[i] == ',' || token[i] == '\t') {
					token.erase(i, 1);
					i -= 1;
				}
				else {
					break;
				}
			}
			int token_len = (int)token.length() - 1;
			for (int i = token_len; i >= 0; i--) {
				if (token[i] == ' ' || token[i] == '{' || token[i] == '}' || token[i] == ',' || token[i] == '\t') {
					token.erase(i, 1);
				}
				else {
					break;
				}
			}
			// token을 찾았으니 vector에 추가한다
			tokens.push_back(token);
			// 구분자를 뛰어넘는다.  "not_of"에 주의하라
			lastPos = str.find_first_not_of(delimiters, pos);
			// 다음 구분자가 아닌 글자를 찾는다
			pos = str.find_first_of(delimiters, lastPos);
		}
		return tokens;
	}

	static std::vector<std::string> field_token(std::string sent) {
		//    std::cout << sent.find("=") << std::endl;
		std::vector<std::string> tokens;
		std::vector<std::string> new_tokens;
		if (sent.find("=") > sent.length()) {
			//exception
		}
		else {
			//        std::cout << "여기여기" << std::endl;
			new_tokens = tokenize(sent, tokens);
			//        copy(new_tokens.begin(), new_tokens.end(), std::ostream_iterator<std::string>(std::cout, ", "));
		}
		return new_tokens;
	}

	static std::vector<std::string> split(std::string str, std::string delimiter) {
		std::vector<std::string> splited;
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			splited.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		splited.push_back(str);
		return splited;
	}

public:
	
	static std::map<std::string, std::string> parseLines(std::vector<std::string> lines) {
		int lines_len = lines.size();
		std::map<std::string, std::string> parsed;

		// "ent_typ" : Entry type str
		std::string entryType = split(lines[0], "{")[0];
		entryType = entryType.substr(1, entryType.length() - 1);
		parsed[ENTRY_TYPE] = entryType;

		// FieldType str : FieldValue str
		for (int i = 1; i < lines_len - 1; i++) {
			std::vector<std::string> token_result = field_token(lines[i]);
			parsed[token_result[0]] = token_result[1];
		}

		return parsed;
	}

	static std::vector<Field>* makeFieldList(std::vector<FieldName> req, std::vector<FieldName> opt, std::map<std::string, std::string> parsed) {
		// For validity check
		int parsedLen = parsed.size();

		std::vector<Field>* fieldList = new std::vector<Field>();

		// required field check
		for(FieldName fn : req) {
			for(std::pair<std::string, std::string> pair : parsed) {
				if (fieldNameToStr(fn) == pair.first) {
					Field field(strToFieldName(pair.first), pair.second);
					fieldList->push_back(field);
					parsed.erase(pair.first);
					break;
				}
			}
		}

		// Req가 다 있는가
		if (fieldList->size() != req.size())
			return NULL;

		// optional field check
		for(FieldName fn : opt) {
			for(std::pair<std::string, std::string> pair : parsed) {
				if (fieldNameToStr(fn) == pair.first) {
					Field field(strToFieldName(pair.first), pair.second);
					fieldList->push_back(field);
					parsed.erase(pair.first);
					break;
				}
			}
		}

		// Opt에 없는게 있는가
		if (fieldList->size() != parsedLen)
			return NULL;
		else
			return fieldList;
	}
};

#endif