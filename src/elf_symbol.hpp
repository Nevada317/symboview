#ifndef _ELF_SYMBOL_H
#define _ELF_SYMBOL_H

#include <stdint.h>
#include <stdbool.h>
#include <string>
#include <list>


class SymbolRecord {
	uint64_t Value; // aka uint64_t Address;
	struct {
		// Group 1
		enum {
			SCOPE_None        = ' ',
			SCOPE_Local       = 'l',
			SCOPE_Global      = 'g',
			SCOPE_Both        = '!',
		} Scope;
		// Group 2
		bool Weak; // w/_
		// Group 3
		bool Constructor; // C/_
		// Group 4
		bool Warning; // W/_
		// Group 5
		bool IndirectReference; // I/_
		// Group 6
		enum {
			Class_Regular     = ' ',
			Class_Debugging   = 'd',
			Class_Dynamic     = 'D'
		} Class;
		// Group 7
		enum {
			NameType_Normal   = ' ',
			NameType_Function = 'F',
			NameType_File     = 'f',
			NameType_Object   = 'O',
		} NameType;
	} Flags;
	std::string Section;
	union {
		uint32_t Size;
		uint32_t Alignment;
	};
	std::string Name;
public:
	SymbolRecord(std::string ObjdumpString);
};

class SymbolRecordList {
	std::list<SymbolRecord> locallist;
public:
	SymbolRecordList();
	void Fill(std::string infile);
};





#endif /* _ELF_SYMBOL_H */
