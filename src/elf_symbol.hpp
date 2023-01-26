#ifndef _ELF_SYMBOL_H
#define _ELF_SYMBOL_H

#include <stdint.h>
#include <stdbool.h>
#include <string>
#include <list>


class SymbolRecord {
	std::string Original;
public:
	// bool compare(const SymbolRecord &a, const SymbolRecord &b);
	bool isValid;

	union {
		uint64_t Value;
		uint64_t Address;
	};
	struct {
		char Scope;
		char Weak;
		char Ctor;
		char Warn;
		char Indir;
		char Cls;
		char Ntype;
	} Chars;
	bool isGlobal;
	bool isLocal;
	bool isWeak;
	bool isCtor;
	bool isWarning;
	bool isIndirectRef;
	bool isDebugging;
	bool isDynamic;
	bool isFunction;
	bool isFile;
	bool isObject;
	bool isSegment;
	std::string Section;
	union {
		uint64_t Size;
		uint64_t Alignment;
	};
	std::string Name;
	std::string Filename;
	SymbolRecord(std::string ObjdumpString);
};

class SymbolRecordList {
	std::list<SymbolRecord> locallist;
	std::list<SymbolRecord> functions;
public:
	SymbolRecordList();

	void Fill(std::string infile);

	std::list<SymbolRecord>* GetFunctions();
};





#endif /* _ELF_SYMBOL_H */
