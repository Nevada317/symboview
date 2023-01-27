#include "symbolrecordlist.hpp"

#include <fstream>
#include <string>
#include <regex>


using namespace std;

SymbolRecordList::SymbolRecordList() {
	printf("SymbolRecordList\n");
}

void SymbolRecordList::Fill(std::string infile) {
	std::ifstream inFile;
	inFile.open(infile);

	string context_filename = "";

	std::string line;
	std::string filename = "";
	while (std::getline(inFile, line))
	{
		SymbolRecord* temp = new SymbolRecord(line);
		if (temp->isValid) {
			temp->Filename = filename;
			locallist.push_back(*temp);
			delete temp;
		} else if (line.length() > 5){
			std::regex rgx("^([^:]+):[\t ]+file");
			std::smatch matches;
			if(std::regex_search(line, matches, rgx) && (matches.size() == 2)) {
				printf("filename: %s\n", matches[1].str().c_str());
				filename = matches[1].str();
			}
		}
		// printf("line: %s\n", line.c_str());
	}
	// for (SymbolRecord& record : locallist) {
	// 	if (record.isFunction) {
	// 		printf("%s\n", record.Name.c_str());
	// 	}
	// }
	// std::list<SymbolRecord>* sorted1 = GetFunctions();
	// for (SymbolRecord& record : *sorted1) {
	// 	printf("D: %s (%s)\n", record.Name.c_str(), record.Filename.c_str());
	// }
	// std::list<SymbolRecord>* sorted2 = GetUndefs();
	// for (SymbolRecord& record : *sorted2) {
	// 	printf("C: %s (%s)\n", record.Name.c_str(), record.Filename.c_str());
	// }
}

static bool SymbolRecord_CompareByName(const SymbolRecord &a, const SymbolRecord &b) {
	return b.Name.compare(a.Name);
}

std::list<SymbolRecord>* SymbolRecordList::GetFunctions() {
	if (functions.empty()) {
		for (SymbolRecord& record : locallist) {
			if (record.isFunction) {
				functions.push_back(record);
			}
		}
		functions.sort(SymbolRecord_CompareByName);
	}
	return &functions;
}

std::list<SymbolRecord>* SymbolRecordList::GetUndefs() {
	if (undefs.empty()) {
		for (SymbolRecord& record : locallist) {
			if (record.isUndefReference) {
				undefs.push_back(record);
			}
		}
		undefs.sort(SymbolRecord_CompareByName);
	}
	return &undefs;
}
