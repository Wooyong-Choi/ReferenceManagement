#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "FileIOManager.h"
#include "Entry.h"
#include "BibParser.h"
#include "EntryFactory.h"

using namespace std;

void importFile(int argc, char *argv[]);
void printList(char *argv[]);
void update(char *argv[]);
void updateElement(char *argv[]);
void printStat();
void group(int argc, char *argv[]);
void searchList(int argc, char *argv[]);

void saveDB(const string file_name, const vector<Entry>& prod);
vector<Entry> loadDB(const string file_name);
Entry* loadEntry(const string path);

vector<Entry> rm_db;

int main(int argc, char *argv[]) {
	// load DB
	rm_db = loadDB(DB_FILE_NAME);
	cout << "Success to load data : " << rm_db.size() << " of ref" << endl << endl;

	try {
		// Do command with arguments
		string cmd(argv[1]);

		// Error 1 : Invalid file
		// Error 2 : Entry type error
		// Error 3 : Index error(out of range)
		// Error 4 : Argument error - not enough or too much arg error
		// Error 5 : Field Name error
		// Error 6 : Required Field Error
		// Error 7 : Optional Field Error
		// Error 8 : Argument Type Error 
		// Error 9 : Invalid Command

		if (cmd == "--input") {
			if (argc < 3) throw 4;
			importFile(argc - 2, argv);
		}
		else if (cmd == "--list") {
			if (argc != 3) throw 4;
			printList(argv);
		}
		else if (cmd == "--update") {
			if (argc != 4) throw 4;
			update(argv);
		}
		else if (cmd == "--element") {
			if (argc != 5) throw 4;
			updateElement(argv);
		}
		else if (cmd == "--stat") {
			if (argc != 2) throw 4;
			printStat();
		}
		else if (cmd == "--group") {
			if (argc < 4) throw 4;
			group(argc, argv);
		}
        else if (cmd == "--search"){
            if (argc % 2 != 0) throw 4;
            searchList(argc, argv);
        }
		else {
			throw 9;
		}
	}
	catch (int x) {
		if (x == 4)
			cout << "Argument Error! Too Much or not enough argument." <<endl;
		else if(x == 9)
			cout << "Invalid command!" << endl;
		exit(x);
	}
	catch (exception& e) {
		cout << "Some Error in command! Check argument type like integer, string, entiry type and so on ... \n" << endl;
		exit(0);
	}
	// save DB
	saveDB(DB_FILE_NAME, rm_db);
}

void searchList(int argc, char *argv[]){
    vector<Field> condList;
    string condEntry;
    
    for (int i = 2; i < argc; i+=2) {
        string condKey(argv[i]);
        string condValue(argv[i+1]);
        condKey = condKey.substr(2, condKey.length());
        
        if (condKey == "EntryType") {
            condEntry = condValue;
            continue;
        }
        
        Field f(strToFieldName(condKey), condValue);
        condList.push_back(f);
    }
    
    vector<Entry> tempList;
    for (Entry e : rm_db) {
        int cnt = 0;
        vector<Field> fieldList = e.getFieldList();
        for (Field f : fieldList) {
            for (Field cond : condList) {
                if (f.getFieldName() == cond.getFieldName() && f.getFieldValue() == cond.getFieldValue())
                    cnt++;
            }
        }
        if (condEntry.length() > 0 && strToEntryType(condEntry) != e.getEntryType())
            continue;
        if (cnt == condList.size()) {
            tempList.push_back(e);
        }
    }
    
    for (Entry e : tempList)
        cout << e << endl;
    
    if (tempList.size() == 0)
        cout << "Not found" << endl;
}

void printList(char *argv[]) {
	string all(argv[2]);

		if (all == "all") {
			for (int i = 0; i < rm_db.size(); i++) {
				cout << "Index : " << i << endl;
				cout << rm_db[i] << endl;
			}
		}
		else {
			try{
				cout << "Index : " << stoi(all) << endl;
				throw 3;
				cout << rm_db[stoi(all)] << endl;
				
			}
			catch (int x) {
				cerr << "Out of Range Error!" << endl;
				exit(x);
			}
		} 		
}

void group(int argc, char *argv[]) {
	try {
		string sub_cmd(argv[2]);
		int idx = stoi(argv[3]);

		if (sub_cmd == "add") {
			char *arg[5] = { "", "", argv[3], "group", argv[4] };
			updateElement(arg);
		}
		else if (sub_cmd == "del") {
			if (argc == 4)
				throw 4;
			char *arg[5] = { "", "", argv[3], "group", "Default" };
			updateElement(arg);
		}
		else
			throw 8;
		cout << rm_db[idx] << endl;
	}
	catch (int x) {
		if (x == 4)
			cout << "Argument Error! Too Much or not enough argument." << endl;
		else if (x == 8)
			cout << "Argument Type Error!" << endl;
		exit(x);
	}
}

