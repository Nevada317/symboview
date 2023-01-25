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
	isValid = false;
	printf("SymbolRecord:\n%s\n", ObjdumpString.c_str());
	std::regex rgx("^([0-9A-Fa-f]+) (.)(.)(.)(.)(.)(.)(.)[\t ]+([^\t ]+)[\t ]+([0-9A-Fa-f]+)[\t ]+([^\t ]+)");
	std::smatch matches;

	if(std::regex_search(ObjdumpString, matches, rgx) && (matches.size() == 12)) {
		string sarg;
		char carg;
		sarg = matches[OBJDUMP_ARG_INDEX_VALUE  ].str();
		Value = stol(sarg, NULL, 16);

		Chars.Scope = (carg = matches[OBJDUMP_ARG_INDEX_SCOPE].str()[0]);
		isLocal  = (carg == 'l') || (carg == '!');
		isGlobal = (carg == 'g') || (carg == '!');

		Chars.Weak  = (carg = matches[OBJDUMP_ARG_INDEX_WEAK ].str()[0]);
		isWeak = (carg == 'w');

		Chars.Ctor  = (carg = matches[OBJDUMP_ARG_INDEX_CTOR ].str()[0]);
		isCtor = (carg == 'C');

		Chars.Warn  = (carg = matches[OBJDUMP_ARG_INDEX_WARN ].str()[0]);
		isWarning = (carg == 'W');

		Chars.Indir = (carg = matches[OBJDUMP_ARG_INDEX_INDIR].str()[0]);
		isIndirectRef = (carg == 'I');

		Chars.Cls   = (carg = matches[OBJDUMP_ARG_INDEX_CLASS].str()[0]);
		isDebugging = (carg == 'd');
		isDynamic   = (carg == 'D');

		Chars.Ntype = (carg = matches[OBJDUMP_ARG_INDEX_NTYPE].str()[0]);
		isFunction = (carg == 'F');
		isFile     = (carg == 'f');
		isObject   = (carg == 'O');
		isSegment  = (carg == ' ');

		sarg = matches[OBJDUMP_ARG_INDEX_SECTION].str();
		Section = sarg;

		sarg = matches[OBJDUMP_ARG_INDEX_SIZE   ].str();
		Size = stol(sarg, NULL, 16);

		sarg = matches[OBJDUMP_ARG_INDEX_NAME   ].str();
		Name = sarg;

		Original = ObjdumpString;
		isValid = true;
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
