#ifndef _SymbolRecord_H
#define _SymbolRecord_H

#include <string>

class SymbolRecord {
	std::string Original;
public:
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

	bool isCommon;
	bool isUndefReference;
	bool isAbsolute;
	std::string Section;
	union {
		uint64_t Size;
		uint64_t Alignment;
	};
	std::string Name;
	std::string Filename;

	// Constructor
	SymbolRecord(std::string ObjdumpString);
};

#endif /* _SymbolRecord_H */
