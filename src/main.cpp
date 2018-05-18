#include <iostream>
#include <string>
#include <vector>

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

void saveDB(const string file_name, const vector<Entry>& prod);
vector<Entry> loadDB(const string file_name);
Entry* loadEntry(const string path);

vector<Entry> rm_db;

int main(int argc, char *argv[]) {
    // load DB
    rm_db = loadDB(DB_FILE_NAME);
    cout << "Success to load data : " << rm_db.size() << " of ref" << endl << endl;
    
    // Do command with arguments
    string cmd(argv[1]);
    
    if (cmd == "--input") {
        importFile(argc - 2, argv);
    }
    else if (cmd == "--list") {
        printList(argv);
    }
    else if (cmd == "--update") {
        update(argv);
    }
    else if (cmd == "--element") {
        updateElement(argv);
    }
    else if (cmd == "--stat") {
        printStat();
    }
    else {
        // Error handling
        cerr << "Invalid arguments" << endl;
    }
    
    // save DB
    saveDB(DB_FILE_NAME, rm_db);
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
        cout << "Index : " << stoi(all) << endl;
        cout << rm_db[stoi(all)] << endl;
    }
}

void importFile(int argc, char *argv[]) {
    if (argc == 1) {
        string path(argv[2]);
        string cmd_type = ".txt";
        if (path.find(cmd_type, 0) != string::npos) {
            vector<string> paths = FileIOManager::readFile(path);
            for (int i = 0; i < paths.size(); i++) {
                Entry* entry = loadEntry(paths[i]);
                if (entry == NULL) {
                    cout << "Fail to import : " << paths[i] << endl << *entry << endl;
                }
                else {
                    rm_db.push_back(*entry);
                    cout << "Success to import : " << paths[i] << endl << *entry << endl;
                }
            }
        }
        else {
            Entry* entry = loadEntry(path);
            if (entry == NULL) {
                cout << "Fail to import : " << path << endl << *entry << endl;
            }
            else {
                rm_db.push_back(*entry);
                cout << "Success to import : " << path << endl << *entry << endl;
            }
        }
    }
    else {
        for (int i = 0; i < argc; i++) {
            Entry* entry = loadEntry(argv[i + 2]);
            if (entry == NULL) {
                cout << "Fail to import : " << argv[i + 2] << endl << *entry << endl;
            }
            else {
                rm_db.push_back(*entry);
                cout << "Success to import : " << argv[i + 2] << endl << *entry << endl;
            }
        }
    }
}

void update(char *argv[]) {
    int idx = stoi(argv[2]);
    string path(argv[3]);
    
    vector<string> new_lines = FileIOManager::readFile(path);
    map<string, string> new_parsed = BibParser::parseLines(new_lines);
    Entry new_entry = *EntryFactory::produce(new_parsed);
    
    Entry temp = rm_db[idx];
    
    rm_db[idx].setEntryType(new_entry.getEntryType());
    rm_db[idx].setFieldList(new_entry.getFieldList());
    
    cout << "Index : " << idx << " is updated" << endl;
    cout << "before : " << endl << temp << endl << "aftrer  : " << endl << rm_db[idx] << endl;
}

void updateElement(char *argv[]) {
    int idx = stoi(argv[2]);
    string field(argv[3]);
    string value(argv[4]);
    
    cout << "Index : " << idx << endl;
    for (int i = 0; i < rm_db[idx].getFieldList().size(); i++) {
        if (strToFieldName(field) == rm_db[idx].getFieldList()[i].getFieldName()) {
            vector<Field> temp = rm_db[idx].getFieldList();
            cout << "before :" << temp[i];
            temp[i].setFieldValue(value);
            rm_db[idx].setFieldList(temp);
            cout << "after  :" << rm_db[idx].getFieldList()[i];
            break;
        }
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
    if (path[path.size()-1] == '\r')
        path = path.substr(0, path.size()-1);
	
    vector<string> lines = FileIOManager::readFile(path);
    map<string, string> parsed = BibParser::parseLines(lines);
    Entry* entry = EntryFactory::produce(parsed);
    
    return entry;
}