void importFile(int argc, char *argv[]) {
	try {
		if (argc == 1) { // single file of text file
			string path(argv[2]);
			string cmd_type = ".txt";
			if (path.find(cmd_type, 0) != string::npos) { // file_path file
				vector<string> paths = FileIOManager::readFile(path);
				for (int i = 0; i < paths.size(); i++) {
					Entry* entry = loadEntry(paths[i]);
					if (entry == NULL) {
						//cout << "Fail to import : " << paths[i] << endl << *entry << endl;
						throw 1;
					}
					else {
						rm_db.push_back(*entry);
						cout << "Success to import : " << paths[i] << endl << *entry << endl;
					}
				}
			}
			else { // single file
				Entry* entry = loadEntry(path);
				if (entry == NULL) {
					//cout << "Fail to import : " << path << endl << *entry << endl;
					throw 1;
				}
				else {
					rm_db.push_back(*entry);
					cout << "Success to import : " << path << endl << *entry << endl;
				}
			}
		}
		else { // multifile
			for (int i = 0; i < argc; i++) {
				Entry* entry = loadEntry(argv[i + 2]);
				if (entry == NULL) {
					//cout << "Fail to import : " << argv[i + 2] << endl << *entry << endl;
					throw 1;
				}
				else {
					rm_db.push_back(*entry);
					cout << "Success to import : " << argv[i + 2] << endl << *entry << endl;
				}
			}
		}
	}
	catch (int x) {
		if (x == 1) cout << "Invalid File" << endl;
		exit(x);	
	}
}

void update(char *argv[]) {
	try {
		int idx = stoi(argv[2]); 
		string path(argv[3]);

		vector<string> new_lines = FileIOManager::readFile(path);
		map<string, string> new_parsed = BibParser::parseLines(new_lines);
		Entry new_entry = *EntryFactory::produce(new_parsed);

	
		Entry temp = rm_db[idx]; 
		throw 3;

		rm_db[idx].setEntryType(new_entry.getEntryType());
		rm_db[idx].setFieldList(new_entry.getFieldList());

		cout << "Index : " << idx << " is updated" << endl;
		cout << "before : " << endl << temp << endl << "aftrer  : " << endl << rm_db[idx] << endl;
	}
	catch (int x) {
		if (x == 3)
			cout << "Out of Range Error!" << endl;
		else if (x == 8)
			cout << "Argument Type Error!" << endl;
		exit(x);
	}
}

void updateElement(char *argv[]) {
	try {
		int idx = stoi(argv[2]);
		string field(argv[3]);
		string value(argv[4]);

		if (rm_db.size() <= idx)
			throw 3;
		int findField = 0;
		for (int i = 0; i < rm_db[idx].getFieldList().size(); i++) {
			if (strToFieldName(field) == rm_db[idx].getFieldList()[i].getFieldName()) {
				vector<Field> temp = rm_db[idx].getFieldList();
				cout << "before :" << temp[i];
				temp[i].setFieldValue(value);
				rm_db[idx].setFieldList(temp);
				cout << "after  :" << rm_db[idx].getFieldList()[i];
				findField = 1;
				break;
			}
		}
		if (findField == 0) throw 5;
	}
	catch (int x) {
		if (x == 3) cout << "Out of Range Error!" << endl;
		else if (x == 5) cout << "Field Type Error!" << endl;
		else if (x == 8) cout << "Argument Type Error!" << endl;
		exit(x);
	}
}

void printStat() {
	vector<int> years;
	map<string, int> stat;
	map<string, int>::iterator iter;
	iter = stat.begin();

	int count = 0;
	for (int i = 0; i < rm_db.size(); i++) {
		for (int j = 0; j < rm_db[i].getFieldList().size(); j++) {
			if (fieldNameToStr(rm_db[i].getFieldList()[j].getFieldName()) == "year") {
				//cout << rm_db[i].getFieldList()[j].getFieldValue() << endl;
				if (!stat[rm_db[i].getFieldList()[j].getFieldValue()]) {
					stat[rm_db[i].getFieldList()[j].getFieldValue()] = 1;;
					count += 1;
				}
				else {
					stat[rm_db[i].getFieldList()[j].getFieldValue()] += 1;
					count += 1;
				}
				//years.push_back(rm_db[i].getFieldList()[j].getFieldValue);
			}
		}
	}

	cout << "Total reference : " << count << endl << endl;

	for (iter = stat.begin(); iter != stat.end(); ++iter) {
		cout << "(In " << (*iter).first << " : " << (*iter).second << " )" << endl;
	}
}

void saveDB(const string file_name, const vector<Entry>& prod) {
	ofstream file(file_name);
	for (const Entry& p : prod)
		file << p;
	file.close();
}

vector<Entry> loadDB(const string file_name) {
	vector<Entry> prod;
	ifstream file(file_name);
	Entry temp;
	while (file >> temp) { // canonical; for every Entry read from the file
		prod.push_back(temp); // add it to the vector
	}
	file.close();

	return prod;
}

Entry* loadEntry(string path) {
	if (path[path.size() - 1] == '\r')
		path = path.substr(0, path.size() - 1);

	vector<string> lines = FileIOManager::readFile(path);
	map<string, string> parsed = BibParser::parseLines(lines);
	Entry* entry = EntryFactory::produce(parsed);

	return entry;
}
