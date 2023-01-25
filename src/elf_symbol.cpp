#include "elf_symbol.hpp"

#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <regex>
#include <iostream>
#include <cassert>

using namespace std;

#define OBJDUMP_ARG_INDEX_VALUE    1
#define OBJDUMP_ARG_INDEX_SCOPE    2
#define OBJDUMP_ARG_INDEX_WEAK     3
#define OBJDUMP_ARG_INDEX_CTOR     4
#define OBJDUMP_ARG_INDEX_WARN     5
#define OBJDUMP_ARG_INDEX_INDIR    6
#define OBJDUMP_ARG_INDEX_CLASS    7
#define OBJDUMP_ARG_INDEX_NTYPE    8
#define OBJDUMP_ARG_INDEX_SECTION  9
#define OBJDUMP_ARG_INDEX_SIZE    10
#define OBJDUMP_ARG_INDEX_NAME    11

SymbolRecord::SymbolRecord(std::string ObjdumpString) {
	printf("SymbolRecord:\n%s\n", ObjdumpString.c_str());
	std::regex rgx("^([0-9]+) (.)(.)(.)(.)(.)(.)(.)[\t ]+([^\t ]+)[\t ]+([0-9]+)[\t ]+([^\t ]+)");
	std::smatch matches;

	if(std::regex_search(ObjdumpString, matches, rgx)) {
		assert(matches.size() == 12);
		string arg;
		arg = matches[OBJDUMP_ARG_INDEX_VALUE  ].str();
		stol(arg.c_str(), &this->Value, 16);
		arg = matches[OBJDUMP_ARG_INDEX_SCOPE  ].str();
		arg = matches[OBJDUMP_ARG_INDEX_WEAK   ].str();
		arg = matches[OBJDUMP_ARG_INDEX_CTOR   ].str();
		arg = matches[OBJDUMP_ARG_INDEX_WARN   ].str();
		arg = matches[OBJDUMP_ARG_INDEX_INDIR  ].str();
		arg = matches[OBJDUMP_ARG_INDEX_CLASS  ].str();
		arg = matches[OBJDUMP_ARG_INDEX_NTYPE  ].str();
		arg = matches[OBJDUMP_ARG_INDEX_SECTION].str();
		arg = matches[OBJDUMP_ARG_INDEX_SIZE   ].str();
		arg = matches[OBJDUMP_ARG_INDEX_NAME   ].str();
		// for (size_t i = 0; i < matches.size(); ++i) {
			// printf("  Match %d: %s\n", (int)i, matches[i].str().c_str());
		// }
		printf("Match: %s @ %lx\n", matches[11].str().c_str(), Value);
	}
}

SymbolRecordList::SymbolRecordList() {
	printf("SymbolRecordList\n");
}

void SymbolRecordList::Fill(std::string infile) {
	ifstream inFile;
	inFile.open(infile);

	string context_filename = "";

	std::string line;
	while (std::getline(inFile, line))
	{
		if (!strncmp(line.c_str(), "@FILE:", 6)) {
			printf("FILENAME: %s\n", line.c_str());
			// scanf("line: %s\n", line.c_str());
		}
		SymbolRecord temp(line);
		// printf("line: %s\n", line.c_str());

	}
}
