#ifndef FILEIOMANAGER_HEADER
#define FILEIOMANAGER_HEADER
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class FileIOManager {
private:

public:
	static std::vector<std::string> readFile(std::string filePath) {
		std::ifstream inFile(filePath);
		std::vector<std::string> docLines;

		try {
			if (inFile.is_open()) {
				std::string line;
				while (getline(inFile, line)) {
					if (line.at(line.size() - 1) == '\n')
						line = line.substr(0, line.size() - 1);
					docLines.push_back(line);
				}
			}
			else {
				throw 1;
			}
		}
		catch (int x) {
			std::cout << "File Open Error!" << std::endl;
			exit(x);
		}

		inFile.close();
		return docLines;
	}
};

#endif
